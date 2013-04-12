#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_2
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "usb_config.h"
#include "USB/usb_device.h"
// *--------------------------------------------------------------------------------*
#pragma udata
char USB_In_Buffer[64];
char USB_Out_Buffer[64];
BOOL stringPrinted;
volatile BOOL buttonPressed;
volatile BYTE buttonCount;
// *--------------------------------------------------------------------------------*
void ProcessIO(void);
void BlinkUSBStatus(void);
// *--------------------------------------------------------------------------------*
int main(){
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	AD1PCFG = 0xFFFF;
	LED1_OUTPUT();
	LED2_OUTPUT();
	SW1_INPUT();
	SW2_INPUT();
	
	buttonCount = 0;
    buttonPressed = FALSE;
    stringPrinted = TRUE;
	
	USBDeviceInit();	
	while(1){
		#if defined(USB_INTERRUPT)
		if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE)){
			USBDeviceAttach();
		}
		#endif
		#if defined(USB_POLLING)
			// Check bus status and service USB interrupts.
			USBDeviceTasks();
		#endif
		ProcessIO();
	}
}
// *--------------------------------------------------------------------------------*
void ProcessIO(void){   
    BYTE numBytesRead;

    //Blink the LEDs according to the USB device status
    BlinkUSBStatus();
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    if(buttonPressed){
        if(stringPrinted == FALSE){
            if(mUSBUSARTIsTxTrfReady()){
                putrsUSBUSART("Button Pressed -- \r\n");
                stringPrinted = TRUE;
            }
        }
    }else{
        stringPrinted = FALSE;
    }

    if(USBUSARTIsTxTrfReady()){
		numBytesRead = getsUSBUSART(USB_Out_Buffer,64);
		if(numBytesRead != 0){
			BYTE i;
	        
			for(i=0;i<numBytesRead;i++){
				switch(USB_Out_Buffer[i]){
					case 0x0A:
					case 0x0D:
						USB_In_Buffer[i] = USB_Out_Buffer[i];
						break;
					default:
						USB_In_Buffer[i] = USB_Out_Buffer[i] + 1;
						break;
				}
			}
			putUSBUSART(USB_In_Buffer,numBytesRead);
		}
	}

    CDCTxService();
}
// *--------------------------------------------------------------------------------*
void BlinkUSBStatus(void){
    static WORD led_count=0;
    
    if(led_count == 0)led_count = 50000U;
    led_count--;

    #define mLED_Both_Off()         {LED1_OFF();LED2_OFF();}
    #define mLED_Both_On()          {LED1_ON();LED2_ON();}
    #define mLED_Only_1_On()        {LED1_ON();LED2_OFF();}
    #define mLED_Only_2_On()        {LED1_OFF();LED2_ON();}

    if(USBSuspendControl == 1){
        if(led_count==0){
            LED1_TOGGLE();
            if(LED1_READ()){
                LED2_ON();
            }else{
                LED2_OFF();
            }
        }
    }else{
        if(USBDeviceState == DETACHED_STATE){
            mLED_Both_Off();
        }else if(USBDeviceState == ATTACHED_STATE){
            mLED_Both_On();
        }else if(USBDeviceState == POWERED_STATE){
            mLED_Only_1_On();
        }else if(USBDeviceState == DEFAULT_STATE){
            mLED_Only_2_On();
        }else if(USBDeviceState == ADDRESS_STATE){
            if(led_count == 0){
                LED1_TOGGLE();
                LED2_OFF();
            }
        }else if(USBDeviceState == CONFIGURED_STATE){
            if(led_count==0){
                LED1_TOGGLE();
                if(LED1_READ()){
                    LED2_OFF();
                }else{
                    LED2_ON();
                }
            }
        }
    }

}
// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
void USBCBSuspend(void){
}

void USBCBWakeFromSuspend(void){
}
void USBCB_SOF_Handler(void){
	BOOL sw2;
	
	sw2=((SW2_STATUS()==0)?0:1);
    //This is reverse logic since the pushbutton is active low
    if(buttonPressed == sw2){
        if(buttonCount != 0){
            buttonCount--;
        }else{
            //This is reverse logic since the pushbutton is active low
            buttonPressed = !sw2;
            //Wait 100ms before the next press can be generated
            buttonCount = 100;
        }
    }else{
        if(buttonCount != 0){
            buttonCount--;
        }
    }
}

void USBCBErrorHandler(void){

}

void USBCBCheckOtherReq(void){
    USBCheckCDCRequest();
}
void USBCBStdSetDscHandler(void){
}
void USBCBInitEP(void){
    CDCInitEP();
}
void USBCBSendResume(void){
    static WORD delay_count;
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE){
        if(USBIsBusSuspended() == TRUE){
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE; 
            delay_count = 3600U;        
            do{
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do{
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}
#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void){
}
#endif
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size){
    switch(event){
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            break;
        default:
            break;
    }      
    return TRUE; 
}
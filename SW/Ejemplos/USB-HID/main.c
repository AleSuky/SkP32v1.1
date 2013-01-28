#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_1, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_1
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"
// *--------------------------------------------------------------------------------*
unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];
USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = TRUE;
// *--------------------------------------------------------------------------------*
void ProcessIO(void);
void BlinkUSBStatus(void);
void vADC_Init(void);
UINT16 ADC_Conversion(void);
// *--------------------------------------------------------------------------------*
int main(){
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	AD1PCFG = 0xFFFF;
	LED1_OUTPUT();
	LED2_OUTPUT();
	SW1_INPUT();
	SW2_INPUT();
	
	USBOutHandle = 0;
    USBInHandle = 0;
    blinkStatusValid = TRUE;
    
	USBDeviceInit();
	#if defined(USB_INTERRUPT)
	USBDeviceAttach();
    #endif
	while(1){
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
    BOOL sw3;

	if(blinkStatusValid==TRUE){
	    //Blink the LEDs according to the USB device status
	    BlinkUSBStatus();
	}    
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    
    if(!HIDRxHandleBusy(USBOutHandle)){				//Check if data was received from the host.
        switch(ReceivedDataBuffer[0]){				//Look at the data the host sent, to see what kind of application specific command it sent.
            case 0x80:  //Toggle LEDs command
		        blinkStatusValid = FALSE;			//Stop blinking the LEDs automatically, going to manually control them now.
                if(LED1_READ() == LED2_READ()){
                    LED1_TOGGLE();
                    LED2_TOGGLE();
                }else{
                    if(LED1_READ()){
                        LED2_ON();
                    }else{
                        LED2_OFF();
                    }
                }
                break;
            case 0x81:  //Get push button state
                ToSendDataBuffer[0] = 0x81;				//Echo back to the host PC the command we are fulfilling in the first byte.  In this case, the Get Pushbutton State command.
				sw3=((SW2_STATUS()==0)?0:1);
				if(sw3 == 1){							//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
					ToSendDataBuffer[1] = 0x01;			
				}else{									//sw3 must be == 0, pushbutton is pressed and overpowering the pull up resistor
					ToSendDataBuffer[1] = 0x00;
				}
                if(!HIDTxHandleBusy(USBInHandle)){
                    USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
                }
                break;

            case 0x37:	//Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host
                {
                    WORD_VAL w;

	                if(!HIDTxHandleBusy(USBInHandle)){
	                    vADC_Init();
	                    w.Val = ADC_Conversion();					
						ToSendDataBuffer[0] = 0x37;  	//Echo back to the host the command we are fulfilling in the first byte.  In this case, the Read POT (analog voltage) command.
						ToSendDataBuffer[1] = w.v[0];  	//Measured analog voltage LSB
						ToSendDataBuffer[2] = w.v[1];  	//Measured analog voltage MSB

	                    USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],64);
	                }					
                }
                break;
        }
        //Re-arm the OUT endpoint for the next packet
        USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
    }
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
// *--------------------------------------------------------------------------------*
void vADC_Init(void){
		
    AD1CON1=0;					// Off
    AD1CON1bits.SIDL=0;			// Encendido en modo IDLE
    AD1CON1bits.FORM=0;			// Data Output Format: Entero 16-bits
    AD1CON1bits.SSRC=0;			// Conversion manual
    AD1CON1bits.CLRASAM=0;		// Operacion Normal
    AD1CON1bits.ASAM=0;			// Para comenzar setear SAMP

    AD1CON2bits.VCFG=0;			// Vdd/Vss
    AD1CON2bits.OFFCAL=0;		// Apagada calibracion de offset
    AD1CON2bits.CSCNA=0;		// Scan off
    AD1CON2bits.SMPI=0b0000;    // Interrupcion por cada conversion
    AD1CON2bits.BUFM=0;			// Buffer 16-bits
    AD1CON2bits.ALTS=0;			// Usar siempre MUXA

    AD1CON3bits.ADRC=0;			// ADC Clock desde PBCLK
    AD1CON3bits.SAMC=0; 		// Muestreo manual
    AD1CON3bits.ADCS=20;        // ADC Conversion Clock Tad = TPB ? 2 ? (ADCS<7:0> + 1) = 525ns
                                // ADC Conversion Time for 10-bit Tc=13*Tad =  ~7us

    //AD1CHS0/AD1CHS123: A/D Input Select Register
    AD1CHSbits.CH0SA=14;		// MUXA +ve -> CH14 (Seleccion del canal analogico)
    AD1CHSbits.CH0NA=0;			// MUXA -ve -> Vr-

    //AD1PCFGH/AD1PCFGL: Port Configuration Register
    AD1PCFG=0xFFFF;
    AD1PCFGbits.PCFG14 = 0;		// AN14 as Analog Input
    AD1CON1bits.ON = 1;			// Turn on the A/D converter
}
// *-------------------------------------------*
UINT16 ADC_Conversion(void){
	
    AD1CON1bits.SAMP=1;			// Inicia adquisicion
    Delay10us(5);
    AD1CON1bits.SAMP=0;			// Inicia conversion
    Nop();
    while(AD1CON1bits.DONE==0);	// Esperamos conversion
    return(ADC1BUF0);
}
// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
void USBCBSuspend(void){

}
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
}
#endif
void USBCBWakeFromSuspend(void){
}
void USBCB_SOF_Handler(void){
}
void USBCBErrorHandler(void){ 
}
void USBCBCheckOtherReq(void){
    USBCheckHIDRequest();
}
void USBCBStdSetDscHandler(void){  
}
void USBCBInitEP(void){
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
}
void USBCBSendResume(void){
    static WORD delay_count;

    if(USBGetRemoteWakeupStatus() == TRUE){
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE){
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
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
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
#include "USB/USB.h"
#include "HardwareProfile.h"
#include "MDD File System/SD-SPI.h"
#include "MDD File System/FSIO.h"

#include "./USB/usb_function_msd.h"
// *--------------------------------------------------------------------------------*
LUN_FUNCTIONS LUN[MAX_LUN + 1] = 
{
    {
        &MDD_SDSPI_MediaInitialize,
        &MDD_SDSPI_ReadCapacity,
        &MDD_SDSPI_ReadSectorSize,
        &MDD_SDSPI_MediaDetect,
        &MDD_SDSPI_SectorRead,
        &MDD_SDSPI_WriteProtectState,
        &MDD_SDSPI_SectorWrite
    }
};
/* Standard Response to INQUIRY command stored in ROM 	*/
const ROM InquiryResponse inq_resp = {
	0x00,		// peripheral device is connected, direct access block device
	0x80,           // removable
	0x04,	 	// version = 00=> does not conform to any standard, 4=> SPC-2
	0x02,		// response is in format specified by SPC-2
	0x20,		// n-4 = 36-4=32= 0x20
	0x00,		// sccs etc.
	0x00,		// bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
			// but as in case of other device, we are just using 00
	0x00,		// 00 obsolete, 0x80 for basic task queueing
	{'M','i','c','r','o','c','h','p'
    },
	// this is the T10 assigned Vendor ID
	{'M','a','s','s',' ','S','t','o','r','a','g','e',' ',' ',' ',' '
    },
	{'0','0','0','1'
    }
};
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
	
	RtccInit();
	while(RtccGetClkStat()!=RTCC_CLK_ON);
	
	AD1PCFG = 0xFFFF;
	LED1_OUTPUT();
	LED2_OUTPUT();
	SW1_INPUT();
	SW2_INPUT();
	
	USBOutHandle = 0;
    USBInHandle = 0;
    blinkStatusValid = TRUE;
    
    MDD_InitIO();
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

	if(blinkStatusValid==TRUE){
	    //Blink the LEDs according to the USB device status
	    BlinkUSBStatus();
	}    
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    
    MSDTasks(); 

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
void USBCBSuspend(void)
{

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

void USBCBWakeFromSuspend(void)
{

}

void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

void USBCBErrorHandler(void)
{

}

void USBCBCheckOtherReq(void)
{
    USBCheckMSDRequest();
}//end

void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end

void USBCBInitEP(void)
{
    #if (MSD_DATA_IN_EP == MSD_DATA_OUT_EP)
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #else
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
        USBEnableEndpoint(MSD_DATA_OUT_EP,USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #endif

    USBMSDInit();
}

void USBCBSendResume(void)
{
    static WORD delay_count;

    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}

BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
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
            if(MSDWasLastCBWValid() == FALSE)
            {
                //Need to re-stall the endpoints, for persistent STALL behavior.
    			USBStallEndpoint(MSD_DATA_IN_EP, IN_TO_HOST);
      			USBStallEndpoint(MSD_DATA_OUT_EP, OUT_FROM_HOST);                 
            }
            else
            {   
                //Check if the host cleared halt on the bulk out endpoint.  In this
                //case, we should re-arm the endpoint, so we can receive the next CBW.
                if((USB_HANDLE)pdata == USBGetNextHandle(MSD_DATA_OUT_EP, OUT_FROM_HOST))
                {
                    USBMSDOutHandle = USBRxOnePacket(MSD_DATA_OUT_EP, (BYTE*)&msd_cbw, MSD_OUT_EP_SIZE);
                }    
            }    
            break;
        default:
            break;
    }      
    return TRUE; 
}
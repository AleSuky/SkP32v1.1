#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "LCDTFT.h"
// *--------------------------------------------------------------------------------*
const UINT16 Colores[]={ColorBlack, ColorBlue, ColorRed, ColorGreen, ColorYellow, ColorFuchsia};
// *--------------------------------------------------------------------------------*
void vADC_Init(void);
UINT16 ADC_Conversion(void);
// *--------------------------------------------------------------------------------*
int main(){
	UINT8 k=0;
	UINT16 Conversion;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED3_OUTPUT();
	LED4_OUTPUT();
	SW1_INPUT();
	SW2_INPUT();
	
	PORTSetPinsDigitalOut(IOPORT_D, BIT_1);		// Backlight del TFT
	mPORTDSetBits(BIT_1);
	vLCDTFTInit();
	vLCDTFTFillScreen(ColorWhite);
	vADC_Init();
	while(1){
		if(SW1_STATUS()==0){
			vLCDTFTRectangle(0,0,200,319,1,Colores[k]);
			if(++k==6){k=0;}
			DelayMs(250);
		}
		if(SW2_STATUS()==0){
			LED2_TOGGLE();
			LED4_TOGGLE();
			DelayMs(250);
		}
		Conversion=ADC_Conversion();
		vLCDTFTRectangle(201,0,239,319,1,ColorWhite);
		// 1023 -> 0; 0 -> 239
		vLCDTFTRectangle(202,((-0.31183*Conversion)+319.0),238,319,1,ColorRed);
		DelayMs(50);
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
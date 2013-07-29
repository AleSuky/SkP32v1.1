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
#include "Player.h"
// *--------------------------------------------------------------------------------*
// *--------------------------------------------------------------------------------*
// *--------------------------------------------------------------------------------*
int main(){
	int frames;
	short x2,y2,x1,y1,k;

    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	PORTSetPinsDigitalOut(IOPORT_D, BIT_1);		// Backlight del TFT
	mPORTDSetBits(BIT_1);
	vInitPlayer();
	
	PORTSetPinsDigitalOut(PORT_LED1, PIN_LED1);
	PORTSetPinsDigitalOut(PORT_LED2, PIN_LED2);
	PORTClearBits(PORT_LED2,PIN_LED2);
	
	vLCDTFTText(80,50,"SkP32",ARIAL,3,ColorNaranja);
	vLCDTFTText(37,80,"Reproductor AVI",ARIAL,2,ColorYellow);
	vLCDTFTText(7,100,"micros-designs.com.ar",ARIAL,2,ColorYellow);	 
	vLCDTFTText(59,150,"Referencia:",ARIAL,2,ColorAqua);
	vLCDTFTText(21,170,"exploringpic32.com",ARIAL,2,ColorAqua);	
	DelayMs(2000);
	x1=120;y1=120;
	x2=120;y2=200;
	for(k=0;k<119;k++){
		vLCDTFTRectangle(x1,y1,x2,y2,0,ColorPurple);
		x1--;y1--;
		x2++;y2++;
		DelayMs(2);
	}
	DelayMs(300);
	while(1){
		if(PlayAVI("VIDEO1.AVI")<0){
			vLCDTFTText(80,50,"Error",ARIAL,3,ColorNaranja);
		}else{
			vLCDTFTFillScreen(ColorBlue);
			DelayMs(500);
		}
	}
}
// *--------------------------------------------------------------------------------*

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
// *--------------------------------------------------------------------------------*

// *--------------------------------------------------------------------------------*
int main(){
	UINT8 StatusMemory=0, Data;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED3_OUTPUT();
	LED4_OUTPUT();
	
	LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();
	
	SW1_INPUT();
	SW2_INPUT();
	
	vInitMemoryFM25L16();
	DelayMs(300);
	
	vEnableWriteMemoryFM25L16();
	StatusMemory=ui8ReadStateMemoryFM25L16();
	if(StatusMemory!=0x02){
		LED1_TOGGLE();
	}else{
		LED2_TOGGLE(); // ok
	}
	vWriteSingleMemoryFM25L16(100,0xA5);
	DelayMs(1);
	Data=ui8ReadSingleMemoryFM25L16(100);
	if(Data!=0xA5){
		LED3_TOGGLE();
	}else{
		LED4_TOGGLE();
	}
	while(1){
	}
}

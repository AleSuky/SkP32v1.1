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
// *--------------------------------------------------------------------------------*

// *--------------------------------------------------------------------------------*
int main(){
	UINT16 Count;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED3_OUTPUT();
	LED4_OUTPUT();
	
	LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();
	
	OpenTimer2(T2_ON | T2_PS_1_1 |  T2_SOURCE_INT, 16000); // 1.3k
	OpenOC1(OC_ON | OC_TIMER2_SRC | OC_TIMER_MODE16 | OC_PWM_FAULT_PIN_DISABLE, 8000, 16000); // RD0
	
	SW1_INPUT();
	SW2_INPUT();
	while(1){
		if(SW1_STATUS()==0){
			LED1_TOGGLE();
			LED3_TOGGLE();
			DelayMs(200);
		}
		if(SW2_STATUS()==0){
			LED2_TOGGLE();			
			DelayMs(200);
		}
		if(++Count==0){
			LED4_TOGGLE();
		}
	}
}

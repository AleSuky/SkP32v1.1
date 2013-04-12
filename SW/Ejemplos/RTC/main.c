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
// *--------------------------------------------------------------------------------*
volatile char kbhit_rtc=0;
// *---------------------------------------------------------------------------*
void __ISR(_RTCC_VECTOR, ipl4) RtccIsr(void){
	
	INTClearFlag(INT_RTCC);
	kbhit_rtc=1;
}
// *--------------------------------------------------------------------------------*
int main(){
	rtccTime	tm,A_tm;		
	rtccDate	dt,A_dt;
		
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	RtccInit();			
	while(RtccGetClkStat()!=RTCC_CLK_ON);
	
	tm.l=0;
	tm.sec=0x30;
	tm.min=0x07;
	tm.hour=0x15;
	dt.wday=2;
	dt.mday=0x19;
	dt.mon=0x07;
	dt.year=0x12;
	
	A_tm=tm;
	A_dt=dt;
	A_tm.sec+=1;
	RtccChimeEnable();			
	RtccSetAlarmRptCount(0);		
	RtccSetAlarmRpt(RTCC_RPT_SEC);			// Cada 1 seg.
	RtccAlarmEnable();
	RtccSetTimeDate(tm.l, dt.l);
	
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();
	INTSetVectorPriority(INT_RTCC_VECTOR, INT_PRIORITY_LEVEL_4);			
	INTSetVectorSubPriority(INT_RTCC_VECTOR, INT_SUB_PRIORITY_LEVEL_1);		
	INTEnable(INT_RTCC, INT_ENABLED);
	
	LED1_OUTPUT();
	while(1){
		if(kbhit_rtc==1){
			kbhit_rtc=0;
			RtccGetTimeDate(&tm, &dt);
			LED1_TOGGLE();
		}	
	}
}

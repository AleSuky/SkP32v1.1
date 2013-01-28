#include "../Include/Ticker.h"

TICKER Tickers[MAX_TICKERS];
UINT8 CountTickers=0;

// *--------------------------------------------------------------------------------*
void __ISR(_TIMER_4_VECTOR, ipl2) Timer4Handler(void){
    
    vISRTimerTickers();
    mT4ClearIntFlag();
}

void vInitTicker(UINT16 ms){
	UINT8 k;
	UINT32 Cycles=GetSystemClock()/1000;
	
	Cycles*=ms;
	if(Cycles<65536){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_1 | T4_SOURCE_INT, Cycles);
	}else if(Cycles<131072){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_2 | T4_SOURCE_INT, (Cycles/2));
	}else if(Cycles<262144){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_4 | T4_SOURCE_INT, (Cycles/4));
	}else if(Cycles<524288){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_8 | T4_SOURCE_INT, (Cycles/8));
	}else if(Cycles<1048576){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_16 | T4_SOURCE_INT, (Cycles/16));
	}else if(Cycles<2097152){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_32 | T4_SOURCE_INT, (Cycles/32));
	}else if(Cycles<4194304){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_64 | T4_SOURCE_INT, (Cycles/64));
	}else if(Cycles<16777216){
		OpenTimer4(T4_ON | T4_IDLE_STOP | T4_GATE_OFF | T4_PS_1_256 | T4_SOURCE_INT, (Cycles/256));
	}
	
	for(k=0;k<MAX_TICKERS;k++){
		Tickers[k].Enabled=0x00;
	}
	CountTickers=0;
	
	TMR4=0;
	ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_2);
	
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}	

TMRTICK tmr_AttachTicker(UINT32 Count,void (*fptr)(void),BOOL *Flag){
	UINT8 k;

	if(CountTickers<MAX_TICKERS){
		for(k=0;k<MAX_TICKERS;k++){
			if(Tickers[k].Enabled==0x00){
				Tickers[k].Enabled=0x01;
				Tickers[k].Load=Count;
				Tickers[k].Count=Count;
				Tickers[k].fptr=fptr;
				Tickers[k].Flag=Flag;
				if(Flag!=NULL){*Flag=0;}
				break;
			}
		}
		CountTickers++;
		return(k);
	}
	return(-1);
} 

void vDetachTicker(TMRTICK tmr){

	if(tmr!=-1){
		Tickers[tmr].Enabled=0x00;
		CountTickers--;
	}	
}
void vResetTickers(TMRTICK tmr){

    Tickers[tmr].Count=Tickers[tmr].Load;
}

void vISRTimerTickers(void){
	UINT8 k;
	
	for(k=0;k<MAX_TICKERS;k++){
		if((Tickers[k].Enabled==0x01)&&(--Tickers[k].Count==0)){
			Tickers[k].Count=Tickers[k].Load;
			if(Tickers[k].fptr!=NULL){
				Tickers[k].fptr();
			}else{
				*Tickers[k].Flag=1;
			}
		}		
	}
}	


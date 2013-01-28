#ifndef _TICKER_H_
#define _TICKER_H_

#include <p32xxxx.h>
#include <plib.h>
#include "HardwareProfile.h"

#define MAX_TICKERS 		15
typedef struct{
	UINT32 Count;
	UINT32 Load;
	UINT8 Enabled;
	void (*fptr)(void);
	BOOL *Flag;
}TICKER;
typedef char TMRTICK;

void vInitTicker(UINT16 ms);
TMRTICK tmr_AttachTicker(UINT32 Count,void (*fptr)(void),BOOL *Flag);
void vDetachTicker(TMRTICK tmr);
void vResetTickers(TMRTICK tmr);
void vISRTimerTickers(void);

#endif

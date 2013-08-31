/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
static USHORT usTim1Timerout50usCpy;
/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    usTim1Timerout50usCpy=usTim1Timerout50us;
    mT2SetIntPriority(2);
    return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
    WriteTimer2(0);
    OpenTimer2(T2_ON | T2_PS_1_8 |  T2_SOURCE_INT, ((GetPeripheralClock()/2)/(80000/usTim1Timerout50usCpy))-1);
    mT2ClearIntFlag();
    mT2IntEnable(1);
    INTEnableSystemMultiVectoredInt();
}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
    CloseTimer2();
    mT2IntEnable(0);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void __ISR(_TIMER_2_VECTOR, ipl2 ) ISR_T2(void){

    mT2ClearIntFlag();
    ( void )pxMBPortCBTimerExpired(  );
}


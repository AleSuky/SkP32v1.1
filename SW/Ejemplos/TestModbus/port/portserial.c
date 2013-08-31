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
 * File: $Id: portserial.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
    if(xRxEnable==TRUE){
        INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
    }else{
        INTEnable(INT_SOURCE_UART_RX(UART2), INT_DISABLED);
    }

    if(xTxEnable==TRUE){
        INTEnable(INT_SOURCE_UART_TX(UART2), INT_ENABLED);
    }else{
        INTEnable(INT_SOURCE_UART_TX(UART2), INT_DISABLED);
    }

}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    (void)ucPORT;
    (void)ucDataBits;
    (void)eParity;
    UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY); // Habilita pines Tx y Rx.
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY); // INT_Tx cuando el buffer tiene espacio para otro caracter.
    																						// INT_Rx cuando el buffer tiene un byte.
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);	// 8:N:1
    UARTSetDataRate(UART2, GetPeripheralClock(), ulBaudRate);								// 19200
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));				// Modulo encedido, Tx y Rx encendido

    INTSetVectorPriority(INT_UART_2_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_UART_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
    return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
    while(!UARTTransmitterIsReady(UART2));
    UARTSendDataByte(UART2, ucByte);
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
    //while(UARTReceivedDataIsAvailable(UART2)==FALSE);
    *pucByte=UARTGetDataByte(UART2);
    return TRUE;
}

void __ISR(_UART2_VECTOR, ipl2) ISRUart2(void){
    
	if(INTGetFlag(INT_SOURCE_UART_RX(UART2))){
	    INTClearFlag(INT_SOURCE_UART_RX(UART2));            
            pxMBFrameCBByteReceived(  );
	}
	/*if(INTGetFlag(INT_SOURCE_UART_TX(UART2))){
            INTClearFlag(INT_SOURCE_UART_TX(UART2));
            LED4_TOGGLE();
            pxMBFrameCBTransmitterEmpty(  );
	}*/
}

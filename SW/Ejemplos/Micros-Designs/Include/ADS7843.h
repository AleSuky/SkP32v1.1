/**
   \version: 1.0

   
   \author Suky
   \web www.micros-designs.com.ar
   \date 19/11/11


///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2011 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
/////////////////////////////////////////////////////////////////////////// 
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 19/11/11      Suky               Original (Rev 1.0)                        *
 *----------------------------------------------------------------------------* */
#ifndef _ADS7843_H_
	#define _ADS7843_H_

#include <p32xxxx.h>
#include <plib.h>
#include "GenericTypeDefs.h"
#include "TimeDelay.h"

#define ADS7843_PIN_CS		LATCbits.LATC2 	// Salida
#define ADS7843_PIN_IRQ		PORTAbits.RA14	// Entrada
#define ADS7843_PIN_CLK		LATCbits.LATC1	// Salida
#define ADS7843_PIN_SDO		PORTCbits.RC4	// Entrada
#define ADS7843_PIN_SDI		LATCbits.LATC3	// Salida
 
#define ADS7843_TRIS_CS		TRISCbits.TRISC2
#define ADS7843_TRIS_IRQ	TRISAbits.TRISA14
#define ADS7843_TRIS_CLK	TRISCbits.TRISC1
#define ADS7843_TRIS_SDO	TRISCbits.TRISC4
#define ADS7843_TRIS_SDI	TRISCbits.TRISC3
 
#define __delay_CLK_ADS7843()	{Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();\
								Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();} // 1uS -> 80 MHz

typedef	UINT16					UINT_COORDxy; 

#define ADS7843_USE_12BITS

#if defined(ADS7843_USE_12BITS)
	#define ADS7843_READ_X		0b10010000 // IRQ Enable
	#define ADS7843_READ_Y		0b11010000	
#else
	#define ADS7843_READ_X		0b10011000 // IRQ Enable	 
	#define ADS7843_READ_Y		0b11011000
#endif
 
#define PIN_INPUT	1
#define PIN_OUTPUT	0
 
typedef struct{
	UINT_COORDxy	x;
	UINT_COORDxy	y;
}TOUCH_DATA;
 
 
void vInitADS7843(void);
UINT_COORDxy ADS7843WriteAndReadData(UINT8);
void vTestTouchPanel(TOUCH_DATA *Data);
#endif

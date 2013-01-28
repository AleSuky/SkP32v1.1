/**
   \version: 1.0

   
   \author Suky (Casanova Alejandro) 
   \web www.micros-designs.com.ar
   \date 14/09/10


///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2010 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
/////////////////////////////////////////////////////////////////////////// 
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 16/08/10      Suky               Original (Rev 1.0)                        *
 * 20/08/10      Suky               Se incluye CodeVisionAVR                  *
 *----------------------------------------------------------------------------* 
  Se puede seleccionar entre 3 modos de trabajo siempre configurando al LCD
 en modo 4-bits:
 Modo normal con control sobre RW  -> RS | RW | E ... LCD4 | LCD5 | LCD6 | LCD7
 Modo sin control sobre RW -> RS | E ... LCD4 | LCD5 | LCD6 | LCD7
 Modo 3 pines, sin control sobre RW -> E ... SERIAL_DATA | SERIAL_CLK
                                 LCD4-> REGISTRO_DESPLAZAMIENTO_D0
                                 LCD5-> REGISTRO_DESPLAZAMIENTO_D1
                                 LCD6-> REGISTRO_DESPLAZAMIENTO_D2
                                 LCD7-> REGISTRO_DESPLAZAMIENTO_D3
                                 RS-> REGISTRO_DESPLAZAMIENTO_D4

 Además permite la configuración entre: 1 linea 5x7, 1 linea 5x10 o varias lineas 5x7.
 Y entre LCD de 2 lineas o 4 lineas, configurando las direcciones de las lineas.-  
  *----------------------------------------------------------------------------**/
 
#ifndef __LCD_GENERIC_H_
#define __LCD_GENERIC_H_

#include "GenericTypeDefs.h"
#if defined(__PIC32MX__)
	#include "TimeDelay.h" 
#endif

/* ****************************************************************************************************** */
/* **  DEFINICION PARA INICIALIZACIÖN DEL LCD ** */
#define LcdType 2 			// 0=5x7, 1=5x10, 2=varias lineas

/* ** DEFINICION PARA TRABAJAR CON LCD DE 2 LINEAS o 4 LINEAS** */
#define LCD_4LINES

/* ** DEFINICIONES DE DIRECCIONAMIENTO DE LINEAS EN LCD ** */
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x40
#if defined(LCD_4LINES)
	#define LCD_LINE_3_ADDRESS 0x14
	#define LCD_LINE_4_ADDRESS 0x54
#endif
/* ** *************************************************** ** */
#define LCD_COMMAND	0
#define LCD_DATA	1

/* ** Para no utilizar el PIN RW comentar la siguiente definición ** */
//#define LCD_USE_RW 
/* ** El siguiente modo no utiliza el PIN RW** */
#define LCD_USE_3PINES		// Se utiliza registro de desplazamiento para DATA[0..3] y RS.
#if defined(LCD_USE_3PINES) && defined(LCD_USE_RW)
	#undef LCD_USE_RW
#endif

/* ************************** MPLAB C18, MPLAB C30 **************************************** */
#if defined(__18CXX) || defined (__C30__) || defined (__PIC32MX__)

	#if defined(__18CXX)
		#include <p18cxxx.h>
   	#include <delays.h>
		#define	__delay_1Cycle()	Nop()
		#define __delay_1us()		{Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}
		#define __delay_100us()		Delay100TCYx(FCY/4000000UL)
		#define __delay_2ms() 		Delay1KTCYx(FCY/2000000UL)
	#endif 
	
	#if defined (__C30__) 				// C30
		#if defined(__dsPIC30F__)
			#include <p30fxxxx.h>
		#elif defined(__dsPIC33F__)
			#include <p33Fxxxx.h>
		#elif defined(__PIC24H__)
			#include <p24Hxxxx.h>
		#elif defined(__PIC24F__)
			#include <p24Fxxxx.h>
		#endif
		#include <libpic30.h>
		#define	__delay_1Cycle()	Nop()
		#define __delay_1us()		__delay_us(1)
		#define __delay_100us()		__delay_us(100)
		#define __delay_2ms() 		__delay_ms(2)
	#endif
	
	#if defined (__PIC32MX__)
		#include <p32xxxx.h>
		#define	__delay_1Cycle()	{Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();}
		#define __delay_1us()		{UINT8 k; for(k=0;k<50;k++){Nop();}}
		#define __delay_100us()		Delay10us(10)
		#define __delay_2ms() 		DelayMs(2)
	#endif
    
    #define CONFIG_INPUT    1
    #define CONFIG_OUTPUT   0
	
	#ifndef LCD_USE_3PINES
		/* ** Pines tolerables a 5V para usar RW ** */
		#define LCD_DATA_PIN_7 	LATBbits.LATB7
		#define LCD_DATA_PIN_6 	LATBbits.LATB6
		#define LCD_DATA_PIN_5 	LATBbits.LATB5
		#define LCD_DATA_PIN_4 	LATBbits.LATB4
		
		#define LCD_READ_PIN_7	PORTBbits.RB7
		#define LCD_READ_PIN_6	PORTBbits.RB6
		#define LCD_READ_PIN_5	PORTBbits.RB5
		#define LCD_READ_PIN_4	PORTBbits.RB4
		
		
		#define LCD_TRIS_DATA_PIN_7       TRISBbits.TRISB7
		#define LCD_TRIS_DATA_PIN_6       TRISBbits.TRISB6
		#define LCD_TRIS_DATA_PIN_5       TRISBbits.TRISB5
		#define LCD_TRIS_DATA_PIN_4       TRISBbits.TRISB4
		
		
		#define LCD_E_PIN	LATBbits.LATB2 
		#define LCD_RS_PIN	LATBbits.LATB0 
		#ifdef LCD_USE_RW
			#define LCD_RW_PIN	LATBbits.LATB1 
		#endif
		
		#define LCD_TRIS_E	TRISBbits.TRISB2 
		#define LCD_TRIS_RS	TRISBbits.TRISB0  
		#ifdef LCD_USE_RW 
			#define LCD_TRIS_RW	TRISBbits.TRISB1 
		#endif 
	#else
		#define LCD_DATA_PIN  	LATEbits.LATE2
		#define LCD_CLOCK_PIN 	LATEbits.LATE3
		#define LCD_E_PIN	LATEbits.LATE4	
	
		#define LCD_TRIS_DATA	TRISEbits.TRISE2
		#define LCD_TRIS_CLOCK	TRISEbits.TRISE3
		#define LCD_TRIS_E	TRISEbits.TRISE4
	#endif
#endif
/* ********************************** C COMPILER CCS ********************************************* */
#if defined(__PCH__) || defined(__PCM__)
	
	#define __delay_1Cycle()	delay_cycles(1)
	#define __delay_1us()		delay_us(1)
	#define __delay_100us()		delay_us(100)
	#define __delay_2ms() 		delay_ms(2)
    
    #define CONFIG_INPUT    1
    #define CONFIG_OUTPUT   0

	#ifndef LCD_USE_3PINES
	   #if defined(__PCH__) // PIC18F
		   #bit LCD_DATA_PIN_7=GETENV("SFR:LATB").7
		   #bit LCD_DATA_PIN_6=GETENV("SFR:LATB").6
		   #bit LCD_DATA_PIN_5=GETENV("SFR:LATB").5
		   #bit LCD_DATA_PIN_4=GETENV("SFR:LATB").4
	   #else				// PIC16F
		   #bit LCD_DATA_PIN_7=GETENV("SFR:PORTB").7
		   #bit LCD_DATA_PIN_6=GETENV("SFR:PORTB").6
		   #bit LCD_DATA_PIN_5=GETENV("SFR:PORTB").5
		   #bit LCD_DATA_PIN_4=GETENV("SFR:PORTB").4
	   #endif
	   
	   #bit LCD_READ_PIN_7=GETENV("SFR:PORTB").7
	   #bit LCD_READ_PIN_6=GETENV("SFR:PORTB").6
	   #bit LCD_READ_PIN_5=GETENV("SFR:PORTB").5
	   #bit LCD_READ_PIN_4=GETENV("SFR:PORTB").4
	   
	   #bit LCD_TRIS_DATA_PIN_7=GETENV("SFR:TRISB").7
	   #bit LCD_TRIS_DATA_PIN_6=GETENV("SFR:TRISB").6
	   #bit LCD_TRIS_DATA_PIN_5=GETENV("SFR:TRISB").5
	   #bit LCD_TRIS_DATA_PIN_4=GETENV("SFR:TRISB").4
	   
	   #if defined(__PCH__) // PIC18F
		   #bit LCD_E_PIN=GETENV("SFR:LATB").2
		   #bit LCD_RS_PIN=GETENV("SFR:LATB").0
		   #ifdef LCD_USE_RW
		   		#bit LCD_RW_PIN=GETENV("SFR:LATB").1
		   #endif 
		#else				// PIC16F
			#bit LCD_E_PIN=GETENV("SFR:PORTB").2
		   #bit LCD_RS_PIN=GETENV("SFR:PORTB").0
		   #ifdef LCD_USE_RW
		   		#bit LCD_RW_PIN=GETENV("SFR:PORTB").1
		   #endif 
		#endif
	   
		#bit LCD_TRIS_E=GETENV("SFR:TRISB").2
		#bit LCD_TRIS_RS=GETENV("SFR:TRISB").0
		#ifdef LCD_USE_RW
			#bit LCD_TRIS_RW=GETENV("SFR:TRISB").1
		#endif
	#else
		#if defined(__PCH__) // PIC18F
		   #bit LCD_DATA_PIN=GETENV("SFR:LATB").4
		   #bit LCD_CLOCK_PIN=GETENV("SFR:LATB").5
		   #bit LCD_E_PIN=GETENV("SFR:LATB").6
	   #else				// PIC16F
		   #bit LCD_DATA_PIN=GETENV("SFR:PORTB").4
		   #bit LCD_CLOCK_PIN=GETENV("SFR:PORTB").5
		   #bit LCD_E_PIN=GETENV("SFR:PORTB").6
	   #endif
	   
	   #bit LCD_TRIS_DATA=GETENV("SFR:TRISB").4
	   #bit LCD_TRIS_CLOCK=GETENV("SFR:TRISB").5
	   #bit LCD_TRIS_E=GETENV("SFR:TRISB").6
	#endif
#endif
/* ********************************** HI-TECH C ********************************************* */
#if defined(HI_TECH_C)
	   
	#define _XTAL_FREQ 20000000
	#include <htc.h>

	#define __delay_1Cycle()	asm("nop")
	#define __delay_1us()		__delay_us(1)
	#define __delay_100us()		__delay_us(100)
	#define __delay_2ms() 		__delay_ms(2)
	
    #define CONFIG_INPUT    1
    #define CONFIG_OUTPUT   0
	
	#ifndef LCD_USE_3PINES
		#if defined(__PICC18__)
			#define LCD_DATA_PIN_7 	LATB7
			#define LCD_DATA_PIN_6 	LATB6
			#define LCD_DATA_PIN_5 	LATB5
			#define LCD_DATA_PIN_4 	LATB4
		#else
			#define LCD_DATA_PIN_7 	RB7
			#define LCD_DATA_PIN_6 	RB6
			#define LCD_DATA_PIN_5 	RB5
			#define LCD_DATA_PIN_4 	RB4
		#endif
		
		#define LCD_READ_PIN_7	RB7
		#define LCD_READ_PIN_6	RB6
		#define LCD_READ_PIN_5	RB5
		#define LCD_READ_PIN_4	RB4
		
		
		#define LCD_TRIS_DATA_PIN_7       TRISB7
		#define LCD_TRIS_DATA_PIN_6       TRISB6
		#define LCD_TRIS_DATA_PIN_5       TRISB5
		#define LCD_TRIS_DATA_PIN_4       TRISB4
		
		#if defined(__PICC18__)
			#define LCD_E_PIN	LATB2 
			#define LCD_RS_PIN	LATB0 
			#ifdef LCD_USE_RW
				#define LCD_RW_PIN	LATB1 
			#endif
		#else
			#define LCD_E_PIN	RB2 
			#define LCD_RS_PIN	RB0 
			#ifdef LCD_USE_RW
				#define LCD_RW_PIN	RB1 
			#endif
		#endif
		
		#define LCD_TRIS_E	TRISB2 
		#define LCD_TRIS_RS	TRISB0  
		#ifdef LCD_USE_RW 
			#define LCD_TRIS_RW	TRISB1 
		#endif 
	#else
		#if defined(__PICC18__)
			#define LCD_DATA_PIN  LATB4
			#define LCD_CLOCK_PIN LATB5
			#define LCD_E_PIN	  LATB6
		#else
			#define LCD_DATA_PIN  RB4
			#define LCD_CLOCK_PIN RB5
			#define LCD_E_PIN	  RB6
		#endif
	
		#define LCD_TRIS_DATA	TRISB4
		#define LCD_TRIS_CLOCK	TRISB5
		#define LCD_TRIS_E		TRISB6
	#endif

#endif

/* ********************************* CODEVISION AVR ******************************************* */
#if defined(__CODEVISIONAVR__ )
    #include <io.h>
    #include <delay.h>
    
    #define __delay_1Cycle()	{#asm("nop")}
	#define __delay_1us()		delay_us(1)
	#define __delay_100us()		delay_us(100)
	#define __delay_2ms() 		delay_ms(2)
    
    #define CONFIG_INPUT    0
    #define CONFIG_OUTPUT   1
    
    #ifndef LCD_USE_3PINES

    	#define LCD_DATA_PIN_7 	PORTB.7
		#define LCD_DATA_PIN_6 	PORTB.6
		#define LCD_DATA_PIN_5 	PORTB.5
		#define LCD_DATA_PIN_4 	PORTB.4

		
		#define LCD_READ_PIN_7	PINB.7
		#define LCD_READ_PIN_6	PINB.6
		#define LCD_READ_PIN_5	PINB.5
		#define LCD_READ_PIN_4	PINB.4
		
		
		#define LCD_TRIS_DATA_PIN_7       DDRB.7
		#define LCD_TRIS_DATA_PIN_6       DDRB.6
		#define LCD_TRIS_DATA_PIN_5       DDRB.5
		#define LCD_TRIS_DATA_PIN_4       DDRB.4
		
		#define LCD_E_PIN	PORTB.2 
		#define LCD_RS_PIN	PORTB.0 
		#ifdef LCD_USE_RW
			#define LCD_RW_PIN	PORTB.1 
		#endif
		
		#define LCD_TRIS_E	DDRB.2 
		#define LCD_TRIS_RS	DDRB.0  
		#ifdef LCD_USE_RW 
			#define LCD_TRIS_RW	DDRB.1 
		#endif 
	#else
		#define LCD_DATA_PIN  PORTB.4
		#define LCD_CLOCK_PIN PORTB.5
		#define LCD_E_PIN	  PORTB.6

	
		#define LCD_TRIS_DATA	DDRB.4
		#define LCD_TRIS_CLOCK	DDRB.5
		#define LCD_TRIS_E		DDRB.6
	#endif

#endif

UINT8 ui8BusyLCD(void);
void vWriteLCD(UINT8 Data,UINT8 Type);
void vInitLCD(void);
void vLCD_Putc(UINT8 Data);
void vGotoxyLCD(UINT8 x,UINT8 y);
void vPuts_LCD(UINT8 *buffer);
void vPutrs_LCD(const UINT8 *buffer);

#endif

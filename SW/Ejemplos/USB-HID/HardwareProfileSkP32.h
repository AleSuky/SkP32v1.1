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
 
#define PORT_LED1 	IOPORT_B
#define PIN_LED1	BIT_8
#define PORT_LED2 	IOPORT_B
#define PIN_LED2	BIT_9
#define PORT_LED3 	IOPORT_B
#define PIN_LED3	BIT_10
#define PORT_LED4 	IOPORT_B
#define PIN_LED4	BIT_11

#define PORT_SW1	IOPORT_B
#define PIN_SW1		BIT_12
#define PORT_SW2	IOPORT_B
#define PIN_SW2		BIT_13

#define LED1_READ()		PORTBbits.RB8
#define LED2_READ()		PORTBbits.RB9
#define LED3_READ()		PORTBbits.RB10
#define LED4_READ()		PORTBbits.RB11

#define LED1_OUTPUT()   PORTSetPinsDigitalOut(PORT_LED1, PIN_LED1);
#define LED2_OUTPUT()   PORTSetPinsDigitalOut(PORT_LED2, PIN_LED2);
#define LED3_OUTPUT()   PORTSetPinsDigitalOut(PORT_LED3, PIN_LED3);
#define LED4_OUTPUT()   PORTSetPinsDigitalOut(PORT_LED4, PIN_LED4);

#define LED1_ON()       PORTSetBits(PORT_LED1, PIN_LED1);
#define LED2_ON()       PORTSetBits(PORT_LED2, PIN_LED2);
#define LED3_ON()       PORTSetBits(PORT_LED3, PIN_LED3);
#define LED4_ON()       PORTSetBits(PORT_LED4, PIN_LED4);

#define LED1_OFF()      PORTClearBits(PORT_LED1, PIN_LED1);
#define LED2_OFF()      PORTClearBits(PORT_LED2, PIN_LED2);
#define LED3_OFF()      PORTClearBits(PORT_LED3, PIN_LED3);
#define LED4_OFF()      PORTClearBits(PORT_LED4, PIN_LED4);

#define LED1_TOGGLE()   PORTToggleBits(PORT_LED1, PIN_LED1);
#define LED2_TOGGLE()   PORTToggleBits(PORT_LED2, PIN_LED2);
#define LED3_TOGGLE()   PORTToggleBits(PORT_LED3, PIN_LED3);
#define LED4_TOGGLE()   PORTToggleBits(PORT_LED4, PIN_LED4);

#define SW1_INPUT()     PORTSetPinsDigitalIn(PORT_SW1, PIN_SW1)
#define SW2_INPUT()     PORTSetPinsDigitalIn(PORT_SW2, PIN_SW2)

#define SW1_STATUS()    PORTReadBits(PORT_SW1,PIN_SW1)
#define SW2_STATUS()    PORTReadBits(PORT_SW2,PIN_SW2)

#define GetSystemClock()		(80000000ul)		// Hz
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/1)

//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2    // Input
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
#define USB_BUS_SENSE       1 
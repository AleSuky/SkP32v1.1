/**
   \version: 1.0
   
   \author Suky. 
   \web www.micros-designs.com.ar 
   \date 27/11/11
   
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2011 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

*- Version Log --------------------------------------------------------------_*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 27/11/11      Suky     Original (Rev 1.0)                                  *
 *----------------------------------------------------------------------------*
*/
#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_


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

#define GetSystemClock()		(80000000ul)			// Hz
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/1)

#define MILLISECONDS_PER_TICK       10                  // Definition for use with a tick timer
#define TIMER_PRESCALER             TIMER_PRESCALER_8   // Definition for use with a tick timer
#define TIMER_PERIOD                37500               // Definition for use with a tick timer

// Description: Macro used to enable the SD-SPI physical layer (SD-SPI.c and .h)
#define USE_SD_INTERFACE_WITH_SPI

#ifdef USE_SD_INTERFACE_WITH_SPI

	//SPI Configuration
	#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
	#define SPI_START_CFG_2     (SPI_ENABLE)
	
	// Define the SPI frequency
	#define SPI_FREQUENCY			(20000000)
	
	// Description: SD-SPI Chip Select Output bit
	#define SD_CS               LATAbits.LATA4
	// Description: SD-SPI Chip Select TRIS bit
	#define SD_CS_TRIS          TRISAbits.TRISA4
	
	// Description: SD-SPI Card Detect Input bit
	#define SD_CD               PORTGbits.RG9
	// Description: SD-SPI Card Detect TRIS bit
	#define SD_CD_TRIS          TRISGbits.TRISG9
	
	// Description: SD-SPI Write Protect Check Input bit
	//#define SD_WE               PORTGbits.RG1
	// Description: SD-SPI Write Protect Check TRIS bit
	//#define SD_WE_TRIS          TRISGbits.TRISG1
	
	// Description: The main SPI control register
	#define SPICON1             SPI2CON
	// Description: The SPI status register
	#define SPISTAT             SPI2STAT
	// Description: The SPI Buffer
	#define SPIBUF              SPI2BUF
	// Description: The receive buffer full bit in the SPI status register
	#define SPISTAT_RBF         SPI2STATbits.SPIRBF
	// Description: The bitwise define for the SPI control register (i.e. _____bits)
	#define SPICON1bits         SPI2CONbits
	// Description: The bitwise define for the SPI status register (i.e. _____bits)
	#define SPISTATbits         SPI2STATbits
	// Description: The enable bit for the SPI module
	#define SPIENABLE           SPI2CONbits.ON
	// Description: The definition for the SPI baud rate generator register (PIC32)
	#define SPIBRG			    SPI2BRG
	
	// Tris pins for SCK/SDI/SDO lines
	
	// Description: The TRIS bit for the SCK pin
	#define SPICLOCK            TRISGbits.TRISG6
	// Description: The TRIS bit for the SDI pin
	#define SPIIN               TRISGbits.TRISG7
	// Description: The TRIS bit for the SDO pin
	#define SPIOUT              TRISGbits.TRISG8
	//SPI library functions
	#define putcSPI             putcSPI2
	#define getcSPI             getcSPI2
	#define OpenSPI(config1, config2)   OpenSPI2(config1, config2)
	
	#define USE_MDD_32   // 32-bits SPI para lectura sector.
#endif

//#include <uart2.h>

#endif

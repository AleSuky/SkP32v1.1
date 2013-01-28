/* 
   \file FM25L16.h  
   \version 1.1 
   
   \author Suky. 
   \web www.micros-designs.com.ar
   \date 06/10/11  
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 06/10/11      Suky         Original (Rev 1.0)                              *
 * 24/07/12		 Suky		  Para C32
 *----------------------------------------------------------------------------* */
#ifndef _FM25L16_H
    #define _FM25L16_H
    
#include <p32xxxx.h>
#include <plib.h>    
#include "GenericTypeDefs.h"
#include "TimeDelay.h" 
#include "HardwareProfile.h"


/************************************************************************
* FM25H20 Commandos                                                       
************************************************************************/
#define MEMORY_SPI_READ				0x03
#define MEMORY_SPI_WRITE			0x02
#define MEMORY_SPI_ENABLE_W			0x06
#define MEMORY_SPI_DISABLE_W		0x04
#define MEMORY_SPI_READ_STATUS		0x05
#define MEMORY_SPI_WRITE_STATUS		0x01


void vInitMemoryFM25L16(void);

void vEnableWriteMemoryFM25L16(void);

UINT8 ui8ReadStateMemoryFM25L16(void);

void vWriteSingleMemoryFM25L16(UINT16 Address,UINT8 Data);

UINT8 ui8ReadSingleMemoryFM25L16(UINT16 Address);

void vWritePageMemoryFM25L16(UINT16 Address,UINT16 Length,UINT8 *Data);

void vReadPageMemoryFM25L16(UINT16 Address,UINT16 Length,UINT8 *Data);

#endif 
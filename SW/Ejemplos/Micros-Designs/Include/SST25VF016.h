/* 
   \file SST25VF016.c  
   \version 1.1 
   
   \author Suky. 
   \web www.micros-designs.com.ar
   \date 06/10/11  
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 06/10/11      Suky         Original (Rev 1.0)                              *
 * 06/12/11		 Suky		  Para C32
 *----------------------------------------------------------------------------* */
#ifndef _SST25VF016_H
    #define _SST25VF016_H
    
#include <p32xxxx.h>
#include <plib.h>    
#include "GenericTypeDefs.h"
#include "TimeDelay.h" 
#include "HardwareProfileSkP32.h"

/************************************************************************
* SST25 Commandos                                                       
************************************************************************/
#define SST25_CMD_READ  (unsigned)0x03
#define SST25_CMD_READH (unsigned)0x0B
#define SST25_CMD_WRITE (unsigned)0x02
#define SST25_CMD_WREN  (unsigned)0x06
#define SST25_CMD_RDSR  (unsigned)0x05
#define SST25_CMD_ERASE (unsigned)0x60
#define SST25_CMD_EWSR  (unsigned)0x50
#define SST25_CMD_WRSR  (unsigned)0x01
#define SST25_CMD_SER   (unsigned)0x20


void vSST25Init(void);
UINT8 uiSST25IsWriteBusy(void);
void vSST25WriteByte(UINT8 data, UINT32 address);
UINT8 uiSST25ReadByte(UINT32 address);
void vSST25WriteEnable(void);
void vSST25ChipErase(void);
void vSST25ResetWriteProtection(void);
void vSST25SectorErase(UINT32 address);

void vSST25InitReadArray(UINT32 address);
void vSST25StopReadArray(void);
#define uiSST25ReadHighByteArray() uiSPIGet()

#endif //_SST25VF016_H

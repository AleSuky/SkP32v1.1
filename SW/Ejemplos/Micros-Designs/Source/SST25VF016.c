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
#include "SST25VF016.h"

// *------------------------------------------------------*
void vSST25Init(void){

	SST25_CS_TRIS=0;
	SST25_CS=1;
	OpenSPI(SPI_START_CFG_1, SPI_START_CFG_2);
	SPIBRG=0; // a 80 MHz -> 40MHz SPI
    vSST25ResetWriteProtection();
}
// *------------------------------------------------------*
inline void __attribute__((always_inline)) vSPIPut(UINT8 data){
    UINT8 clear;
    
    putcSPI((UINT8)data);
    clear = getcSPI();
    return; 
}
// *------------------------------------------------------*
inline UINT8 __attribute__((always_inline)) uiSPIGet(void){
	
	putcSPI((UINT8)0xFF);
    return((UINT8)getcSPI());
}
// *------------------------------------------------------*
void vSST25WriteByte(UINT8 data,UINT32 address){
	
    vSST25WriteEnable();
    
	SST25_CS=0;
    vSPIPut(SST25_CMD_WRITE);
    vSPIPut(*((UINT8 *)&address+2));
    vSPIPut(*((UINT8 *)&address+1));
    vSPIPut(*((UINT8 *)&address));
    vSPIPut(data);
    SST25_CS=1;

    // Wait for write end
    while(uiSST25IsWriteBusy());
}
// *------------------------------------------------------*
UINT8 uiSST25ReadByte(UINT32 address){
    UINT8 temp;
    
	SST25_CS=0;
    vSPIPut(SST25_CMD_READ);
	vSPIPut(*((UINT8 *)&address+2));
    vSPIPut(*((UINT8 *)&address+1));
    vSPIPut(*((UINT8 *)&address));
    temp = uiSPIGet();
	SST25_CS=1;
	
    return (temp);
}
// *------------------------------------------------------*
void vSST25InitReadHighArray(UINT32 address){
   
	SST25_CS=0;
    vSPIPut(SST25_CMD_READH);
	vSPIPut(*((UINT8 *)&address+2));
    vSPIPut(*((UINT8 *)&address+1));
    vSPIPut(*((UINT8 *)&address));
    vSPIPut(0xFF); // Dummy
}

void vSST25StopReadHighArray(void){
	SST25_CS=1;
}
// *------------------------------------------------------*
void vSST25WriteEnable(void){
	
    SST25_CS=0;
    vSPIPut(SST25_CMD_WREN);
    SST25_CS=1;
}
// *------------------------------------------------------*
UINT8 uiSST25IsWriteBusy(void){
    UINT8 temp;

    SST25_CS=0;
    vSPIPut(SST25_CMD_RDSR);
    temp = uiSPIGet();
    SST25_CS=1;

    return(temp & 0x01);
}
// *------------------------------------------------------*
void vSST25ChipErase(void){
	
    vSST25WriteEnable();

    SST25_CS=0;
    vSPIPut(SST25_CMD_ERASE);
    SST25_CS=1;

    // Wait for write end
    while(uiSST25IsWriteBusy());
}
// *------------------------------------------------------*
void vSST25ResetWriteProtection(void){
	
    SST25_CS=0;
    vSPIPut(SST25_CMD_EWSR);
    SST25_CS=1;
	Nop();
    SST25_CS=0;
    vSPIPut(SST25_CMD_WRSR);
    vSPIPut(0x00);
    SST25_CS=1;
}
// *------------------------------------------------------*
void vSST25SectorErase(UINT32 address){	// 4kByte...
	
    vSST25WriteEnable();
    
	SST25_CS=0;
   	vSPIPut(SST25_CMD_SER);
    vSPIPut(*((UINT8 *)&address+2));
    vSPIPut(*((UINT8 *)&address+1));
    vSPIPut(*((UINT8 *)&address));
    SST25_CS=1;

    // Wait for write end
    DelayMs(100);
    while(uiSST25IsWriteBusy());
}


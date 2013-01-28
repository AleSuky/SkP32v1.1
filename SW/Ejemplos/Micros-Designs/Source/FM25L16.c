/* 
   \file FM25L16.c  
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
#include "FM25L16.h"
// *------------------------------------------------------*
void vInitMemoryFM25L16(void){

	FM25L16_CS_TRIS=0;
	FM25L16_CS=1;
	OpenSPI(SPI_START_CFG_1, SPI_START_CFG_2);
	SPIBRG=39; // a 80 MHz -> 2MHz SPI
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

void vEnableWriteMemoryFM25L16(void){

	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_ENABLE_W);
	FM25L16_CS=1;
}

UINT8 ui8ReadStateMemoryFM25L16(void){
	UINT8 DataRead;

	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_READ_STATUS);
	DataRead=uiSPIGet();
	FM25L16_CS=1;
	
	return(DataRead);
}

void vWriteSingleMemoryFM25L16(UINT16 Address,UINT8 Data){
	
	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_ENABLE_W);
	FM25L16_CS=1;
	Nop();
	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_WRITE);
	vSPIPut((*((UINT8 *)&Address+1))&0x07);
	vSPIPut(Address);
	vSPIPut(Data);
	FM25L16_CS=1;
  
}

UINT8 ui8ReadSingleMemoryFM25L16(UINT16 Address){
	UINT8 DataRead;
	
	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_READ);
	vSPIPut((*((UINT8 *)&Address+1))&0x07);
	vSPIPut(Address);
	DataRead=uiSPIGet();
	FM25L16_CS=1;

	return(DataRead);
}

void vWritePageMemoryFM25L16(UINT16 Address,UINT16 Length,UINT8 *Data){
	UINT16 k;

	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_ENABLE_W);
	FM25L16_CS=1;
	Nop();
	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_WRITE);
	vSPIPut((*((UINT8 *)&Address+1))&0x07);
	vSPIPut(Address);
	k=0;
	do{
		vSPIPut(*Data++);
	}while(++k<Length);	
	FM25L16_CS=1;
	return;
}

void vReadPageMemoryFM25L16(UINT16 Address,UINT16 Length,UINT8 *Data){
	UINT16 k;

	FM25L16_CS=0;
	vSPIPut(MEMORY_SPI_READ);
	vSPIPut((*((UINT8 *)&Address+1))&0x07);
	vSPIPut(Address);
	k=0;
	do{
		*Data++=uiSPIGet();
	}while(++k<Length);
	FM25L16_CS=1;
	return;
}

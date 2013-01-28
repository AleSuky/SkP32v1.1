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
#include "..\Include\ADS7843.h"


void vInitADS7843(void){
	
	ADS7843_TRIS_CS=PIN_OUTPUT;
	ADS7843_TRIS_IRQ=PIN_INPUT;
	ADS7843_TRIS_CLK=PIN_OUTPUT;
	ADS7843_TRIS_SDO=PIN_INPUT;
	ADS7843_TRIS_SDI=PIN_OUTPUT;
 
	ADS7843_PIN_CS=1;
	ADS7843_PIN_SDI=0;
	ADS7843_PIN_CLK=0;
	
	return;
}
/*****************************************************************/
void vTestTouchPanel(TOUCH_DATA *Data){
	UINT16 TempX,TempY;
	UINT8 k;
	
	DelayMs(1);
	
	TempX=0;TempY=0;
	for(k=0;k<8;k++){
		TempX+=ADS7843WriteAndReadData(ADS7843_READ_X);
		TempY+=ADS7843WriteAndReadData(ADS7843_READ_Y); 
	}
	
 
	Data->x=(TempX>>3);
	Data->y=(TempY>>3);
	
	return;
}
/*****************************************************************/
UINT_COORDxy ADS7843WriteAndReadData(UINT8 Data){
	UINT8 k;
	UINT_COORDxy Temp;
	
	ADS7843_PIN_CS=0;
	__delay_CLK_ADS7843();
	// En cada flanco ascendente se toma el dato:
	
	for(k=0;k<8;k++){
		ADS7843_PIN_SDI=!!(Data&0x80);
		__delay_CLK_ADS7843();
		ADS7843_PIN_CLK=1;
		__delay_CLK_ADS7843();
		Data<<=1;
		ADS7843_PIN_CLK=0;
		
	}
	__delay_CLK_ADS7843(); // Esperamos busy:
    ADS7843_PIN_CLK=1;
    __delay_CLK_ADS7843();
    ADS7843_PIN_CLK=0;
    __delay_CLK_ADS7843();
    __delay_CLK_ADS7843(); // Esperamos busy:
	// En flanco descendente leemos data desde el ADS7843:
	Temp=0;
	ADS7843_PIN_CLK=1;
	#if defined(ADS7843_USE_12BITS)
	for(k=0;k<12;k++){
	#else
	for(k=0;k<8;k++){
	#endif
		Temp<<=1;
		ADS7843_PIN_CLK=0;
		Temp+=(UINT16)ADS7843_PIN_SDO;
		__delay_CLK_ADS7843();
		ADS7843_PIN_CLK=1;
	}
	__delay_CLK_ADS7843();
	ADS7843_PIN_CLK=0;
	ADS7843_PIN_CS=1;
	
	return(Temp);
}
/*****************************************************************/

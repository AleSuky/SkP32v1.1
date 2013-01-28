/**
   \version: 1.1


   \author Suky
   \web www.micros-designs.com.ar
   \date 22/11/11


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
 * 22/11/11      Suky               Original (Rev 1.0)                        *
 * 29/11/11		 Suky				Se agrega vCreateFileBMP24bits(...)		  *
 *----------------------------------------------------------------------------* */
#include "..\Include\Graphics_Card2TFT.h"

volatile char kbhit_rtc=0;
BOOL RelojSalir;
// *---------------------------------------------------------------------------*
void __ISR(_RTCC_VECTOR, ipl4) RtccIsr(void){
	
	INTClearFlag(INT_RTCC);
	kbhit_rtc=1;
}
// *---------------------------------------------------------------------------*
UINT8 ui8BCD2BIN(UINT8 BCDValue){
	UINT8 Temp;

	Temp = BCDValue;
	Temp >>= 1;
	Temp &= 0x78;
	return(Temp + (Temp >> 2) + (BCDValue & 0x0f));
}
// *---------------------------------------------------------------------------*
void vDrawReloj(void){
	rtccTime	tm;
	BOOL Esperar;
	UINT16 x_sec,y_sec,x_min,y_min,x_hr,y_hr;
    UINT16 Angulo;
    #define CENTRO_X                119
    #define CENTRO_Y                159
    #define AGUJA_SEC               55
    #define AGUJA_MIN               50
    #define AGUJA_HR                42
    #define COLOR_FONDO             0xEF7D
	
	RtccInit();			
	while(RtccGetClkStat()!=RTCC_CLK_ON);
	tm.l=0;
	tm.sec=0x30;
	tm.min=0x45;
	tm.hour=0x13;
	
	RtccChimeEnable();			
	RtccSetAlarmRptCount(0);		
	RtccSetAlarmRpt(RTCC_RPT_SEC);			// Cada 1 seg.
	RtccAlarmEnable();
	RtccSetTimeDate(tm.l,0x11112202);
	
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();
	INTSetVectorPriority(INT_RTCC_VECTOR, INT_PRIORITY_LEVEL_4);			
	INTSetVectorSubPriority(INT_RTCC_VECTOR, INT_SUB_PRIORITY_LEVEL_1);		
	INTEnable(INT_RTCC, INT_ENABLED);
	
	// Dibujamos imagen desde Sd Card
	vDrawImageSDBMP24Bits("RELOJ.BMP");
	while(RelojSalir==0){
		// Calculamos extremos (x,y) de las agujas->
		// Esto depende de la imagen del reloj de fondo :p
        Angulo=ui8BCD2BIN(tm.sec)*6; // 6=360/60
        x_sec=CENTRO_X+sin((Angulo*3.14159)/180.0)*AGUJA_SEC;
        y_sec=CENTRO_Y-cos((Angulo*3.14159)/180.0)*AGUJA_SEC;
        Angulo=ui8BCD2BIN(tm.min)*6+ui8BCD2BIN(tm.sec)*0.1;  // 0.1=6/360
        x_min=CENTRO_X+sin((Angulo*3.14159)/180.0)*AGUJA_MIN;
        y_min=CENTRO_Y-cos((Angulo*3.14159)/180.0)*AGUJA_MIN;
        Angulo=ui8BCD2BIN(tm.hour)*30+ui8BCD2BIN(tm.min)*0.5; // 30=360/12, 0.5=30/60
        x_hr=CENTRO_X+sin((Angulo*3.14159)/180.0)*AGUJA_HR;
        y_hr=CENTRO_Y-cos((Angulo*3.14159)/180.0)*AGUJA_HR;
        // Dibujamos:        
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_min,y_min,ColorAzulMarino);
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_hr,y_hr,ColorAzulMarino);
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_sec,y_sec,ColorNaranja);
        vLCDTFTCircle(CENTRO_X,CENTRO_Y,3,1,ColorNaranja);
        Esperar=0;
        while(Esperar==0){
            // Interrpcion cada 1 segundo que setea bandera kbhit_Temporizacion.
            if(kbhit_rtc==1){
                kbhit_rtc=0;
                tm.l=RtccGetTime();
                Esperar=1;       
            }
        }
        // Borramos:
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_sec,y_sec,COLOR_FONDO);
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_min,y_min,COLOR_FONDO);
        vLCDTFTLine(CENTRO_X,CENTRO_Y,x_hr,y_hr,COLOR_FONDO);
	
	}
}
// *---------------------------------------------------------------------------*
void vDrawImageSDBMP24Bits(const CHAR8 *NameImagen){
    #define OffsetWidthPixel    18
    #define OffsetHeighPixel    22
    #define OffsetSizeFile      34
    #define OffsetInitData      10
    #define OffserTipeFile      28
    
    CHAR8 err,p;
    UINT16 PosXImagen,PosYImagen,k,i,y;
    UINT8 Temp,BufferHeader[54],BufferTemp[3],Adicional;
    UINT32 WidthPixel,HeighPixel;
    UINT16 TipeFile,InitData,Temp16bits;
    DATA_COLOR Color; 
    FSFILE *Imagen;
    
    err=FSInit();    
	if(err==FALSE){
		vLCDTFTFillScreen(ColorBlack);
		return;
	}
	Imagen = FSfopen(NameImagen,"r");
    // Si no se pudo encontrar archivo:
    if(Imagen==NULL){
        vLCDTFTFillScreen(ColorBlack);
        return;
    }
    // Leemos cabecera de archivo
    FSfread(&BufferHeader[0],1,54,Imagen);
    WidthPixel = ((UINT32)BufferHeader[OffsetWidthPixel + 3]*16777216+BufferHeader[OffsetWidthPixel + 2]*65536+BufferHeader[OffsetWidthPixel + 1]*256+BufferHeader[OffsetWidthPixel]);
    HeighPixel = ((UINT32)BufferHeader[OffsetHeighPixel + 3]*16777216+BufferHeader[OffsetHeighPixel + 2]*65536+BufferHeader[OffsetHeighPixel + 1]*256+BufferHeader[OffsetHeighPixel]);
    InitData = ((UINT16)BufferHeader[OffsetInitData]);
    TipeFile = ((UINT16)BufferHeader[OffserTipeFile + 1]*256 + BufferHeader[OffserTipeFile]);
    
    if((WidthPixel>LCD_X_MAX) || (HeighPixel>LCD_Y_MAX) || (TipeFile!=24)){
	    LATBbits.LATB8=1;
        FSfclose(Imagen);
        return;
    }
    
    if(InitData!=54){
        for(k=54;k<InitData;k++){
            FSfread(&Temp,1,1,Imagen);
        }
    }
    
    PosXImagen=(LCD_X_MAX/2)-(WidthPixel/2);
    PosYImagen=(LCD_Y_MAX/2)+(HeighPixel/2);
    
    Temp16bits=WidthPixel*3;
    Adicional=0;
    while(((Temp16bits)%4)!=0){
        Adicional++;
        Temp16bits++;
    }
    for(k=0,y=PosYImagen;k<HeighPixel;k++,y--){
        vLCDTFTAddressSet(PosXImagen,y,PosXImagen+WidthPixel-1,y);
        for(i=0;i<WidthPixel;i++){
            FSfread(&BufferTemp[0],1,3,Imagen); // Leemos 3 bytes (R,G,B)
            Color.Blue=BufferTemp[0]>>3;Color.Green=BufferTemp[1]>>2;Color.Red=BufferTemp[2]>>3; // Conversion de 24-bits a 16-bits.-
            vLCDTFTWriteData(Color.Val);
        }
        // Bytes adicionales para que linea sea multiplo de 4.-
        for(p=0;p<Adicional;p++){
            FSfread(&Temp,1,1,Imagen);
        }
    }
    FSfclose(Imagen);
}
void vCreateFileBMP24bits(const CHAR8 *Name){
	const UINT8 Header[54]={0x42,0x4D,0x36,0x84,0x03,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,
							0x00,0x28,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x40,0x01,0x00,0x00,
							0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x84,0x03,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00};
	FSFILE *Imagen;
	CHAR8 err;
	UINT8 eof;
	DATA_COLOR Color; 
	UINT16 k,i,y;
    UINT8 BufferTemp[3];
    
    err=FSInit();    
	if(err==FALSE)return;
	Imagen=FSfopen(Name,"w");
	if(Imagen==NULL)return;
	// Cabecera del formato BMP.
	eof=(FSfwrite((void *)&Header[0],1,54,Imagen)!=54);
	if(eof){
		FSfclose(Imagen);
		return;
	}
	
	vLCDTFTAddressSet(0,0,239,319);
	vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6010); // x incrementa, y decrementa	
	vLCDTFTAddressSetPoint(0,319);	
	for(k=0,y=319;k<320;k++,y--){
		for(i=0;i<240;i++){
			Color.Val=uiLCDTFTGetPointCurrent();
			BufferTemp[0]=Color.Blue<<3;BufferTemp[1]=Color.Green<<2;BufferTemp[2]=Color.Red<<3; // 16-bits a 24-bits.-
			eof=(FSfwrite((void *)&BufferTemp[0],1,3,Imagen)!=3);
			if(eof){
				FSfclose(Imagen);
				vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6030); // x incrementa, y incrementa
				vLCDTFTAddressSet(0,0,239,319);
				return;
			}
		}
	}		
	vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6030); // x incrementa, y incrementa
	vLCDTFTAddressSet(0,0,239,319);
	FSfclose(Imagen);
}
// *---------------------------------------------------------------------------*
void vTextoJustificado(const CHAR8 *PtrTexto,UINT16 ExtremoIzq,UINT16 ExtremoDer,UINT16 y,UINT8 Just,const CHAR8 (*Fuente)[5],UINT8 Alto,UINT16 Color){
    UINT8 x,NCaracteres;
    const CHAR8 *Ptr;

    if(Just!=JUST_IZQ){
        for(Ptr=PtrTexto;*Ptr!='\0';Ptr++);
        NCaracteres=Ptr - PtrTexto;
    }
    switch(Just){
        case JUST_IZQ:
            x=ExtremoIzq+5;
        break;
        case JUST_DER:
            x=ExtremoDer-NCaracteres*(5*Alto+1)-4;
        break;
        case JUST_CENTRADO:
            x=((ExtremoIzq+ExtremoDer-NCaracteres*(5*Alto+1))/2);
        break;
    }
    vLCDTFTText(x,y,PtrTexto,Fuente,Alto,Color);
}

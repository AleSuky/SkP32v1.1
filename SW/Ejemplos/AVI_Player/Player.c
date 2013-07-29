/*
**  AVIPlayer.c    Audio Video Interleaved playback from SD card 
**
**  by LDJ  
**
**  NOTE: This version assumes an input AVI file <= @15fps QQVGA RGB565
**      with 8-bit audio @22050Hz (mono)
**  Ref:    www.exploringpic32.com
** 
**  Modificado por Suky 27/11/11:
**  Adaptado a Board SkP32 con PIC32MX360F512L y LCD TFT SSD1289
**  Audio generado por PWM (OC3 y OC4) a 22050 Hz, 8-bits, mono.-
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2011 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
*/
#include "Player.h"

UINT16 BufferVideo[H_MAX];

AUDIO_DATA BufferAudio[N_BUFFERS]; // Cola de Buffers circulares.

struct{
	UINT8 NBufferEscritura;
	UINT8 NBufferLectura;
	UINT16 NActual;
	UINT8 *PtrBuffer;
	BOOL BuffersAudioVacio;
}ControlAudio;
//*******************************************************************************
void __ISR(_TIMER_2_VECTOR, ipl2 ) ISR_T2(void){
	INT8 i;		
	
	// Se ha leido el buffer actual completamente?
	if(ControlAudio.NActual==0){
		i=i8GetBufferRead();
		if(i<0){
			// No hay buffers para leer :(
			ControlAudio.BuffersAudioVacio=1;
			OC3RS=((UINT16)(*(ControlAudio.PtrBuffer-1))*8);//14
		}else{
			ControlAudio.NBufferLectura=i;
			ControlAudio.NActual=BufferAudio[ControlAudio.NBufferLectura].Count;
			ControlAudio.PtrBuffer=&BufferAudio[ControlAudio.NBufferLectura].Buffer[0];
			OC3RS=((UINT16)(*ControlAudio.PtrBuffer)*10);//14
		}		
		OC4RS=OC3RS;
	}else{
		OC3RS=((UINT16)(*ControlAudio.PtrBuffer)*8);//14
		OC4RS=OC3RS;
		ControlAudio.PtrBuffer++;
		ControlAudio.NActual--;	
	}	
	mT2ClearIntFlag();
}
//*-------------------------------------------------------------------------------*   	
void vInitAudio(UINT16 FSample){

	ControlAudio.NBufferEscritura=0;
	ControlAudio.NBufferLectura=0;
	
	OpenOC3(OC_ON | OC_TIMER2_SRC | OC_TIMER_MODE16 | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // RD2
   	OpenOC4(OC_ON | OC_TIMER2_SRC | OC_TIMER_MODE16 | OC_PWM_FAULT_PIN_DISABLE, 0, 0); // RD3

    OpenTimer2(T2_ON | T2_PS_1_1 |  T2_SOURCE_INT, (GetPeripheralClock()/FSample)-1);  // Frecuencia, depende de sps del audio.-    
    // Para FPB=80MHz y Fpwm=22050 -> Bits=11.82 -> 3627. 50%=1813.
    // Audio de 8-bits -> 0=0x80=128. 
    // 128 del audio equivale a 1813 PWM y 255 -> 3627 PWM
    // ValorPWM=ValorAudio*14 Max volumen
    mT2SetIntPriority(2);
    
    // Para saltar primer frame
	ControlAudio.BuffersAudioVacio=1;
}
//*-------------------------------------------------------------------------------*   
INT8 i8GetBufferWrite(void){
    INT8 i=(ControlAudio.NBufferEscritura+1)%N_BUFFERS;
    
    if(i==ControlAudio.NBufferLectura){
        return -1;   // Cola de buffer llena
    }
    // Retorna posicion
    return(i); 
}
//*-------------------------------------------------------------------------------*   
INT8 i8GetBufferRead(void){
	INT8 i;
	
	if(ControlAudio.NBufferLectura==ControlAudio.NBufferEscritura){
		return -1;      // No hay
	}  
	i=(ControlAudio.NBufferLectura+1)%N_BUFFERS;
     
	return(i);     
} 
//*-------------------------------------------------------------------------------*   
void vStartAudio(void){

	ControlAudio.NBufferLectura=i8GetBufferRead();
	ControlAudio.NActual=BufferAudio[ControlAudio.NBufferLectura].Count;
	ControlAudio.PtrBuffer=&BufferAudio[ControlAudio.NBufferLectura].Buffer[0];
		
	mT2ClearIntFlag();
    mT2IntEnable(1);
    INTEnableSystemMultiVectoredInt();
}
//*******************************************************************************
void vInitPlayer(void){
	
	vLCDTFTInit();
	vLCDTFTFillScreen(ColorGray);
	while( !FSInit());	
}
//*-------------------------------------------------------------------------------*       
UINT32 PlayAVI(const CHAR8 *fname){
    UINT16 *pV;
    UINT32 i, j, r, eof;
    UINT32 frames=0;
    FSFILE *fp;
    CHUNK ck;
    BOOL InitAudio;
    UINT8 CtrlVideo=5;
    INT8 Status;
    
    
    // Rotamos pantalla 90º
    vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6038); 

    // 1. Se define tamaño de la ventana y se inicia primera posicion
#ifndef DOUBLE_H
    vLCDTFTAddressSetH(80,60,H_MAX-1,V_MAX-1);  
#else
    #ifndef DOUBLE_V
    vLCDTFTAddressSetH( 0, 60, (H_MAX*2)-1, V_MAX);     
    #else
    vLCDTFTAddressSetH( 0, 0, (H_MAX*2)-1, (V_MAX*2)-1);   
    #endif
#endif
	//mPORTGSetBits(LCD_PIN_RS);  // RS = 1 
	
    // 2. Abrir AVI
    if(( fp = FSfopen( fname, "r")) == NULL){
        return -3;  // No se encuentra archivo
    }    
       
    // 3. Lectura de Chuck RIFF
    r = FSfread( (void*)&ck, sizeof(CHUNK), 1, fp);
    if(r == 0){ return -100;}   
    
    // 4. Es correcto?
    if(( ck.ckID != RIFF_DWORD) || ( ck.ckType != AVI_DWORD)){
        return -4;  // No es RIFF-AVI
    }    
        
    // 5. Chunk LIST
    r = FSfread( (void*)&ck, sizeof(CHUNK), 1, fp);
    if( r == 0){return -100;}    // unexpected eof
    
    if( ck.ckID != LIST_DWORD){
        return -5;  // 
    }    
    
    // 6. Saltamos hasta llegar a Chuck MOVI
    while((( ck.ckID == LIST_DWORD) && (ck.ckType != MOVI_DWORD)) || ( ck.ckID == JUNK_DWORD)){
        // Saltamoes chuck
        eof = FSfseek( fp, ck.ckSize-4, SEEK_CUR);
        if(eof){return -100;}   
        
        // Leemos siguiente chuck
        r = FSfread( (void *)&ck, sizeof(CHUNK), 1, fp);
        if(r == 0){return -100;}    
    }
    // 7. Iniciamos audio 22050 - 8-bit - mono
	vInitAudio(22050);           
	InitAudio=1;
    // 8. Reproducimos video
    while(1){
        // Lectura del siguiente chuck
        r = FSfread( (void*)&ck, 8, 1, fp);
        if(r == 0) break;
        
        // 8.1 Es audio o video? 
        if ( ck.ckID == WB_DWORD){ // audio
	        do{
		        Status=i8GetBufferWrite();
         	}while(Status<0); // Esperamos hasta que hay un buffer libre
            r = FSfread( (void*)&BufferAudio[Status].Buffer[0], (ck.ckSize+1) & 0xFFFFFFFE, 1, fp); 
            if (r == 0) break; 
            
            BufferAudio[Status].Count = ck.ckSize;                
            ControlAudio.NBufferEscritura=Status;
            
            if(InitAudio==1){
            	InitAudio=0;
            	vStartAudio();
            }
            //eof = FSfseek( fp, (ck.ckSize+1) & 0xFFFFFFFE, SEEK_CUR);   // skip audio
            //if ( eof)  break;
        }        
        // 8.2 video
        else if (ck.ckID == DC_DWORD){ // video
            frames++;
            // Si se necesita rellenar buffers de audio, salteamos frame
            if(ControlAudio.BuffersAudioVacio==1){
            	ControlAudio.BuffersAudioVacio=0;
            	eof = FSfseek( fp, (ck.ckSize+1) & 0xFFFFFFFE, SEEK_CUR);  // skip video
	        	if(eof) break;
	        	
	        	if(CtrlVideo!=0){ // Para cargar varios buffer de audio al iniciar
		        	CtrlVideo--;
	        		ControlAudio.BuffersAudioVacio=1;
	        	}
            }
            else{	
				//mPORTDClearBits(LCD_PIN_CS); // CS = 0  
	            // 8.2.1 Lee cada linea y dibuja
	            for( j=0; j<V_MAX; j++){        
	                eof = (FSfread( BufferVideo, 2, H_MAX, fp) != 160);
	                if ( eof) break;                   
	                  
	                pV = &BufferVideo[H_MAX-1]; i = H_MAX;
	                while( i--) {
#ifdef DOUBLE_H
		                vLCDTFTWriteData(*pV);    
#endif
		                vLCDTFTWriteData(*pV--);
		            }
#ifdef DOUBLE_V
		            pV = &BufferVideo[H_MAX-1]; i = H_MAX;
		            while( i--) {
#ifdef DOUBLE_H
		            	vLCDTFTWriteData(*pV);          
#endif
		            	vLCDTFTWriteData(*pV--);
		        	}
#endif
				}  // for               
				//mPORTDSetBits(LCD_PIN_CS); // CS = 1   
			}// else
        } // video
    } // while 
    
    // Des-habilitamos interrupcion de audio.-
    mT2IntEnable(0);
    // Cerramos archivo
    FSfclose(fp);   

    // 9. Reestablecemos ventana
    vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6030); 
    vLCDTFTAddressSetH(0,0,239,319);
    
    return frames;
} // PlayAVI


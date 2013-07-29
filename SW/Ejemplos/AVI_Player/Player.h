#include <p32xxxx.h>
#include <plib.h>
#include "LCDTFT.h"
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

#include "FSIO.h"
#include "LCDTFT.h"

#define  RIFF_DWORD  0x46464952UL
#define  WAVE_DWORD  0x45564157UL
#define  DATA_DWORD  0x61746164UL
#define  AVI_DWORD   0x20495641UL
#define  LIST_DWORD  0x5453494CUL
#define  MOVI_DWORD  0x69766f6dUL
#define  JUNK_DWORD  0x4b4e554aUL
#define  DC_DWORD    0x63643030UL
#define  WB_DWORD    0x62773130UL
#define  FMT_DWORD   0x20746d66UL     
#define  WAV_DWORD   0x00564157UL

#define V_MAX       120
#define H_MAX       160
#define DOUBLE_H	// 320
#define DOUBLE_V	// 240

#define AUDIO_SIZE	1024	// 
#define N_BUFFERS	5

typedef struct {
    UINT32 ckID;
    UINT32 ckSize;
    UINT32 ckType;
}CHUNK;

typedef struct{
    UINT16 Count;
    UINT8 Buffer[AUDIO_SIZE];
}AUDIO_DATA;


void vInitAudio(UINT16 FSample);
INT8 i8GetBufferWrite(void);
INT8 i8GetBufferRead(void);
void vStartAudio(void);
void vInitPlayer(void);
UINT32 PlayAVI(const CHAR8 *fname);

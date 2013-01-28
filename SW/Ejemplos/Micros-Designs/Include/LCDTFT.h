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
#ifndef _LCDTFT_H_
#define _LCDTFT_H_ 

#include <p32xxxx.h>
#include <plib.h>
#include "GenericTypeDefs.h"
#include "TimeDelay.h" 
// *------------------------------------------------------------* 
#define LCD_PIN_RS      BIT_15
#define LCD_TRIS_RS     TRISGbits.TRISG15

#define LCD_PIN_RST     LATAbits.LATA15
#define LCD_TRIS_RST    TRISAbits.TRISA15

#define LCD_PIN_CS      BIT_10
#define LCD_TRIS_CS     TRISDbits.TRISD10

#define LCD_PIN_RD		BIT_5
#define LCD_TRIS_RD		TRISDbits.TRISD5

#define LCD_PIN_WR		BIT_4
#define LCD_TRIS_WR		TRISDbits.TRISD4
// *------------------------------------------------------------* 
#define LCD_WIDTH   320
#define LCD_HEIGHT  240
#define LCD_X1      0
#define LCD_X2      (LCD_WIDTH - LCD_X1 - 1)
#define LCD_Y1      0
#define LCD_Y2      (LCD_HEIGHT - LCD_Y1 - 1)
#define X_SIZE      300
#define Y_SIZE      200
#define MIN_X       1
#define MIN_Y       20
#define MAX_X       (MIN_X + X_SIZE - 1)
#define MAX_Y       (MIN_Y + Y_SIZE - 1)
// *------------------------------------------------------------* 
#define    ColorRed             0xf800
#define    ColorGreen           0x400
#define    ColorBlue            0x001f
#define    ColorMarron          0x8208
#define    ColorBlack           0x0
#define    ColorWhite           0xffff
#define    ColorMaroon          0x8000
#define    ColorFuchsia         0xf81f
#define    ColorVioleta         0x801f
#define    ColorAzulMarino      0x14
#define    ColorGray            0x8410
#define    ColorOlive           0x8400
#define    ColorNaranja         0xfc08
#define    ColorYellow          0xffe0
#define    ColorCian            0x87ff
#define    ColorRosado          0xf810
#define    ColorNavy            0x10
#define    ColorPurple          0x8010
#define    ColorTeal            0x410
#define    ColorLime            0x7e0
#define    ColorAqua            0x7ff
#define	   ColorGray1			0xc618
#define    ColorGray2			0xdefb
#define    ColorGray3			0xf79e
// *------------------------------------------------------------* 
#define       LCD_X_MAX            240
#define       LCD_Y_MAX            320

extern const char ARIAL[95][5];
extern const char COMIC[95][5];

typedef union{
	UINT16 Val;
	struct{
		unsigned Blue:5;
		unsigned Green:6;
		unsigned Red:5;
	};
	struct{
		UINT8 LB;
		UINT8 HB;
	};
}DATA_COLOR;
// *------------------------------------------------------------* 
void vLCDTFTInit(void);
void vLCDTFT_Scroll_V(UINT16 y1);
void vLCDTFTFillScreen(UINT16 Color);
void vLCDTFTFillScreenH(UINT16 Color);
UINT16 uiLCDTFTGetPointCurrent(void);
UINT16 uiLCDTFTGetPoint(UINT16 x,UINT16 y);
void vLCDTFTPoint(UINT16 x,UINT16 y,UINT16 Color);
void vLCDTFTText(UINT16 x,UINT16 y,const char *PtrText,const char (*Fuente)[5],unsigned char Alto,UINT16 Color);
void vLCDTFTLine(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 Color);
void vLCDTFTRectangle(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,BOOL Filled,UINT16 Color);
void vLCDTFTCircle(UINT16 x,UINT16 y,UINT16 Radius,BOOL Filled,UINT16 Color);

void vLCDTFTAddColor(UINT16 x, UINT16 y, UINT16 Color);
void vLCDTFTEraseColor(UINT16 x, UINT16 y, UINT16 Color);
void vLCDTFTTextH(UINT16 x,UINT16 y,const char *PtrText,const char (*Fuente)[5],UINT16 Color);
// *------------------------------------------------------------* 
// R = 5 bits 0:4, G = 6 bits 5:10, B = 5 bits 11:15
#define RGB(_R,_G,_B) (((_R & 0x3E) >> 1) | ((_G & 0x3f) << 5) | ((_B & 0x3e) << 10))

#define C_GROUP     0x1082  // 00010 000100 00010 
#define F_SELEC     0x18E3  // 00011 000111 00011 
#define WAV_FLAG    0x0080
#define CH2_FLAG    0x0002
#define REF_FLAG    0x1000
#define LN1_FLAG    0x0020   
#define LN2_FLAG    0x0800   
#define GRD_FLAG    0x0040   
#define LN1_COLOR   (RGB(32,63,32) & ~F_SELEC) | LN1_FLAG
#define LN2_COLOR   (RGB(63,63,63) & ~F_SELEC) | LN2_FLAG
#define GRD_COLOR   (RGB(32,32,32) & ~F_SELEC) | GRD_FLAG
#define WAV_COLOR   (RGB(0,63,63) & ~F_SELEC) | WAV_FLAG
#define CH2_COLOR   (RGB(63,63,0) & ~F_SELEC) | CH2_FLAG
#define REF_COLOR   (RGB(63,0,63) & ~F_SELEC) | REF_FLAG

//========================= color definitions ================================== 
#define YEL         RGB(63,63,0)
#define WHITE       RGB(63,63,63)
#define RED         RGB(63,0,0)
#define GRN         RGB(0,63,0)
#define BLACK       RGB(0,0,0)

#define FRM_COLOR   RGB(24,24,24)
#define BACKGROUND  BLACK
// *------------------------------------------------------------* 
#define vClearScreen(a) vLCDTFTFillScreen(a)
// *------------------------------------------------------------* 

#endif

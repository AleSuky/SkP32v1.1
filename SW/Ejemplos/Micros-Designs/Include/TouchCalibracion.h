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

#include <p32xxxx.h>
#include <plib.h>
#include "LCDTFT2.4.h"
#include "ADS7843.h" 

typedef struct{
    double  kx1;
    double  kx2;
    double  kx3;
    double  ky1;
    double  ky2;
    double  ky3;
}DATA_CALIBRACION;

void vAdquirirPuntosTouch(TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD, unsigned char N);
void vCalibrarTouch(DATA_CALIBRACION *Coef,TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD, unsigned char N);
void vPuntosTouch2LCD(DATA_CALIBRACION *Coef,TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD);

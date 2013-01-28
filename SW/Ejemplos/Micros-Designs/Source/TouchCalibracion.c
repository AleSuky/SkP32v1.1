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

#include "..\Include\TouchCalibracion.h"
	
		
void vAdquirirPuntosTouch(TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD, unsigned char N){
	char k;
	
	vLCDTFTFillScreen(ColorWhite);
    for(k=0;k<N;k++){
        vLCDTFTCircle(DataLCD->x,DataLCD->y,3,1,ColorBlack); 
        while(ADS7843_PIN_IRQ==1);
        vTestTouchPanel(DataTouch);
        DelayMs(500);
        vLCDTFTCircle(DataLCD->x,DataLCD->y,3,1,ColorWhite); 
        DataTouch++;
        DataLCD++;
    }
}
// http://www.analog.com/static/imported-files/application_notes/AN-1021.pdf
void vCalibrarTouch(DATA_CALIBRACION *Coef,TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD, unsigned char N){
    double a[3],b[3],c[3],d[3],k; 
    int i;
    
    if(N<3){
        return;
    }else{
        if(N==3){
            for(i=0;i<N;i++){ 
                a[i]=(double)(DataTouch->x); 
                b[i]=(double)(DataTouch->y); 
                c[i]=(double)(DataLCD->x); 
                d[i]=(double)(DataLCD->y);
                DataTouch++;
                DataLCD++; 
            }
        }else{ 
            for(i=0;i<3;i++){ 
                a[i]=0; 
                b[i]=0; 
                c[i]=0; 
                d[i]=0; 
            } 
            for(i=0; i<N; i++){  //AN-1021  Application Note Rev. 0 | Page 10 of 12 
                a[2]=a[2]+(double)(DataTouch->x); 
                b[2]=b[2]+(double)(DataTouch->y); 
                c[2]=c[2]+(double)(DataLCD->x); 
                d[2]=d[2]+(double)(DataLCD->y); 
                a[0]=a[0]+(double)(DataTouch->x)*(double)(DataTouch->x); 
                a[1]=a[1]+(double)(DataTouch->x)*(double)(DataTouch->y); 
                b[0]=a[1]; 
                b[1]=b[1]+(double)(DataTouch->y)*(double)(DataTouch->y); 
                c[0]=c[0]+(double)(DataTouch->x)*(double)(DataLCD->x); 
                c[1]=c[1]+(double)(DataTouch->y)*(double)(DataLCD->x); 
                d[0]=d[0]+(double)(DataTouch->x)*(double)(DataLCD->y); 
                d[1]=d[1]+(double)(DataTouch->y)*(double)(DataLCD->y); 
                DataTouch++;
                DataLCD++;
            } 
            a[0]=a[0]/a[2]; 
            a[1]=a[1]/b[2];  
            b[0]=b[0]/a[2]; 
            b[1]=b[1]/b[2];  
            c[0]=c[0]/a[2]; 
            c[1]=c[1]/b[2]; 
            d[0]=d[0]/a[2]; 
            d[1]=d[1]/b[2]; 
            a[2]=a[2]/N; 
            b[2]=b[2]/N; 
            c[2]=c[2]/N; 
            d[2]=d[2]/N;        
        }
        k=(a[0]-a[2])*(b[1]-b[2])-(a[1]-a[2])*(b[0]-b[2]); 
        Coef->kx1=((c[0]-c[2])*(b[1]-b[2])-(c[1]-c[2])*(b[0]-b[2]))/k; 
        Coef->kx2=((c[1]-c[2])*(a[0]-a[2])-(c[0]-c[2])*(a[1]-a[2]))/k; 
        Coef->kx3=(b[0]*(a[2]*c[1]-a[1]*c[2])+b[1]*(a[0]*c[2]-a[2]*c[0])+b[2]*(a[1]*c[0]-a[0]*c[1]))/k; 
        Coef->ky1=((d[0]-d[2])*(b[1]-b[2])-(d[1]-d[2])*(b[0]-b[2]))/k; 
        Coef->ky2=((d[1]-d[2])*(a[0]-a[2])-(d[0]-d[2])*(a[1]-a[2]))/k; 
        Coef->ky3=(b[0]*(a[2]*d[1]-a[1]*d[2])+b[1]*(a[0]*d[2]-a[2]*d[0])+b[2]*(a[1]*d[0]-a[0]*d[1]))/k; 
    }
}
void vPuntosTouch2LCD(DATA_CALIBRACION *Coef,TOUCH_DATA *DataTouch, TOUCH_DATA *DataLCD){

    DataLCD->x=Coef->kx1*DataTouch->x+Coef->kx2*DataTouch->y+Coef->kx3;
    DataLCD->y=Coef->ky1*DataTouch->x+Coef->ky2*DataTouch->y+Coef->ky3;
}

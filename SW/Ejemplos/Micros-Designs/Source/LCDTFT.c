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
 * 19/11/11      Suky               Original (Rev 1.0)   Driver SSD1289       *
 *----------------------------------------------------------------------------* */
#include "..\Include\LCDTFT.h"
#include "Fuentes_Imagenes.c"


void vLCDTFTWriteCommand(UINT16 Data){
    
    mPORTGClearBits(LCD_PIN_RS);
    mPORTDClearBits(LCD_PIN_CS);
    mPORTDClearBits(LCD_PIN_WR); 
    PMPMasterWrite(Data);
    mPORTDSetBits(LCD_PIN_WR);
    mPORTDSetBits(LCD_PIN_CS);  
}

void vLCDTFTWriteData(UINT16 Data){
 
    mPORTGSetBits(LCD_PIN_RS);
    mPORTDClearBits(LCD_PIN_CS);  
    mPORTDClearBits(LCD_PIN_WR);  
    PMPMasterWrite(Data);
    mPORTDSetBits(LCD_PIN_WR);
    mPORTDSetBits(LCD_PIN_CS);
}

void vLCDTFTWriteCommandData(UINT16 CMD,UINT16 Data){
    vLCDTFTWriteCommand(CMD);
    vLCDTFTWriteData(Data);
}


void vLCDTFTAddressSet(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2){ 

    vLCDTFTWriteCommandData(0x0044,(x2<<8)+x1);
    vLCDTFTWriteCommandData(0x0045,y1);
    vLCDTFTWriteCommandData(0x0046,y2);
    vLCDTFTWriteCommandData(0x004e,x1);
    vLCDTFTWriteCommandData(0x004f,y1);
    vLCDTFTWriteCommand(0x0022);  
}  

void vLCDTFTAddressSetH(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2){ 
        
    vLCDTFTWriteCommandData(0x0044,(y2<<8)+y1);
    vLCDTFTWriteCommandData(0x0045,x1);
    vLCDTFTWriteCommandData(0x0046,x2);
    vLCDTFTWriteCommandData(0x004e,y1);
    vLCDTFTWriteCommandData(0x004f,x1);
    vLCDTFTWriteCommand(0x0022);  
} 

void vLCDTFTAddressSetPoint(UINT16 x,UINT16 y){ 

    vLCDTFTWriteCommand(0x004e);vLCDTFTWriteData(x);
    vLCDTFTWriteCommand(0x004f);vLCDTFTWriteData(y);
    vLCDTFTWriteCommand(0x0022); 
} 

void vLCDTFTInit(void){
	
	LCD_TRIS_CS=0;
	LCD_TRIS_RS=0;
	LCD_TRIS_RST=0;
	LCD_TRIS_RD=0;
	LCD_TRIS_WR=0;
	
	mPORTDSetBits(LCD_PIN_WR);
	mPORTDSetBits(LCD_PIN_RD);
	mPORTDSetBits(LCD_PIN_CS);
    LCD_PIN_RST=0;

    // Inicilizamos PMP    
	PMMODE = 0;
    PMAEN = 0;
    PMCON = 0;
    PMMODEbits.MODE = 2;                    // Intel 80 master interface
    PMMODEbits.WAITB = 1;
    PMMODEbits.WAITM = 4;
    PMMODEbits.WAITE = 1; 
    PMMODEbits.MODE16 = 1;                  // 16 bit mode
    PMCONbits.PTRDEN = 0;                   // disable RD line
    PMCONbits.PTWREN = 0;                   // disable WR line
    PMCONbits.PMPEN = 1;                    // enable PMP

    DelayMs(40);
    LCD_PIN_RST = 1;                         // release from reset
    DelayMs(400);
     
    vLCDTFTWriteCommand(0x0000);vLCDTFTWriteData(0x0001); //Start Oscillation OSCEN=1
    DelayMs(15);
/*
    vLCDTFTWriteCommand(0x0003);vLCDTFTWriteData(0xA2A4); //Power Control (1)
    vLCDTFTWriteCommand(0x000C);vLCDTFTWriteData(0x0000); //Power Control (2)
    vLCDTFTWriteCommand(0x000D);vLCDTFTWriteData(0x0308); //Power Control (3)
    vLCDTFTWriteCommand(0x000E);vLCDTFTWriteData(0x3001); //Power Control (4)
    vLCDTFTWriteCommand(0x001E);vLCDTFTWriteData(0x00AC); //Power Control (5)
*/
    vLCDTFTWriteCommand(0x0003);vLCDTFTWriteData(0xAAAC); //Power Control (1)
    vLCDTFTWriteCommand(0x000C);vLCDTFTWriteData(0x0002); //Power Control (2)
    vLCDTFTWriteCommand(0x000D);vLCDTFTWriteData(0x000A); //Power Control (3)
    vLCDTFTWriteCommand(0x000E);vLCDTFTWriteData(0x2C00); //Power Control (4)
    vLCDTFTWriteCommand(0x001E);vLCDTFTWriteData(0x00B8); //Power Control (5)
    DelayMs(15);
    vLCDTFTWriteCommand(0x0001);vLCDTFTWriteData(0x2B3F); //Driver Output Control RL=0, REV=1, BGR=1, TB=1 
    //vLCDTFTWriteCommand(0x0001);vLCDTFTWriteData(0x6B3F); //Driver Output Control RL=1, REV=1, BGR=1, TB=1 
    vLCDTFTWriteCommand(0x0002);vLCDTFTWriteData(0x0600);
    // Restore VSYNC mode from low power state 
    vLCDTFTWriteCommand(0x0010);vLCDTFTWriteData(0x0000); //Sleep mode cancel
    //vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6038);
    vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6030); //Entry Mode
                                                            // DFM   0x4000 = 262L color
                                                            // DFM   0x6000 = 65K color
                                                            // AM    0x0000 = horizontal display
                                                            // AM    0x0008 = Vertical display
                                                            // ID[0] 0x0000 = horizontal decrement
                                                            // ID[0] 0x0010 = horizontal increment
                                                            // ID[1] 0x0000 = Vertical decrement
                                                            // ID[1] 0x0020 = Vertical decrement


    DelayMs(20);
    vLCDTFTWriteCommand(0x0005);vLCDTFTWriteData(0x0000); // Compare register
    vLCDTFTWriteCommand(0x0006);vLCDTFTWriteData(0x0000); // Compare register
    // Horizontal and Vertical porch are for DOTCLK mode operation
    vLCDTFTWriteCommand(0x0016);vLCDTFTWriteData(0xEF1C); // Horizontal Porch 
    vLCDTFTWriteCommand(0x0017);vLCDTFTWriteData(0x0003); // Vertical Porch
    // Display Control
    vLCDTFTWriteCommand(0x0007);vLCDTFTWriteData(0x0233); // Display Control
                                                             // D1 0x0000 = display off
                                                             // D1 0x0002 = display on
                                                             // D0 0x0000 = internal display halt
                                                             // D0 0x0001 = internal display operate


    vLCDTFTWriteCommand(0x000B);vLCDTFTWriteData(0x5312); // Frame cycle control
    vLCDTFTWriteCommand(0x000F);vLCDTFTWriteData(0x0000); // Gate Scan Position 
    DelayMs(20);
    // Vertical Scroll Control
    vLCDTFTWriteCommand(0x0041);vLCDTFTWriteData(0x0000); // Vertical Scroll Control
    vLCDTFTWriteCommand(0x0042);vLCDTFTWriteData(0x0000); // Vertical Scroll Control

    // 1st Screen driving position
    vLCDTFTWriteCommand(0x0048);vLCDTFTWriteData(0x0000); // Start position. 0
    vLCDTFTWriteCommand(0x0049);vLCDTFTWriteData(0x013F); // End position.   319

    // Source RAM address
    vLCDTFTWriteCommand(0x0044);vLCDTFTWriteData(0xEF00); //Horizontal RAM address position start/end setup 
                                                             //dec 239 
                                                             //dec 0, i.e. horizontal ranges from 0 -> 239 
                                                             //POR value is 0xEF00 anyway. This address must be set before RAM write 

    vLCDTFTWriteCommand(0x0045);vLCDTFTWriteData(0x0000); //Vertical RAM address start position setting 
                                                             //0x0000 = dec 0
    vLCDTFTWriteCommand(0x0046);vLCDTFTWriteData(0x013F); //Vertical RAM address end position setting (0x013F = dec 319)

    // 2nd Screen driving position
    //vLCDTFTWriteCommand(0x004A);vLCDTFTWriteData(0x0000); // Start position. 0
    //vLCDTFTWriteCommand(0x004B);vLCDTFTWriteData(0x0000); // End position.   0
    DelayMs(20); 
    //gamma control 
    vLCDTFTWriteCommand(0x0030);vLCDTFTWriteData(0x0707);
    vLCDTFTWriteCommand(0x0031);vLCDTFTWriteData(0x0704);
    vLCDTFTWriteCommand(0x0032);vLCDTFTWriteData(0x0204);
    vLCDTFTWriteCommand(0x0033);vLCDTFTWriteData(0x0201);
    vLCDTFTWriteCommand(0x0034);vLCDTFTWriteData(0x0203);
    vLCDTFTWriteCommand(0x0035);vLCDTFTWriteData(0x0204);
    vLCDTFTWriteCommand(0x0036);vLCDTFTWriteData(0x0204);
    vLCDTFTWriteCommand(0x0037);vLCDTFTWriteData(0x0502);
    vLCDTFTWriteCommand(0x003A);vLCDTFTWriteData(0x0302);
    vLCDTFTWriteCommand(0x003B);vLCDTFTWriteData(0x0500);
    DelayMs(20);
    vLCDTFTWriteCommand(0x0022);
}

void vLCDTFT_Scroll_V(UINT16 y1){

    vLCDTFTWriteCommand(0x0007);vLCDTFTWriteData(0x0233); // Display Control
    // Vertical Scroll Control
    vLCDTFTWriteCommand(0x0041);vLCDTFTWriteData(y1); // Vertical Scroll Control
}

void vLCDTFTFillScreen(UINT16 Color){
    UINT32 i;
    vLCDTFTAddressSet(0,0,239,319);

    for(i=0;i<76800;i++){
        vLCDTFTWriteData(Color);
    }      
}

void vLCDTFTFillScreenH(UINT16 Color){
    UINT32 i;
    vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6038);     
    vLCDTFTAddressSetH(0,0,319,239);             
    for(i=0;i<76800;i++){
        vLCDTFTWriteData(Color);
    }    
    vLCDTFTWriteCommand(0x0011);vLCDTFTWriteData(0x6030);    
}

UINT16 uiLCDTFTGetPointCurrent(void){
	UINT16 result;

	mPORTGSetBits(LCD_PIN_RS);		// RS = 1 .. Data
    mPORTDClearBits(LCD_PIN_CS); 	// CS = 0
	mPORTDClearBits(LCD_PIN_RD);
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    result=PMDIN;
    mPORTDSetBits(LCD_PIN_RD);    
    mPORTDSetBits(LCD_PIN_CS);	// CS = 1
    
    return (result);
}

UINT16 uiLCDTFTGetPointCurrentII(void){
	UINT16 result;

	mPORTGSetBits(LCD_PIN_RS);		// RS = 1 .. Data
    mPORTDClearBits(LCD_PIN_CS); 	// CS = 0
	mPORTDClearBits(LCD_PIN_RD);
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    result=PMDIN;
    mPORTDSetBits(LCD_PIN_RD); 
    Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	mPORTDClearBits(LCD_PIN_RD);
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    result=PMDIN;
    mPORTDSetBits(LCD_PIN_RD);    
    mPORTDSetBits(LCD_PIN_CS);	// CS = 1
    
    return (result);
}
// *------------------------------------------------------------------------------*
void vLCDTFTAddColor(UINT16 x, UINT16 y,UINT16 Color){
	UINT16 Temp;
	
	vLCDTFTAddressSet(x,y,x,y);   
	Temp=uiLCDTFTGetPointCurrentII();  
	if((Temp&C_GROUP)==0){
		Temp=(Temp&F_SELEC)|Color;			
	}else if((Temp&Color)==0){
		Temp=(Color&F_SELEC)|Temp;	
	}else{
		Temp=(Temp&F_SELEC)|Color;	
	}
	vLCDTFTWriteCommand(0x004e);vLCDTFTWriteData(x);
    vLCDTFTWriteCommand(0x0022);
	vLCDTFTWriteData(Temp);// Temp
}
// *------------------------------------------------------------------------------*
void vLCDTFTEraseColor(UINT16 x, UINT16 y, UINT16 Color){
	UINT16 Temp;

	vLCDTFTAddressSet(x,y,x,y); 
	Temp=uiLCDTFTGetPointCurrentII();	
	if(((Temp&F_SELEC)&Color)!=0){ // El color a borrar esta presente?
		Temp=(Temp&F_SELEC)&(~(Color&F_SELEC)); // Solo dejamos flag del color a reponer
		if(Temp!=0){
			if((Temp&WAV_FLAG)!=0){
				Temp|=WAV_COLOR;
			}else if((Temp&GRD_FLAG)!=0){
				Temp|=GRD_COLOR;
			}	
		}		
	}
	vLCDTFTWriteCommand(0x004e);vLCDTFTWriteData(x);
    vLCDTFTWriteCommand(0x0022);
	vLCDTFTWriteData(Temp);
}
// *------------------------------------------------------------------------------*

UINT16 uiLCDTFTGetPoint(UINT16 x,UINT16 y){

	vLCDTFTAddressSetPoint(x,y);
	return(uiLCDTFTGetPointCurrent());
}

void vLCDTFTPoint(UINT16 x,UINT16 y,UINT16 Color){

    vLCDTFTAddressSetPoint(x,y);
    vLCDTFTWriteData(Color);
}
 
void vLCDTFTText(UINT16 x,UINT16 y,const char *PtrText,const char (*Fuente)[5],unsigned char Alto,UINT16 Color){
   UINT16 i, j, k, l, m, temp;           
   char DataPunto[5]; 
   const char *Ptr;
    
   while(*PtrText!='\0'){
      Ptr=(Fuente+*PtrText-' ')[0];
      for(i=0;i<5;i++){DataPunto[i]=*Ptr++;}
      switch(*PtrText){
         case '\n':
            y += 7*Alto + 1;
         break;
         case '\r':
            x = 0;
         break;
         default:
            if(x+5*Alto >= LCD_X_MAX){
                 x = 0;                           
                 y += 7*Alto + 1;                
              }
              for(j=0; j<5; ++j, x+=Alto){
                 for(k=0; k < 7; k++){
                    temp=(0x01<<k);
                    if((DataPunto[j]&temp)==temp){
                       for(l=0; l < Alto; ++l){                         
                          for(m=0; m < Alto; ++m){
                             vLCDTFTPoint(x+m,y+k*Alto+l,Color);
                          }
                       }
                    }
                 }
              }
              x++;
          break;
      } 
      *PtrText++;     
   }
}

void vLCDTFTTextH(UINT16 x,UINT16 y,const char *PtrText,const char (*Fuente)[5],UINT16 Color){
	UINT16 i, j, k, temp;           
	char DataPunto[5]; 
	const char *Ptr;
	
	while(*PtrText!='\0'){
		Ptr=(Fuente+*PtrText-' ')[0];
		for(i=0;i<5;i++){DataPunto[i]=*Ptr++;}
		if(y+5 >= LCD_Y_MAX){
			y = 0;                           
			x += 7 + 1;                
		}
		for(j=0; j<5; ++j, y++){
			for(k=0; k < 7; k++){
				temp=(0x01<<k);
				if((DataPunto[j]&temp)==temp){
					vLCDTFTPoint(x-k,y,Color);
				}
			}
		}
		y++;
		*PtrText++;     
	}
}

void vLCDTFTLine(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 Color){

   UINT16 dy, dx;
   INT16 addx=1, addy=1;
   INT16 P, diff;
   UINT16 i=0;

   diff=((INT16)x2-x1);
   if(diff<0) diff*=-1;
   dx=diff;
   diff=((INT16)y2-y1);
   if(diff<0) diff*=-1;
   dy=diff;


   if(x1 > x2)addx = -1;
   if(y1 > y2)addy = -1;
   if(dx >= dy){
      dy *= 2;
      P = dy - dx;
      diff = P - dx;
      for(;i<=dx;++i){
         vLCDTFTPoint(x1, y1, Color);
         if(P < 0){
            P  += dy;
            x1 += addx;
         }else{
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }else{
      dx *= 2;
      P = dx - dy;
      diff = P - dy;
      for(; i<=dy; ++i){
         vLCDTFTPoint(x1, y1, Color);
         if(P < 0){
            P  += dx;
            y1 += addy;
         }else{
            P  += diff;
            x1 += addx;
            y1 += addy;
         }
      }
   }
}


void vLCDTFTRectangle(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,BOOL Filled,UINT16 Color){
   UINT32 i,Lenght;
   
    if(Filled){
        Lenght=((UINT32)(x2-x1+1)*(y2-y1+1));  
       
        vLCDTFTAddressSet(x1,y1,x2,y2);      
        for(i=0;i<Lenght;i++){
            vLCDTFTWriteData(Color);                         
        }   
    }else{
        vLCDTFTLine(x1, y1, x2, y1, Color);     
        vLCDTFTLine(x1, y2, x2, y2, Color);
        vLCDTFTLine(x1, y1, x1, y2, Color);
        vLCDTFTLine(x2, y1, x2, y2, Color);
    }
}


void vLCDTFTCircle(UINT16 x,UINT16 y,UINT16 Radius,BOOL Filled,UINT16 Color){
    INT16  a, b, P;

    a = 0;
    b = Radius;
    P = 1 - Radius;

    do{
        if(Filled){
            vLCDTFTLine(x-a, y+b, x+a, y+b, Color);
            vLCDTFTLine(x-a, y-b, x+a, y-b, Color);
            vLCDTFTLine(x-b, y+a, x+b, y+a, Color);
            vLCDTFTLine(x-b, y-a, x+b, y-a, Color);
        }else{
            vLCDTFTPoint(a+x, b+y, Color);
            vLCDTFTPoint(b+x, a+y, Color);
            vLCDTFTPoint(x-a, b+y, Color);
            vLCDTFTPoint(x-b, a+y, Color);
            vLCDTFTPoint(b+x, y-a, Color);
            vLCDTFTPoint(a+x, y-b, Color);
            vLCDTFTPoint(x-a, y-b, Color);
            vLCDTFTPoint(x-b, y-a, Color);
        }
        if(P < 0) P += 3 + 2 * a++;
        else P += 5 + 2 * (a++ - b--);
    }while(a <= b);
}

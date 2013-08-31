#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_1
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "TouchCalibracion.h"
// *--------------------------------------------------------------------------------*
TOUCH_DATA TouchData;
volatile BOOL kbhit_irq=0;
volatile BOOL kbhit_tratament=0;
DATA_CALIBRACION CoefTouch2LCD={-0.000497,0.074856,-30.616973,-0.106301,-0.000272,382.063497};
// *--------------------------------------------------------------------------------*
void vCalibracionTouch(void);
// *--------------------------------------------------------------------------------*
void __ISR(_EXTERNAL_3_VECTOR, ipl2) Int3Handler(void){
	TOUCH_DATA Temp;
    
    if(kbhit_tratament==0){
    	// Lectura
    	vTestTouchPanel(&Temp);
    	// Conversion
    	vPuntosTouch2LCD(&CoefTouch2LCD,&Temp,&TouchData);    
                
    	kbhit_irq=1;
    	LED1_TOGGLE()
    }    
    mINT3ClearIntFlag();
}
// *--------------------------------------------------------------------------------*
int main(){
	TOUCH_DATA Temp;
	UINT16 CurrentColor=ColorBlack;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	DelayMs(100);
		
	LED1_OUTPUT();
	LED1_OFF();
	
	PORTSetPinsDigitalOut(IOPORT_D, BIT_1);		// Backlight del TFT
	mPORTDSetBits(BIT_1);
	vLCDTFTInit();	
	
	vInitADS7843();
	
	vCalibracionTouch();
	//ConfigINT3(EXT_INT_PRI_2 | FALLING_EDGE_INT | EXT_INT_ENABLE);
    //INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    //INTEnableInterrupts();
    //vLCDTFTRectangle(0,0,239,319,1,ColorWhite);
    //vLCDTFTRectangle(2,2,237,317,0,ColorBlack);
    
    vLCDTFTRectangle(0,0,239,319,1,ColorWhite);
    vLCDTFTRectangle(0,237,39,277,1,ColorWhite);
    vLCDTFTRectangle(40,237,79,277,1,ColorBlack);
    vLCDTFTRectangle(80,237,119,277,1,ColorRed);
    vLCDTFTRectangle(120,237,159,277,1,ColorBlue);
    vLCDTFTRectangle(160,237,199,277,1,ColorGreen);
    vLCDTFTRectangle(200,237,239,277,1,ColorYellow);
    vLCDTFTRectangle(0,237,239,277,0,ColorBlack);
    vLCDTFTText(72,288,"BORRAR",ARIAL,3,ColorBlack);
	while(1){
		if(ADS7843_PIN_IRQ==0){
			vTestTouchPanel(&Temp);
    		vPuntosTouch2LCD(&CoefTouch2LCD,&Temp,&TouchData); 
    		vLCDTFTPoint(TouchData.x,TouchData.y, CurrentColor);
			DelayMs(2);
		}  		
	}
}
// *-------------------------------------------------------------------------*
void vCalibracionTouch(void){
	TOUCH_DATA DatosTouch[9], DatosLCD[9];
	
	DatosLCD[0].x=25;
    DatosLCD[0].y=25;
    
    DatosLCD[1].x=120;
    DatosLCD[1].y=25;
    
    DatosLCD[2].x=214;
    DatosLCD[2].y=25;
      
    DatosLCD[3].x=25;
    DatosLCD[3].y=160;
    
    DatosLCD[4].x=120;
    DatosLCD[4].y=160;  
    
    DatosLCD[5].x=214;
    DatosLCD[5].y=160;
    
    DatosLCD[6].x=25;
    DatosLCD[6].y=294;
    
    DatosLCD[7].x=120;
    DatosLCD[7].y=294;
    
    DatosLCD[8].x=214;
    DatosLCD[8].y=294;
    
    vAdquirirPuntosTouch(&DatosTouch[0],&DatosLCD[0],9);
    vCalibrarTouch(&CoefTouch2LCD,&DatosTouch[0],&DatosLCD[0],9);
}
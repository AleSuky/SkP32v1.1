/**
   \version: 1.0

   
   \author Suky (Casanova Alejandro) 
   \web www.micros-designs.com.ar
   \date 14/09/10


///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2010 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
/////////////////////////////////////////////////////////////////////////// 
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 14/09/10      Suky               Original (Rev 1.0)                        *
 *----------------------------------------------------------------------------* 

 */ 
#include "..\include\Driver LCD.h"

UINT8 NLinea;
static xSemaphoreHandle xLCDMutex = NULL;
portTickType xBlockTimeMutexLCD=400;//portMAX_DELAY;
// *------------------------------------------*
UINT8 ui8BusyLCD(void){

#ifdef LCD_USE_RW
	LCD_DATA_PIN_7 = 0;
	LCD_DATA_PIN_6 = 0;
	LCD_DATA_PIN_5 = 0;
	LCD_DATA_PIN_4 = 0;

	LCD_TRIS_DATA_PIN_7 = CONFIG_INPUT;
	LCD_TRIS_DATA_PIN_6 = CONFIG_INPUT;
	LCD_TRIS_DATA_PIN_5 = CONFIG_INPUT;
	LCD_TRIS_DATA_PIN_4 = CONFIG_INPUT;

	LCD_RW_PIN = 1;    
	LCD_RS_PIN = 0; 
	LCD_E_PIN=1;         
	__delay_1us();

	if(LCD_READ_PIN_7==1){
		LCD_E_PIN = 0; 
		__delay_1us();
		LCD_E_PIN = 1;
		__delay_1us();
		LCD_E_PIN = 0;
		LCD_RW_PIN = 0; 
		return 1;
	}else{
		LCD_E_PIN = 0;
		__delay_1us();
		LCD_E_PIN = 1;
		__delay_1us();
		LCD_E_PIN = 0;
		LCD_RW_PIN = 0;       
		return 0;
	}
#else
	vTaskDelay(1/portTICK_RATE_MS);
	return 0;
#endif
}

void vWriteLCD(CHAR8 Data,UINT8 Type){

#ifdef LCD_USE_3PINES
	UINT8 i, data_temp;
#endif

	while(ui8BusyLCD());

	#ifndef LCD_USE_3PINES
		#ifdef LCD_USE_RW
			LCD_RW_PIN = 0;
		#endif   
		if(Type){
			LCD_RS_PIN=1;
		}else{
			LCD_RS_PIN = 0;
		}	  
		LCD_TRIS_DATA_PIN_7 = CONFIG_OUTPUT;
		LCD_TRIS_DATA_PIN_6 = CONFIG_OUTPUT;
		LCD_TRIS_DATA_PIN_5 = CONFIG_OUTPUT;
		LCD_TRIS_DATA_PIN_4 = CONFIG_OUTPUT;
		
		LCD_DATA_PIN_7 = !!(Data & 0x80);
		LCD_DATA_PIN_6 = !!(Data & 0x40);
		LCD_DATA_PIN_5 = !!(Data & 0x20);
		LCD_DATA_PIN_4 = !!(Data & 0x10);
	#else
		data_temp=(Data>>4);  // Rs es bit 4
		if(Type){
			data_temp|=0x10;
		}
		for(i=0;i<8;i++){
			LCD_DATA_PIN=!!(data_temp & 0x80);
			data_temp<<=1;
			LCD_CLOCK_PIN=1;
			__delay_1us();
			LCD_CLOCK_PIN=0;
		}
	#endif
	__delay_1Cycle();
	LCD_E_PIN = 1;
	__delay_1us();
	LCD_E_PIN = 0;
	#ifndef LCD_USE_3PINES	
		LCD_DATA_PIN_7 = !!(Data & 0x08);
		LCD_DATA_PIN_6 = !!(Data & 0x04);
		LCD_DATA_PIN_5 = !!(Data & 0x02);
		LCD_DATA_PIN_4 = !!(Data & 0x01);
	#else
		data_temp=(Data&0x0F);  // Rs es bit 4
		if(Type){
			data_temp|=0x10;
		}
		for(i=0;i<8;i++){
			LCD_DATA_PIN=!!(data_temp & 0x80);
			data_temp<<=1;
			LCD_CLOCK_PIN=1;
			__delay_1us();
			LCD_CLOCK_PIN=0;
		}
	#endif
	__delay_1Cycle();	
	LCD_E_PIN = 1;
	__delay_1us();
	LCD_E_PIN = 0;	
} 

void vInitLCD(){
	UINT8 i;
#ifdef LCD_USE_3PINES
	UINT8 temp;
#endif
	xLCDMutex=xSemaphoreCreateMutex();

	vTaskDelay(20/portTICK_RATE_MS);
	NLinea=1;
	// Tomamos el recurso sin esperar nada.-
	xSemaphoreTake(xLCDMutex,0);
#ifndef LCD_USE_3PINES
/* ** Configuración de pines ** */	
	LCD_DATA_PIN_7 = 0;
	LCD_DATA_PIN_6 = 0;
	LCD_DATA_PIN_5 = 0;
	LCD_DATA_PIN_4 = 0;
	#ifdef LCD_USE_RW
		LCD_RW_PIN = 0;
	#endif
	LCD_RS_PIN = 0;
	LCD_E_PIN = 0;
	
	LCD_TRIS_DATA_PIN_7 = CONFIG_OUTPUT;
	LCD_TRIS_DATA_PIN_6 = CONFIG_OUTPUT;
	LCD_TRIS_DATA_PIN_5 = CONFIG_OUTPUT;
	LCD_TRIS_DATA_PIN_4 = CONFIG_OUTPUT;
	#ifdef LCD_USE_RW	
		LCD_TRIS_RW = CONFIG_OUTPUT;
	#endif
	LCD_TRIS_RS = CONFIG_OUTPUT;
	LCD_TRIS_E = CONFIG_OUTPUT;
#else
	LCD_DATA_PIN = 0;
	LCD_CLOCK_PIN = 0;
	LCD_E_PIN = 0;

	LCD_TRIS_DATA = CONFIG_OUTPUT;
	LCD_TRIS_CLOCK = CONFIG_OUTPUT;
	LCD_TRIS_E = CONFIG_OUTPUT;
	
	for(i=0;i<8;i++){
		LCD_DATA_PIN=0;
		LCD_CLOCK_PIN=1;
		__delay_1us();
		LCD_CLOCK_PIN=0;
	}
#endif
/* ** INICIALIZACION ** */     
#ifndef LCD_USE_3PINES
	LCD_DATA_PIN_5 = 1;
	LCD_DATA_PIN_4 = 1;
#else
	temp=0x03;
	for(i=0;i<8;i++){
		LCD_DATA_PIN=!!(temp & 0x80);
		temp<<=1;
		LCD_CLOCK_PIN=1;
		__delay_1us();
		LCD_CLOCK_PIN=0;
	}
#endif
	for(i=0;i<3;i++){
		LCD_E_PIN = 1;
		vTaskDelay(2/portTICK_RATE_MS);
		LCD_E_PIN = 0;
	 	vTaskDelay(2/portTICK_RATE_MS);
	}
#ifndef LCD_USE_3PINES
	LCD_DATA_PIN_4 = 0;
#else
	temp=0x02;
	for(i=0;i<8;i++){
		LCD_DATA_PIN=!!(temp & 0x80);
		temp<<=1;
		LCD_CLOCK_PIN=1;
		__delay_1us();
		LCD_CLOCK_PIN=0;
	}
#endif
	LCD_E_PIN = 1;
	__delay_1us();
	LCD_E_PIN = 0;

	vWriteLCD(0x20|(LcdType<<2),LCD_COMMAND);  // Tipo display.-  
	vTaskDelay(2/portTICK_RATE_MS);    
	vWriteLCD(0x01,LCD_COMMAND);	// Borramos display.-   
	vTaskDelay(2/portTICK_RATE_MS);         
	vWriteLCD(0x06,LCD_COMMAND);	// Incrementa cursor.-
	vWriteLCD(0x0C,LCD_COMMAND);	// Encendemos display.-
	
	vTaskDelay(1/portTICK_RATE_MS);
	xSemaphoreGive(xLCDMutex); 
}
// -------------------------------------------------------
void vLCDPutc(CHAR8 Data){
	switch(Data){
		case '\f':
			vWriteLCD(0x01,LCD_COMMAND);
			NLinea=1;
			vTaskDelay(2/portTICK_RATE_MS);
		break;
		case '\n':
			vGotoxyLCD(1,++NLinea);			
		break;
		default:
			vWriteLCD(Data,LCD_DATA);
	}
}
void vGotoxyLCD(UINT8 x,UINT8 y){
UINT8 Direccion;

	switch(y){
		case 1:Direccion = LCD_LINE_1_ADDRESS;NLinea=1;break;
		case 2:Direccion = LCD_LINE_2_ADDRESS;NLinea=2;break;
		#ifdef LCD_4LINES
		case 3:Direccion = LCD_LINE_3_ADDRESS;NLinea=3;break;
		case 4:Direccion = LCD_LINE_4_ADDRESS;NLinea=4;break;
		#endif
		default:Direccion = LCD_LINE_1_ADDRESS;NLinea=1;break;
	}

	Direccion+=x-1;
	vWriteLCD(0x80|Direccion,LCD_COMMAND);
}
// *----------------------------------------------------------------*
portCHAR cLCDPutc(CHAR8 Data){
	// Intentamos tomar el recurso....
	if(xSemaphoreTake(xLCDMutex,(portTickType)xBlockTimeMutexLCD)!=pdTRUE){
		return(-1);
	}
	switch(Data){
		case '\f':
			vWriteLCD(0x01,LCD_COMMAND);
			NLinea=1;
			vTaskDelay(2/portTICK_RATE_MS);
		break;
		case '\n':
			vGotoxyLCD(1,++NLinea);			
		break;
		default:
			vWriteLCD(Data,LCD_DATA);
	}
   xSemaphoreGive(xLCDMutex);  
   return(1); 
}

portCHAR cLCDPutrs(UINT8 x, UINT8 y, const CHAR8 *Data){
	
	// Intentamos tomar el recurso....
	if(xSemaphoreTake(xLCDMutex,(portTickType)xBlockTimeMutexLCD)!=pdTRUE){
		return(-1);
	}
   if((x!=0)&&(y!=0)){
		vGotoxyLCD(x,y);
	}
	while(*Data!='\0'){
		vLCDPutc(*Data++);
	}
   xSemaphoreGive(xLCDMutex);   
   return(1);
}

portCHAR cLCDPuts(UINT8 x, UINT8 y, CHAR8 *Data){
	
	// Intentamos tomar el recurso....
	if(xSemaphoreTake(xLCDMutex,(portTickType)xBlockTimeMutexLCD)!=pdTRUE){
		return(-1);
	}
   if((x!=0)&&(y!=0)){
		vGotoxyLCD(x,y);
	}
	while(*Data!='\0'){
		vLCDPutc(*Data++);
	}
   xSemaphoreGive(xLCDMutex);   
   return(1);
}
portCHAR cGotoxyLCD(UINT8 x,UINT8 y){
UINT8 Direccion;

	// Intentamos tomar el recurso....
	if(xSemaphoreTake(xLCDMutex,(portTickType)xBlockTimeMutexLCD)!=pdTRUE){
		return(-1);
	}
	switch(y){
		case 1:Direccion = LCD_LINE_1_ADDRESS;NLinea=1;break;
		case 2:Direccion = LCD_LINE_2_ADDRESS;NLinea=2;break;
		#ifdef LCD_4LINES
		case 3:Direccion = LCD_LINE_3_ADDRESS;NLinea=3;break;
		case 4:Direccion = LCD_LINE_4_ADDRESS;NLinea=4;break;
		#endif
		default:Direccion = LCD_LINE_1_ADDRESS;NLinea=1;break;
	}

	Direccion+=x-1;
	vWriteLCD(0x80|Direccion,LCD_COMMAND);
	xSemaphoreGive(xLCDMutex);   
	return(1);
}

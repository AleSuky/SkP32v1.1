#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_2
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "ff.h"
// *--------------------------------------------------------------------------------*
FATFS SD_FS;
FIL file;
BYTE buffer[50]="Probando memoria con FSFAT y PIC32\n\r";
BYTE temp[50];
// *--------------------------------------------------------------------------------*

int main(void){
	FRESULT err,res;
	UINT br, bw;
	UINT32 Count=0xFFFFF; 
	
	
	mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED3_OUTPUT();
	LED4_OUTPUT();
	
	LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();
	
	err = f_mount(0, &SD_FS);
	if (err == FR_OK) {
		f_open(&file, "dstfile.txt", FA_CREATE_ALWAYS | FA_WRITE);
		f_write(&file,buffer,36,&bw);
		f_close(&file);
		if(bw!=36){
			LED1_TOGGLE();
		}
		
		f_open(&file, "dstfile.txt", FA_READ);
		f_read(&file,temp,36,&br);
		f_close(&file);
		if(br!=36){
			LED2_TOGGLE();
		}
		
		f_open(&file, "dstfile2.txt", FA_CREATE_ALWAYS | FA_WRITE);
		f_write(&file,temp,36,&bw);		
		f_close(&file);
		if(bw!=36){
			LED3_TOGGLE();
		}
	}
	while(1){
		if(--Count==0){
			Count=0xFFFFF;
			LED4_TOGGLE();
		}
	}
}
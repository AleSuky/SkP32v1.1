#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_1, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
#include "MDD File System/FSIO.h"
// *--------------------------------------------------------------------------------*
char MyBuffer[100]="Creación de archivo mediante libreria de Microchip\r\nby Suky...\r\n\r\n";
// *--------------------------------------------------------------------------------*
int main(){
	FSFILE *MyFile;
	rtccTime tm;		
	rtccDate dt;
	UINT8 k,err;
	char *Sc;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED1_OFF();
	LED2_OFF();
	
	//Initialize the RTCC
	RtccInit();
	while(RtccGetClkStat()!=RTCC_CLK_ON);
	
	tm.l=0;
	tm.sec=0x30;
	tm.min=0x07;
	tm.hour=0x19;
	dt.wday=2;
	dt.mday=0x21;
	dt.mon=0x11;
	dt.year=0x11;
	RtccSetTimeDate(tm.l, dt.l);
	
	SD_CD_TRIS=1; // Deteccion de memoria.
	while(SD_CD==1);
	k=0;
	do{
		DelayMs(50);
		err=FSInit();
		k++;      	 	
	}while((k<10) && (err==FALSE));
	if((k==10) && (err==FALSE)){
		// Error...	
		LED1_ON();
	}else{	
		LED2_ON();
		// w Abre archivo para escritura, si existe sobre-escribe
		// a Abre archivo para escritura, si existe continua agregando datos al final.
		MyFile = FSfopen("ARCHIVO.TXT","a+");
		for(Sc=&MyBuffer[0];*Sc!=0;Sc++);
		k=Sc-&MyBuffer[0];
		FSfwrite(&MyBuffer[0],1,k,MyFile);
		FSfclose(MyFile);	
	}	
	while(1){

	}
}

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
#include "SST25VF016.h"
// *--------------------------------------------------------------------------------*
char Text[35]="Prueba de almacenamiento en EEPROM";
// *--------------------------------------------------------------------------------*
int main(){
	DRV_SPI_INIT_DATA ConfigSPI;
	char err;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	LED1_OUTPUT();
	LED2_OUTPUT();
	LED1_OFF();
	LED2_OFF();
	
	ConfigSPI.channel=2;
	ConfigSPI.baudRate=1; 	// 20 MHz = 80 Mhz/(2*(Brg+1))
	ConfigSPI.cke=1;		// MODE_11, Sample Middle (Misma SD Card)
	ConfigSPI.ckp=0;
	ConfigSPI.smp=0;
	ConfigSPI.mode=0b00; 	// 8-bits
	SST25Init(&ConfigSPI); 	// Configuracion SPI.
	SST25SectorErase(0x0000);
	err=SST25WriteArray(0x0000,Text,34); 
	if(err==0){
		LED2_ON();	// Error
	}else{
		LED1_ON(); // Ok
	}
	while(1){
	}
}

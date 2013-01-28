#include <p32xxxx.h>
/** CONFIGURATION **************************************************/
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_1, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_1
#pragma config CP=OFF, BWP=OFF, PWP=OFF
/** END CONFIGURATION **************************************************/
#include <plib.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Driver LCD.h"
#include "HardwareProfile.h"

#define PRIORITY_TASK0      ( tskIDLE_PRIORITY + 1 )
#define PRIORITY_TASK1      ( tskIDLE_PRIORITY + 1 )
#define PRIORITY_TASK2      ( tskIDLE_PRIORITY + 1 )
/*************************** Tasks Prototypes ****************************/
static void vTASK0( void *pvParameters );
static void vTASK1( void *pvParameters );
static void vTASK2( void *pvParameters );
void _itoa(WORD Value, CHAR8* Buffer);
CHAR8 Text[5],Text2[5];
WORD Count=0,Count2=0;
/*-----------------------------------------------------------*/
int main( void ){

    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	/* Setup to use the external interrupt controller. */
	INTEnableSystemMultiVectoredInt();
	portDISABLE_INTERRUPTS();
	
	TRISBbits.TRISB8=0;
	TRISBbits.TRISB9=0;
	TRISBbits.TRISB3=0;
	LATBbits.LATB3=1;
	LATBbits.LATB8=0;
	LATBbits.LATB9=0;
	
	vPortInitialiseBlocks();
	xTaskCreate( vTASK0, ( const char * const ) "T0", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK0, NULL );
    vTaskStartScheduler();
}
/*-----------------------------------------------------------*/
static void vTASK0( void *pvParameters ){
    while(1)
    {
        vInitLCD();
        xTaskCreate( vTASK1, ( const char * const ) "T1", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK1, NULL );
        xTaskCreate( vTASK2, ( const char * const ) "T2", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK2, NULL );
        vTaskDelete(NULL);      
    }
}
/*-----------------------------------------------------------*/
static void vTASK1( void *pvParameters ){

    while(1){
	    LATBbits.LATB8=!PORTBbits.RB8;
        cLCDPutrs(5,1,"    ");				// Borra sector (x=5, linea 1)
        _itoa(Count2,&Text[0]);				// Convierte a string contador
        cLCDPuts(5,1,&Text[0]);				// Escribe en LCD
        Count2++;							// Incrementa
        vTaskDelay(1200/portTICK_RATE_MS);	// Demora
    }
}
/*-----------------------------------------------------------*/
static void vTASK2( void *pvParameters ){   
    while(1){
	    LATBbits.LATB9=!PORTBbits.RB9;
        cLCDPutrs(5,3,"    ");
        _itoa(Count,&Text2[0]);
        cLCDPuts(5,3,&Text2[0]);
        Count++;
        vTaskDelay(600/portTICK_RATE_MS);
    }
}
/*-----------------------------------------------------------*/
void vApplicationStackOverflowHook( void )
{
	/* Look at pxCurrentTCB to see which task overflowed its stack. */
	for( ;; );
}
/*-----------------------------------------------------------*/
void _general_exception_handler( unsigned portLONG ulCause, unsigned portLONG ulStatus )
{
	/* This overrides the definition provided by the kernel.  Other exceptions 
	should be handled here. */
	for( ;; );
}
/*-----------------------------------------------------------*/
void _itoa(WORD Value, CHAR8* Buffer){
	BYTE i;
	WORD Digit;
	WORD Divisor;
	BOOL Printed = FALSE;

	if(Value){
		for(i = 0, Divisor = 10000; i < 5u; i++){
			Digit = Value/Divisor;
			if(Digit || Printed){
				*Buffer++ = '0' + Digit;
				Value -= Digit*Divisor;
				Printed = TRUE;
			}
			Divisor /= 10;
		}
	}else{
		*Buffer++ = '0';
	}
	*Buffer = '\0';
}

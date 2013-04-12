#include <p32xxxx.h>
/** CONFIGURATION **************************************************/
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config UPLLEN=ON, UPLLIDIV=DIV_2
#pragma config CP=OFF, BWP=OFF, PWP=OFF
/** END CONFIGURATION **************************************************/
#include <plib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "HardwareProfile.h"

#define PRIORITY_TASK0		( tskIDLE_PRIORITY + 1 )
#define PRIORITY_TASK1		( tskIDLE_PRIORITY + 2 )
/*************************** Tasks Prototypes ****************************/
static void vTASK0( void *pvParameters );
static void vTASK1( void *pvParameters );
/*-----------------------------------------------------------*/
int main( void ){
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	/* Setup to use the external interrupt controller. */
	INTEnableSystemMultiVectoredInt();
	portDISABLE_INTERRUPTS();
	
	TRISBbits.TRISB8=0;
	TRISBbits.TRISB9=0;
	vPortInitialiseBlocks();

	xTaskCreate( vTASK0, ( const char * const ) "T0", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK0, NULL );
	xTaskCreate( vTASK1, ( const char * const ) "T1", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK1, NULL );

	vTaskStartScheduler();
}
/*-----------------------------------------------------------*/
static void vTASK0( void *pvParameters ){
	while(1){
		LATBbits.LATB8=!PORTBbits.RB8;
		vTaskDelay(250/portTICK_RATE_MS);
	}
}
/*-----------------------------------------------------------*/
static void vTASK1( void *pvParameters ){
	while(1){
		LATBbits.LATB9=!PORTBbits.RB9;
		vTaskDelay(350/portTICK_RATE_MS);
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
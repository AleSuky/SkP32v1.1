#include <p32xxxx.h>
#include <plib.h>
// *--------------------------------------------------------------------------------*
// Cristal de 4MHz.-
// SYSCLK = 80 MHz (4MHz Cristal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// FPLLDIV 1:1, PLLMULT x20, PLLODIV 1:1. -> 80MHz
// FPBDIV 1:1 -> 80MHz
#pragma config FPLLODIV=DIV_1, FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPBDIV=DIV_1
#pragma config FWDTEN=OFF, FCKSM=CSDCMD, POSCMOD=XT, FNOSC=PRIPLL
#pragma config CP=OFF, BWP=OFF, PWP=OFF
// *--------------------------------------------------------------------------------*
#include "HardwareProfile.h"
// *--------------------------------------------------------------------------------*

// *--------------------------------------------------------------------------------*
// *--------------------------------------------------------------------------------*
void __ISR(_UART2_VECTOR, ipl2) ISRUart2(void){
	unsigned char Temp;

	if(INTGetFlag(INT_SOURCE_UART_RX(UART2))){
	    INTClearFlag(INT_SOURCE_UART_RX(UART2));

		Temp=UARTGetDataByte(UART2);
		UARTSendDataByte(UART2,Temp);

	}
	/*if(INTGetFlag(INT_SOURCE_UART_TX(UART2))){
		INTClearFlag(INT_SOURCE_UART_TX(UART2));
	}*/
}
void __ISR(_UART1_VECTOR, ipl2) ISRUart1(void){
	unsigned char Temp;

	if(INTGetFlag(INT_SOURCE_UART_RX(UART1))){
	    INTClearFlag(INT_SOURCE_UART_RX(UART1));

		Temp=UARTGetDataByte(UART1);
		UARTSendDataByte(UART1,Temp);

	}
	/*if(INTGetFlag(INT_SOURCE_UART_TX(UART1))){
		INTClearFlag(INT_SOURCE_UART_TX(UART1));
	}*/
}
// *--------------------------------------------------------------------------------*
void vUARTPuts(UART_MODULE id,const char *Ptr){

	while(*Ptr!='\0'){
		while(!UARTTransmitterIsReady(id));
    	UARTSendDataByte(id, *Ptr++);
	}
}
// *--------------------------------------------------------------------------------*
int main(){
	char Text[20];
	unsigned char Valor1=126;
	float Valor2=456.342;
	
    mJTAGPortEnable(0);							// JTAG des-habilitado
	SYSTEMConfigPerformance(GetSystemClock()); 	// Activa pre-cache.-
	
	UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY); // Habilita pines Tx y Rx.
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY); // INT_Tx cuando el buffer tiene espacio para otro caracter.
    																						// INT_Rx cuando el buffer tiene un byte.
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);	// 8:N:1
    UARTSetDataRate(UART2, GetPeripheralClock(), 19200);									// 19200	
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));				// Modulo encedido, Tx y Rx encendido
    
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY); // Habilita pines Tx y Rx.
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY); // INT_Tx cuando el buffer tiene espacio para otro caracter.
    																						// INT_Rx cuando el buffer tiene un byte.
    UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);	// 8:N:1
    UARTSetDataRate(UART1, GetPeripheralClock(), 19200);									// 19200	
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));				// Modulo encedido, Tx y Rx encendido
    
    vUARTPuts(UART2,"Iniciando comunicacion serial por UART 2, SkP32\r\n");
    sprintf(&Text[0],"-->%u,%3.2f<--",Valor1,Valor2);
    vUARTPuts(UART2,(const char *)&Text[0]);
    
    vUARTPuts(UART1,"Iniciando comunicacion serial por UART 1, SkP32\r\n");
    
    // Configuramos interrupcion por Rx UART2
	INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
    INTSetVectorPriority(INT_UART_2_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_UART_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    
    // Configuramos interrupcion por Rx UART1
	INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
    INTSetVectorPriority(INT_UART_1_VECTOR, INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_UART_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);

    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
	while(1){
	}
}

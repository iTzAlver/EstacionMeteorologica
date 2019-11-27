/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		UART0.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que recoge la transmisión por UART0.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes a la transmisión asíncrona.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	UART0
#define	UART0
#include	"UART0.h"
#endif


void	__configuraUART0__()					//	Configurado a 9600 baudios.
{
	LPC_SC->PCONP			=	(1	<<	3);	//	Activo el bit de power para la UART0.
	LPC_PINCON->PINSEL0		|=	(1	<<	4)	//	P0.2	como TXD0.
						|	(1	<<	6);	// 	P0.2 como RXD0.
	
	LPC_UART0->LCR			|=	(0x3	<<	0);	//	Palabras de 1 byte.
	LPC_UART0->LCR			&=	~(1	<<	2)	//	Un bit de stop.
						|	~(1	<<	3);	//	Sin bit de paridad.
	
	LPC_UART0->LCR			&=	~(1	<<	DLP);		//	Activo el latch.
	LPC_UART0->DLL			=	163;					//	9600 baudios. -> 9645,06 el real.
	LPC_UART0->DLM			=	0;					//	No supera 255;
	LPC_UART0->FDR;								//	No toco el FR, no hay mucha variación.	
	LPC_UART0->LCR			|=	 (1	<<	DLP);		//	Desactivo el latch.
	
	LPC_UART0->IER			=	(	0x3	);	//	Activo interrupción por TX y RX.
	NVIC_EnableIRQ(	UART0_IRQn	);		//	Activo el manejador de la interrupción.
}

/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

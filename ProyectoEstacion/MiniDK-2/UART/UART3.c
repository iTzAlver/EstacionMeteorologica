/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		UART3.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que recoge la transmisi�n por UART3.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes a la transmisi�n as�ncrona.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	UART3
#define	UART3
#include	"UART3.h"
#endif
//	Variables globales y externas.
char	UART3_BUFFER_RX[CADMAX + 1];
char UART3_BUFFER_TX[CADMAX + 1];
static char * _prx	=	UART3_BUFFER_RX;
static char * _ptx	=	UART3_BUFFER_TX;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraUART3__()															//
//																								//
//		@brief		Esta funci�n es la que configura el UART3 para transmisi�n y recepci�n.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART3__(	void	)				//	Configurado a 9600 baudios.
{
	LPC_SC->PCONP			=	(1	<<	25);	//	Activo el bit de power para la UART3.
	LPC_PINCON->PINSEL0		|=	(1	<<	4)	//	P0.2	como TXD3.
						|	(1	<<	6);	// 	P0.2 como RXD3.
	
	LPC_UART3->LCR			|=	(0x3	<<	0);	//	Palabras de 1 byte.
	LPC_UART3->LCR			&=	~(1	<<	2)	//	Un bit de stop.
						|	~(1	<<	3);	//	Sin bit de paridad.
	
	LPC_UART3->LCR			&=	~(1	<<	DLP);		//	Activo el latch.
	LPC_UART3->DLL			=	163;					//	9600 baudios. -> 9645,06 el real.
	LPC_UART3->DLM			=	0;					//	No supera 255;
	LPC_UART3->FDR;								//	No toco el FR, no hay mucha variaci�n.	
	LPC_UART3->LCR			|=	 (1	<<	DLP);		//	Desactivo el latch.
	
	LPC_UART3->IER			=	(1	<<	2);	//	Activo interrupci�n por RX lleno.
	
	NVIC_EnableIRQ(	UART3_IRQn	);		//	Activo el manejador de la interrupci�n.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__ignore()																	//
//																								//
//		@brief		Esta funci�n no hace nada.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
static void __ignore(	void	)
{
	/**	@DO:	No hace nada.	*/
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__recibirDatos()																//
//																								//
//		@brief		Esta subfunci�n de apoyo para el handler del uart3, se encarga de recibir datos.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
static void __recibirDatos(	void	)
{
	*_prx = LPC_UART3->RBR;					//	Guardo el byte que ha llegado.
	
	if	(*_prx 	== 	RetornoDeCarro)		//	Si es el �ltimo byte...
	{
		*_prx 	= 	NULL;				//	Se a�ade el caracter null en vez de el retorno de carro.			
		_prx		=	UART3_BUFFER_RX;		//	Vuelve al inicio del buffer.
	}
	else									//	Si no es el �ltimo byte...
	{
		_prx++;							//	Cargo la siguiente posici�n en el puntero.
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__transmitirDatos()																//
//																								//
//		@brief		Esta subfunci�n de apoyo para el handler del uart3, se encarga de transmitir datos.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
static void __transmitirDatos(	void	)
{
	if	(*_ptx	==	NULL)				//	Si es el fin de la cadena...
	{
		LPC_UART3->THR	=	RetornoDeCarro;	//	Mando el retorno de carro.
		_ptx			=	UART3_BUFFER_TX;	//	Vuelve al inicio del buffer.
		LPC_UART3->IER	&=	~(1	<<	1);		//	Desactivo interrupci�n por buffer TX vac�o.		
	}
	else									//	Si no es el fin de la cadena...
	{
		LPC_UART3->THR	=	*_ptx;			//	Mando el caracter.
		_ptx++;							//	Cargo la siguiente muestra en el puntero.
	}
	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		UART3_mandaBufferTx()															//
//																								//
//		@brief		Esta funci�n manda el UART0_BUFFER_TX a la salida TX del UART3.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void UART3_MandaBufferTx(	void	)
{
	if	(	(LPC_UART3->IER & (	1	<<	1))	==	0)	//	Si no hay transmisi�n pendiente...
	{
		LPC_UART3->IER	|=	(1	<<	1);	//	Activo interrupci�n por buffer TX vac�o.
		LPC_UART3->THR	=	*_ptx;		//	Env�o el primer caracter.
		_ptx++;						//	Cargo el siguiente caracter.
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		UART3_IRQHandler()																//
//																								//
//		@brief		Este es el handler de la interrupci�n por UART3, tiene dos modos: recepci�n y transmisi�n;	//
//					para recepci�n se llama a la subfunci�n __recibirDatos() y __transmitirDatos() para			//
//					transmisi�n.																	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void UART3_IRQHandler()
{
	(LPC_UART0->IIR & UART3_MRX) ? __recibirDatos()	:	__ignore();
	(LPC_UART0->IIR & UART3_MTX) ? __transmitirDatos():	__ignore();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																															//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

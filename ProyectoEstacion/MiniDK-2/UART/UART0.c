/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		UART0.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que recoge la transmisi�n por UART0.								//
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
#ifndef	UART0
#define	UART0
#include	"UART0.h"
#endif
//	Variables globales y externas.
char	UART0_BUFFER_RX[CADMAX + 1];
char UART0_BUFFER_TX[CADMAX + 1];
static char * _prx	=	UART0_BUFFER_RX;
uint8_t	  _pprx = 0;
static char * _ptx	=	UART0_BUFFER_TX;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraUART0__()															//
//																								//
//		@brief		Esta funci�n es la que configura el UART0 para transmisi�n y recepci�n.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART0__(	void	)				//	Configurado a 9600 baudios.
{
	LPC_SC->PCONP			|=	(1	<<	3);	//	Activo el bit de power para la UART0.
	LPC_PINCON->PINSEL0		|=	(1	<<	4)	//	P0.2	como TXD0.
						|	(1	<<	6);	// 	P0.2 como RXD0.
	
	LPC_UART0->LCR			|=	(0x3	<<	0);	//	Palabras de 1 byte.
	LPC_UART0->LCR			&=	~(1	<<	2)	//	Un bit de stop.
						|	~(1	<<	3);	//	Sin bit de paridad.
	
	LPC_UART0->LCR			|=	(1	<<	DLP);		//	Activo el latch.
	LPC_UART0->DLL			=	163;					//	9600 baudios. -> 9645,06 el real.
	LPC_UART0->DLM			=	0;					//	No supera 255;
	LPC_UART0->FDR;								//	No toco el FR, no hay mucha variaci�n.	
	LPC_UART0->LCR			&=	 ~(1	<<	DLP);		//	Desactivo el latch.
	
	LPC_UART0->IER			=	(1	<<	2);	//	Activo interrupci�n por RX lleno.
	strcpy(UART0_BUFFER_TX	,	"Hola.\n\r");
	UART0_MandaBufferTx();
	
	NVIC_EnableIRQ(	UART0_IRQn	);		//	Activo el manejador de la interrupci�n.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__recibirDatos()																//
//																								//
//		@brief		Esta subfunci�n de apoyo para el handler del uart0, se encarga de recibir datos.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
static void __recibirDatos(	void	)
{
	uint32_t var = LPC_UART0->RBR;
//	*_prx = var;					//	Guardo el byte que ha llegado.
//	
//	if	(*_prx 	== 	RetornoDeCarro)		//	Si es el �ltimo byte...
//	{
//		*_prx 	= 	NULL;				//	Se a�ade el caracter null en vez de el retorno de carro.			
//		_prx		=	UART0_BUFFER_RX;		//	Vuelve al inicio del buffer.
//		procesarComando(	UART0_BUFFER_RX);	//	Proceso el comando recibido.
//	}
//	else									//	Si no es el �ltimo byte...
//	{
//		_prx++;							//	Cargo la siguiente posici�n en el puntero.
//	}
	UART0_BUFFER_RX[_pprx] = var;
	if	(var 	== 	RetornoDeCarro)		//	Si es el �ltimo byte...
	{
		UART0_BUFFER_RX[_pprx]	= 	NULL;	//	Se a�ade el caracter null en vez de el retorno de carro.			
		_pprx		=	0;				//	Vuelve al inicio del buffer.
		procesarComando(	UART0_BUFFER_RX);	//	Proceso el comando recibido.
	}
	else
	{
		_pprx++;
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__transmitirDatos()																//
//																								//
//		@brief		Esta subfunci�n de apoyo para el handler del uart0, se encarga de transmitir datos.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
static void __transmitirDatos(	void	)
{
	if	(*_ptx	==	NULL)				//	Si es el fin de la cadena...
	{
		LPC_UART0->THR	=	RetornoDeCarro;	//	Mando el retorno de carro.
		_ptx			=	UART0_BUFFER_TX;	//	Vuelve al inicio del buffer.
		LPC_UART0->IER	&=	~(1	<<	1);		//	Desactivo interrupci�n por buffer TX vac�o.		
	}
	else									//	Si no es el fin de la cadena...
	{
		LPC_UART0->THR	=	*_ptx;			//	Mando el caracter.
		_ptx++;							//	Cargo la siguiente muestra en el puntero.
	}
	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		UART0_mandaBufferTx()															//
//																								//
//		@brief		Esta funci�n manda el UART0_BUFFER_TX a la salida TX del UART0.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void UART0_MandaBufferTx(	void	)
{
	if	(	(LPC_UART0->IER & (	1	<<	1))	==	0)	//	Si no hay transmisi�n pendiente...
	{
		LPC_UART0->IER	|=	(1	<<	1);	//	Activo interrupci�n por buffer TX vac�o.
		LPC_UART0->THR	=	*_ptx;		//	Env�o el primer caracter.
		_ptx++;						//	Cargo el siguiente caracter.
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		procesarComando()																//
//																								//
//		@brief		Esta funci�n manda el UART0_BUFFER_TX a la salida TX del UART0.							//
//																								//
//		@input		char * Buff:	El buffer donde est� contenido el comando.								//
//																								//
//		@ret			Devuelve 1 si ha sido exitoso y 0 si no se ha obtenido el comando.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	procesarComando(	char	*	Buff	)
{
	uint8_t 	retval = 0;
	uint8_t	comSET = 0;
	/**	SECCI�N PARA LOS COMANDOS DE TIPO 0:	ABOUT*/
	if	(	!strcmp(	Buff	,	COM0	)	)
	{
		retval = 1;
		strcpy(	UART0_BUFFER_TX	,	"\n Autor: \t Alberto Palomo Alonso \n Version: \t 0.0.0 \n Sistemas Electronicos Digitales Avanzados \t UAH \n"	);
	}
	/**	SECCI�N PARA LOS COMANDOS DE TIPO 1:	GIMME*/
	if	(	!strcmp( Buff , COM1)	)
	{
		if 	(	!strcmp(	&Buff[6]	,	COM10)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nSUGAR\n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM11)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nIP: 192.168.1.120 \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM12)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nTEMPERATURA: \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM13)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nPRESION: \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM14)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nVELOCIDAD DEL VIENTO: \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM15)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nX:   \nY:   \nZ:\n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM16)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nINDICE UV: \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM17)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\n / / / : : \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM18)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nHUMEDAD: \n");
			retval = 1;
		}
		if 	(	!strcmp(	&Buff[6]	,	COM19)	)
		{
			strcpy	(	UART0_BUFFER_TX	,	"\nBRILLO: \n");
			retval = 1;
		}
	}
	/**	SECCI�N PARA LOS COMANDOS DE TIPO 2:	SET*/
	if	(	!strcmp(	Buff	,	COM2	)	)
	{
		if (	!strcmp	(	&Buff[4]	,	COM20)	)
		{
			sscanf(	&Buff[11]	,	"%c"	,	&comSET);
			modificaPulso		(	PWM6,	MODO_CICLO	,	comSET	,	none	,	none			,	none			);
			retval = 1;
		}
	}
	/**	SECCI�N PARA LOS COMANDOS DE TIPO 3:	KILL*/
	if	(	!strcmp(	Buff	,	COM3	)	)
	{
		while (1);
	}
	/**	SECCI�N PARA LOS COMANDOS DE TIPO 4:	HELP	*/
	if	(	!strcmp(	Buff	,	COM4	)	)
	{
		strcpy(	UART0_BUFFER_TX	,	"ABOUT: Muestra info. del sistema. \n GIMME: Proporciona el dato deseado. \n   IP: Ip web.\n   TEMPERATURA\n   PRESION\n   LUGAR\n   VIENTO\n   INDICEUV\n   HORA\n   HUMEDAD\n   BRILLO\n SET: Configura parametros del sistema.\n   BRILLO X\n KILL: Cuelga el programa.\n"	);
		retval = 1;
	}
	/**	CONTROL DE ERROR:	*/
	if (	!retval	)
	{
		strcpy(	UART0_BUFFER_TX,	"Error: comando no definido, escriba 'HELP' para ver la lista.\n");
	}
	UART0_MandaBufferTx();
	/**	ZONA RETURN	*/
	return retval;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		UART0_IRQHandler()																//
//																								//
//		@brief		Este es el handler de la interrupci�n por UART0, tiene dos modos: recepci�n y transmisi�n;	//
//					para recepci�n se llama a la subfunci�n __recibirDatos() y __transmitirDatos() para			//
//					transmisi�n.																	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void UART0_IRQHandler()
{
	uint32_t swart = LPC_UART0->IIR & 0x0E;
	switch( swart )
	{
		case 6:								 /* RBR, Receiver Buffer Ready */
			__recibirDatos();
			break;
		case 2:								/* THRE, Transmit Holding Register empty */
			__transmitirDatos();
			break;     
		default:
			
			break;
    }
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																															//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

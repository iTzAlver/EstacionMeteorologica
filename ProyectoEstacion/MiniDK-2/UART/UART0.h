/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		UART0.h																		//
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
//		@include		Includes pertenecientes a e la transmisión asíncrona.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	LPC17XX
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
#ifndef	STDIO
#define	STDIO
#include	<stdio.h>
#endif
#ifndef	STRING
#define	STRING
#include	<string.h>
#endif
#ifndef	PWM
#define	PWM
#include	"PWM.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al protocolo UART0.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	DLP				7
#define	UART0_MTX			(1	<<	1)
#define	UART0_MRX			(1	<<	2)
#define	RetornoDeCarro		13
#define	CADMAX			120

#define	COM1				"GIMME \r"
#define	COM10			"SUGAR"
#define	COM11			"IP"
#define	COM12			"TEMPERATURA"
#define	COM13			"PRESION"
#define	COM14			"VIENTO"
#define	COM15			"LUGAR"
#define	COM16			"INDICEUV"
#define	COM17			"HORA"
#define	COM18			"HUMEDAD"
#define	COM19			"BRILLO"


#define	COM2				"SET "
#define	COM20			"BRILLO "

#define	COM3				"KILL\r"

#define	COM0				"ABOUT"
#define	COM4				"HELP"
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo UART0.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART0__	(	void	);
void UART0_MandaBufferTx	(	void	);
uint8_t	procesarComando(	char *	);
static void	__transmitirDatos	(	void	);
static void __recibirDatos		(	void	);
static void __ignore			(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

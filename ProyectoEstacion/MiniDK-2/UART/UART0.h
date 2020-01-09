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

#define	COM10			"GIVE SUGAR\r"
#define	COM11			"GIVE IP\r"
#define	COM12			"GIVE TEMPERATURA\r"
#define	COM13			"GIVE PRESION\r"
#define	COM14			"GIVE VIENTO\r"
#define	COM15			"GIVE LUGAR\r"
#define	COM16			"GIVE INDICEUV\r"
#define	COM17			"GIVE HORA\r"
#define	COM18			"GIVE HUMEDAD\r"
#define	COM19			"GIVE BRILLO\r"

#define	COM20			"SET BRILLO\r"
#define	COM21			"SET HORA\r"
#define	COM22			"SET MIN TEMP\r"
#define	COM23			"SET MAX TEMP\r"
#define	COM24			"SET MIN PRES\r"
#define	COM25			"SET MAX PRES\r"
#define	COM26			"SET TEMPERATURA\r"
#define	COM27			"SET PRESION\r"

#define	COM3				"KILL\r"

#define	COM0				"ABOUT\r"
#define	COM4				"HELP\r"
#define	COM41			"HELP GIVE\r"
#define	COM42			"HELP SET\r"

#define	UART_TX			0
#define	UART_RX_BRILLO		1
#define	UART_RX_MINT		2
#define	UART_RX_MAXT		3
#define	UART_RX_MINP		4
#define	UART_RX_MAXP		5
#define	UART_RX_HORA		6
#define	UART_RX_VARM		7
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo UART0.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART0__	(	void	);
uint8_t	procesarComando(	char *	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

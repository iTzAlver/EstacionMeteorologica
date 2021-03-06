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
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al protocolo UART0.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	DLP				7
#define	UART3_MTX			(1	<<	1)
#define	UART3_MRX			(1	<<	2)
#define	RetornoDeCarro		13
#define	CADMAX			120
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo UART0.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART3__	(	void	);
void UART3_MandaBufferTx	(	void	);
static void	__transmitirDatos	(	void	);
static void 	__recibirDatos		(	void	);
static void 	__ignore			(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

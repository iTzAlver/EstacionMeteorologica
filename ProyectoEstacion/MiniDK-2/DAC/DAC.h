/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.h																		//
//		@version																					//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para el c�digo de DAC.c													//
//																								//
//		@category		Perif�rico.																	//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el c�digo de configuraci�n.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	LPC17xx
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
#ifndef	LUT
#define	LUT
#include	"LUT.h"
#endif
#ifndef	TIMERS
#define	TIMERS
#include	"Timers.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los s�mbolos correspondientes a la configuraci�n.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	DAC_PIN		(28 - 16)			//	Pin del DAC.
#define	DAC_FUNC		0x2				//	Funci�n 2 del pin 28.
#define	DAC_BIAS		(1 << 16)			//	2.5 us de upstream.
#define	BORRAR_DAC	(0x3FF << 6)		//	10 bits de DAC.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuraci�n.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraDAC__	(	void	);
void	activarDac		(	void	);
void desactivarDAC		(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

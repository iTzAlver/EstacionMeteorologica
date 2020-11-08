/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.h																		//
//		@version																					//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para el código de DAC.c													//
//																								//
//		@category		Periférico.																	//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código de configuración.						//
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
//		@private		Estos son los símbolos correspondientes a la configuración.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	DAC_PIN		(28 - 16)			//	Pin del DAC.
#define	DAC_FUNC		0x2				//	Función 2 del pin 28.
#define	DAC_BIAS		(1 << 16)			//	2.5 us de upstream.
#define	BORRAR_DAC	(0x3FF << 6)		//	10 bits de DAC.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuración.							//
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

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LDR.h																		//
//		@version																					//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para el c�digo de LDR.c													//
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
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los s�mbolos correspondientes a la configuraci�n.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	PCONP_ADC_ON	(1 << 12)
#define	PINSEL_ADC01	(1 << 16)
#define	BRUST_PIN		(1 << 16)
#define	SEL_CANAL1	(1 << 1)
#define	ADC_POWER		(1 << 21)

#define	RESISTENCIA_PULL	1.5
#define	LDRRESISTENCIA_MAX	100
#define	LDRRESISTENCIA_MIN	1
#define	BRILLO_MAX		100
#define	BRILLO_MIN		1
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuraci�n.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraLDR__(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LDR.h																		//
//		@version																					//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para el código de LDR.c													//
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
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes a la configuración.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	PCONP_ADC_ON	(1 << 12)
#define	PINSEL_ADC01	(1 << 16)
#define	PINMODE_ADC01	(3 << 16)
#define	BRUST_PIN		(1 << 16)
#define	SEL_CANAL1	(1 << 1)
#define	SEL_CANAL_GLOBAL	(1 << 8)
#define	ADC_POWER		(1 << 21)
#define	ADC_START		(0x6 << 24)
#define	CLK_DIV_MAX	(0xFF << 8)

#define	RESISTENCIA_PULL	70.00
#define	LDRRESISTENCIA_MAX	100
#define	LDRRESISTENCIA_MIN	1
#define	BRILLO_MAX		100
#define	BRILLO_MIN		1

#define	VREF				3.3
#define	VINDICE			10
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraLDR__(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

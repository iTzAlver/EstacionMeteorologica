/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Anemometro.h																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Esta es la cabecera donde se declara todo lo utilizado en el anemómetro.					//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del PWM.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	LPC17XX
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include "Systemsymbols.h"
#endif
#ifndef	TIMERS
#define	TIMERS
#include	"Timers.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al anemómetro.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	PULSOS_VUELTA		2
#define	DIAMETRO_ANEMOMETRO	14	// En centímetros.
#define	PULSOS_CENTIMETRO	(float)PULSOS_VUELTA/((float)PI*(float)DIAMETRO_ANEMOMETRO)
#define	CTCR_MASCARA		0x0	// 	Dejar al TC contando.
#define	CCR_MASCARA_EN		0x5	//	Generar interrupción.
#define	CCR_MASCARA_DIS	0x1	//	Desactivar interrupción.
#define	WARMUP_CICLOS		4	//	Ciclos de calentamiento.
#define	CAPTURE_FUNCION	0x3	//	Capture 1.0.
#define	PULL_UP			0x0	//
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al anemómetro.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraAnemometro__	(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

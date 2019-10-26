/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		PWM.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa donde están definidas las funciones a utilizar en el módulo				//
//					PWM dedicado al proyecto de Sistemas electrónicos digitales avanzados (UAH - EPS).			//
//																								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//		|---|	|		|	|\	 /|																//
//		|   |	 |	    | 	| \  / |																//
//		|---|	  |	   |		|  \/  |																//
//		|		   |	| |		|	  |																//
//		|		    | |		|	  |																//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código PWM.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef LPC17XX
#define LPC17XX
#include "LPC17XX.H"
#endif

#ifndef SYSTEMSYMBOLS
#define SYSTEMSYMBOLS
#include "Systemsymbols.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al módulo PWM.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define		Fpwm			50				// Velocidad de 20Hz.
#define		Tpwm			0.02				// Periodo de 20ms.
#define		TCR_MASK		0x9				// Activo el contador y el PWM.
#define		MCR_MASK		0x4				// Para el set del PWM.
#define		MCR_MASK_RESET	0x5				// Para resetear el MCR.
#define		PCONP_MASK	0x1 << 6			// Para encender el PWM.
#define		MODO_CICLO	1				// Para la función modificaPulso().
#define		MODO_SERVO	0				// Para la función modificaPulso().
#define		PWM1			1
#define		PWM2			2
#define		PWM3			3
#define		PWM4			4
#define		PWM5			5
#define		PWM6			6
#define	MINIMO_SERVO		0.001
#define 	MAXIMO_SERVO		0.002
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al módulo PWM.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraPWM__	(	float	FrecuenciaPWM		,	uint16_t	CualesPWM	);	//	Default = 0x3F3F -> Todo activado.
void	modificaPulso		(	uint32_t	PWMn				,	uint8_t	Modo		,	uint8_t	Ciclo		,	uint8_t Grados	,	float Minimo	,	float Maximo	);
void softMod			(	uint8_t	GradosObjetivo		,	uint8_t	GradosActuales,	float Minimo	,	float	Maximo	,	uint32_t	PWMn);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

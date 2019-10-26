/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		configura.h																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para el código de configuración.c											//
//																								//
//		@category		Principal.																	//
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
// PWM
#ifndef	PWM
#define	PWM
#include 	"PWM.h"
#endif
#ifndef	GLCD
#define	GLDC
#include	"GLCD.h"
#include	"TouchPanel.h"
#include	"menu.h"
#include	"leds.h"
#endif
#ifndef	STATECHART
#define	STATECHART
#include	"Statechart.h"
#endif
#ifndef	RTC
#define	RTC
#include	"RTC.h"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include 	"Systemsymbols.h"
#endif
#ifndef	WDT
#define	WDT
#include	"WDT.h"
#endif
#ifndef	HTTP_SOURCE
#define	HTTP_SOURCE
#include "HTTP_SOURCE.h"
#endif
#ifndef	TIMERS
#define	TIMERS
#include 	"Timers.h"
#endif
#ifndef	ANEMOMETRO
#define	ANEMOMETRO
#include "Anemometro.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes a la configuración.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	ACTIVOS_TODOS2		0x003F
#define	ACTIVOS_1_2		0x0001
#define	ACTIVOS_2_2		0x0002
#define	ACTIVOS_1_1		0x0100
#define	ACTIVOS_2_1		0x0200
#define	ACTIVOS_6_2		0x0020
#define	ACTIVOS_6_1		0x2000
#define	MINIMO_SERVO		0.001
#define 	MAXIMO_SERVO		0.002
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraPrograma__(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

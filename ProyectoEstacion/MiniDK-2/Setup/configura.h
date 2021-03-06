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
#include 	"Anemometro.h"
#endif
#ifndef	DAC
#define	DAC
#include 	"DAC.h"
#endif
#ifndef	UVA30A
#define	UVA30A
#include	"UVA30A.h"
#endif
#ifndef	UFONO
#define	UFONO
#include	"uFono.h"
#endif
#ifndef	LUT
#define	LUT
#include	"LUT.h"
#endif
#ifndef	DMA
#define	DMA	
#include	"DMA.h"
#endif
#ifndef	I2C
#define	I2C	
#include	"I2C.h"
#endif
#ifndef	UART0
#define	UART0
#include	"UART0.h"
#endif
#ifndef	UART3
#define	UART3
#include	"UART3.h"
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

#define	MAXIMO_PRESION		1500
#define	MINIMO_PRESION		500
#define	MAXIMO_TEMPERATURA	50
#define	MINIMO_TEMPERATURA	-10
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a la configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraPrograma__	(	void	);
void __iniciaVariables__		(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

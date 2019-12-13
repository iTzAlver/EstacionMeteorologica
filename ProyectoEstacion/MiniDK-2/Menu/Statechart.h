/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Statechart.c																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera del código fuente de Statechart.c											//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@private																		//
//					@types																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el statechart.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	LCD
#ifndef	GLCD
#define	GLCD
#include	"GLCD.h"
#include	"TouchPanel.h"
#include	"menu.h"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include 	"Systemsymbols.h"
#endif
#ifndef	STRING
#define	STRING
#include	<string.h>
#endif
#ifndef	WTD
#define	WDT
#include "WDT.h"
#endif
#ifndef	PWM
#define	PWM
#include	"PWM.h"
#endif
#ifndef	STDIO
#define	STDIO
#include	<stdio.h>
#endif
#ifndef	MIGLOBAL
#define	MIGLOBAL
#include	"miGlobal.h"
#endif
#ifndef	TIMERS
#define	TIMERS
#include	"Timers.h"
#endif
#ifndef	RTL
#define	RTL
#include	"RTL.h"
#endif
#ifndef	HTTPSOURCE
#define	HTTPSOURCE
#include	"HTTP_SOURCE.h"
#endif
#ifndef	LUT
#define	LUT
#include "LUT.h"
#endif
#ifndef	DAC
#define	DAC
#include	"DAC.h"
#endif
#ifndef	UFONO
#define	UFONO
#include	"uFono.h"
#endif
#ifndef	ONEWIRE
#define	ONEWIRE
#include	"OneWire.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al statechart.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	PANTALLA_INICIO	0
#define	PANTALLA_MEDIDAS1	1
#define	PANTALLA_MEDIDAS2	2
#define	PANTALLA_AJUSTES	3
#define	PANTALLA_LOADING	4

#define	MAXIMOX			240
#define	MAXIMOY			320
#define	CLEAR_BUFFER		"                       "
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@types		Tipos utilizados en el statechart.	COPIADOS DE menu.c									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
typedef struct {
	uint16_t x;         
	uint16_t y;
	uint16_t size_x;
	uint16_t size_y;
	uint8_t  pressed;
}screenZone_t;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al statechart.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__mainLoop__		(	void	);
void __configuraLCD__	(	void	);
void __pintaInicio__	(	void	);
void __pintaAjustes__	(	void	);
void	__pintaMedidas1__	(	void	);
void	__pintaMedidas2__	(	void	);
void squareButton		( screenZone_t *	zone		, char * 		text	, uint16_t 	textColor	, uint16_t 	lineColor);
void checkTouchPanel	(	void	);
int8_t zoneNewPressed	(screenZone_t * zone		);
void squareBox			( screenZone_t *	zone		,	uint16_t	color);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

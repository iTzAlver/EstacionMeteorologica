/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		header.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabezera del c�digo fuente, agrupa todos los archivos.									//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Incluye todos los archivos necesarios.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	Librer�a de registros.
#ifndef LPC17XX
#define LPC17XX
#include "LPC17XX.H"
#endif
// 	S�mbolos del sistema.
#ifndef SYSTEMSYMBOLS
#define SYSTEMSYMBOLS
#include "Systemsymbols.h"
#endif
//	Pwm.
#ifndef 	PWM
#define	PWM
#include "PWM.h"
#endif
//	Configura
#ifndef	CONFIGURA
#define	CONFIGURA
#include "configura.h"
#endif
#ifndef	STATECHART
#define	STATECHART
#include "Statechart.h"
#endif
#ifndef	GLCD
#define	GLCD
#include	"GLCD.h"
#include	"TouchPanel.h"
#include	"menu.h"
#include	"leds.h"
#endif
#ifndef	STATECHART
#define	STATECHART	
#include	"Statechart.h"
#endif
#ifndef HTTPSOURCE
#define	HTTPSOURCE
#include "HTTP_SOURCE.h"
#endif
#ifdef	DEBUG
#include	"DEBUG.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


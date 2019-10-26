/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		RTC.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente del configurado y manejador del RTC.									//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@HANDLER																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código del RTC.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	RTC
#define	RTC
#include "RTC.h"
#endif
#ifndef	STRING
#define	STRING
#include <string.h>
#endif
#ifndef	STDIO
#define	STDIO
#include	<stdio.h>
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
uint8_t Clock[23];
extern Counters_t	*	COUNTERS;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function	__configuraRTC__()																	//
//																								//
//		@brief	Función que configura el RTC como un contador que interrumpe cada segundo.						//
//																								//
//			@Tiempo	Puntero a variable donde se almacena el tiempo actual.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraRTC__( void ) 
{
	LPC_SC->PCONP 		|= RTCMASK; 				// Activo el RTC.
	LPC_RTC->CCR 		= CALIBRACION_RTC;			// Calibro el RTC.
	LPC_RTC->CALIBRATION = CALIBRATION_VALUE;
	LPC_RTC->CCR		= 0x1;
	LPC_RTC->CIIR		|= INT_SEGUNDOS;			// Interrupción del RTC cada segundo.
	LPC_RTC->YEAR 		= 	2019;				// Configuro el registro
	LPC_RTC->MONTH		= 	10;					//  que tiene en cuenta
	LPC_RTC->DOM		=	12;					//  los dias, meses,
	LPC_RTC->HOUR		=	15;					//  minutos y segundos
	LPC_RTC->MIN		=	37;					//  del RTC.
	LPC_RTC->SEC		=	0;					//
	NVIC_EnableIRQ( RTC_IRQn);					// Habilito la interrumpción del RTC.
	NVIC_SetPriority(	RTC_IRQn	,	0	);		// Se le asigna prioridad alta.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER	RTC_IRQHandler()																	//
//																								//
//		@brief	Manejador de la interrupción RTC.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void RTC_IRQHandler( void ) 
{
	COUNTERS->Segundos 		+= 0x1;	// Incrementa el contador.
	LPC_RTC->ILR 			|= 1;	// Borra el flag de interrupción.
	sprintf((char*)Clock,"%02d/%02d/%04d-%02d:%02d:%02d",LPC_RTC->DOM,LPC_RTC->MONTH,LPC_RTC->YEAR,LPC_RTC->HOUR,LPC_RTC->MIN,LPC_RTC->SEC);
//	if (COUNTERS->Segundos == 60)
//	{
//		__sumaMinReloj__();
//		COUNTERS->Segundos = 0;
//	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

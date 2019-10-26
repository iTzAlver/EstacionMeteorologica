/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		HTTP_CGI.h																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera que configura los callback la página WEB.												//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el código de configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	NETCONFIG
#define	NETCONFIG
#include	<Net_Config.h>
#endif
#ifndef	STDIO
#define	STDIO
#include	<stdio.h>
#endif
#ifndef	STDLIB
#define	STDLIB
#include <stdlib.h>
#endif
#ifndef	STDINT
#define	STDINT
#include <stdint.h>
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include <Systemsymbols.h>
#endif
#ifndef	LPC17XX
#define   LPC17XX
#include "LPC17XX.H"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al cgi.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	TEMPERATURA	't'
#define	VELOCIDAD		'v'
#define	PRESION		'p'
#define	HUMEDAD		'h'
#define	INDICEUV		'i'
#define	BRILLO		'b'
#define	ALTITUD		'a'
#define	LONGITUD		'x'
#define	LATITUD		'y'
#define	ANYO			'A'
#define	MES			'M'
#define	DIA			'D'
#define	HORAS		'H'
#define	MINUTOS		'T'
#define	SEGUNDOS		'S'
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al cgi.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void cgi_process_var	(	U8*	qs);	//		NO SE USA.
void cgi_process_data	(	U8 		tipo	,	U8	*	qs	,	U16		longitud);	//	NO SE USA.
U16 cgi_func			(	U8	*	env	,	U8	*	buff	,	U16		bufflen	,	U32	*	pcgi);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

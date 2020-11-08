/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		HTTP_CGI.c																	//
//		@version		3.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que contiene las llamadas a las funciones de CGI.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@extern																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el código de configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	HTTPCGI
#define	HTTPCGI
#include	"HTTP_CGI.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@extern		misDatos_t * DATOS -> main.c														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
extern misDatos_t	*	DATOS;
extern modificables_t 	MODIFICABLES;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		cgi_process_var																//
//																								//
//		@brief		Utilizado para el método GET.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void cgi_process_var	(	U8*	qs)
{
	U8 * var;
	var = (U8 *)alloc_mem(40);
	
	do
	{
		qs = http_get_var(qs , var, 40);
		if( var[0] )
		{
			if (str_scomp( var , (U8 *)"tmin="))
			{
				sscanf( (const char *)&var[5] , "%f" , &MODIFICABLES.Min_servo_t);
			}
			if (str_scomp( var , (U8 *)"tmax="))
			{
				sscanf( (const char *)&var[5] , "%f" , &MODIFICABLES.Max_servo_t);
			}
			if (str_scomp( var , (U8 *)"pmin="))
			{
				sscanf( (const char *)&var[5] , "%f" , &MODIFICABLES.Min_servo_p);
			}
			if (str_scomp( var , (U8 *)"pmax="))
			{
				sscanf( (const char *)&var[5] , "%f" , &MODIFICABLES.Max_servo_p);
			}
			if (str_scomp( var , (U8 *)"bsec="))
			{
				sscanf( (const char *)&var[5] , "%d" , &MODIFICABLES.TiempoBrillo);
			}
			if (str_scomp( var , (U8 *)"vart="))
			{
				MODIFICABLES.Var_medida = 0;
			}
			if (str_scomp( var , (U8 *)"varp="))
			{
				MODIFICABLES.Var_medida = 1;
			}
		}
	}while(qs);
	
	free_mem( (OS_FRAME *)var );
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		cgi_process_var																//
//																								//
//		@brief		NO UTILIZADO.																	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void cgi_process_data	(	U8 		tipo	,	U8	*	qs	,	U16		longitud)
{
	//	NO UTILIZADO,	NO HAY PETICIONES EN ESTA VERSIÓN.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		cgi_func()																	//
//																								//
//		@brief		Función que es llamada por el CGI cada vez que se socilicita una callback.					//
//					Obtiene una cadena de caracteres como parámetro de CGI y actúa en consecuencia.				//
//					En nuestro caso sólo llama a los datos y los exporta a html.							//
//																								//
//			@env				Cadena de caracteres de entrada.											//
//			@buff			Salida de datos.														//
//			@bufflen			(No utilizado)Tamaño del buffer.											//
//			@pcgui			(No utilizado)															//
//																								//
//				@return		Tamaño de la cadena de salida en bytes.										//
//																								//
//																								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
U16 cgi_func			(	U8	*	env	,	U8	*	buff	,	U16		bufflen	,	U32	*	pcgi)
{
	U32 longitud;
	
	switch(	env[0]	)
	{
		case	TEMPERATURA:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Temperatura	);
			break;
		case	PRESION:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Presion		);
			break;
		case	HUMEDAD:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Humedad		);
			break;
		case	BRILLO:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Brillo		);
			break;
		case	ALTITUD:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Lugar.Altura	);
			break;
		case	LATITUD:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Lugar.Latitud);
			break;
		case	LONGITUD:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->Lugar.Longitud);
			break;
		case	INDICEUV:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->IndiceUV	);
			break;
		case	VELOCIDAD:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	DATOS->VelViento	);
			break;
		case ANYO:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->YEAR		);
			break;
		case MES:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->MONTH		);
			break;
		case DIA:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->DOM		);
			break;
		case HORAS:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->HOUR		);
			break;
		case MINUTOS:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->MIN		);
			break;
		case SEGUNDOS:
			longitud = sprintf	(	(char*)buff	,	(const char *)&env[4]		,	LPC_RTC->SEC		);
			break;
		default:
			longitud = sprintf	(	(char*)buff	,	"<p>Y... que quieres que ponga aqui? :v</p>");
			break;
	}
	return	(	(U16)longitud	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

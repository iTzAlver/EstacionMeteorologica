/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		UART0.c																		//
//		@version		2.01																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que recoge la transmisión por UART0.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@variables																	//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes a la transmisión asíncrona.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	UART0
#define	UART0
#include	"UART0.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@variables		Variables del fichero.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	Variables globales y externas.
char UART0_BUFFER_TX[CADMAX + 1];
extern char bufferx[30];
extern misDatos_t * DATOS;
extern uint8_t Clock[23];
uint8_t EstadoUART0 = UART_TX;
extern modificables_t MODIFICABLES;
uint8_t Inmortal = 0;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraUART0__()															//
//																								//
//		@brief		Esta función es la que configura el UART0 para transmisión y recepción.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraUART0__(	void	)				//	Configurado a 9600 baudios.
{
	uart0_init(9600);
	tx_cadena_UART0(	"Hola.\n"	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		procesarComando()																//
//																								//
//		@brief		Esta función manda el UART0_BUFFER_TX a la salida TX del UART0.							//
//																								//
//		@input		char * Buff:	El buffer donde está contenido el comando.								//
//																								//
//		@ret			Devuelve 1 si ha sido exitoso y 0 si no se ha obtenido el comando.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	procesarComando(	char	*	Buff	)
{
	uint8_t 	retval = 0;
	switch( EstadoUART0 )
	{
		case UART_TX:
			/**	SECCIÓN PARA LOS COMANDOS DE TIPO 0:	ABOUT*/
			if	(	!strcmp(	Buff	,	COM0	)	)
			{
				retval = 1;
				strcpy(	UART0_BUFFER_TX	,	"\n Autor: \t Alberto Palomo Alonso \n Version: \t 2.1.0 \n Sistemas Electronicos Digitales Avanzados \t UAH \n"	);
			}
			/**	SECCIÓN PARA LOS COMANDOS DE TIPO 1:	GIMME*/
			if 	(	!strcmp(	Buff	,	COM10)	)
			{
				if ( !Inmortal )
				{
					strcpy	(	UART0_BUFFER_TX	,	"\nSUGAR n.n\n");
					Inmortal = 1;
					retval = 1;
				}
			}
			if 	(	!strcmp(	Buff	,	COM11)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nIP: %d.%d.%d.%d \n", __IP1B, __IP2B, __IP3B, __IP4B);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM12)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nTEMPERATURA: %f ºC\n", DATOS->Temperatura);
				
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM13)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nPRESION: %f mBar.\n", DATOS->Presion);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM14)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nVELOCIDAD DEL VIENTO: %f m./s.\n", DATOS->VelViento);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM15)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nX: NA   \nY: NA  \nZ: %f m.\n", DATOS->Lugar.Altura);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM16)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nINDICE UV: %f\n", DATOS->IndiceUV);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM17)	)
			{
				strcpy	(	UART0_BUFFER_TX	,	(const char *)Clock);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM18)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nHUMEDAD: %f \n", 0.01*DATOS->Humedad);
				retval = 1;
			}
			if 	(	!strcmp(	Buff	,	COM19)	)
			{
				sprintf	(	UART0_BUFFER_TX	,	"\nBRILLO: %f LUX.\n", DATOS->Brillo);
				retval = 1;
			}
			/**	SECCIÓN PARA LOS COMANDOS DE TIPO 3:	KILL*/
			if	(	!strcmp(	Buff	,	COM3	)	)
			{
				while ( !Inmortal );
				strcpy(	UART0_BUFFER_TX	,	"Demasiado dulce como para matarlo, mejor para otra ocasion...\n");
				retval = 1;
			}
			/**	SECCIÓN PARA LOS COMANDOS DE TIPO 4:	HELP	*/
			if	(	!strcmp(	Buff	,	COM4	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Informacion:\n\n ABOUT: Muestra info. del sistema.\n GIVE: Proporciona el dato deseado.\n KILL: Cuelga el programa.\n SET: Modifica variables.\n"	);
				retval = 1;
			}
			if	(	!strcmp(	Buff	,	COM41	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"\nGIVE + [IP, TEMPERATURA, PRESION, BRILLO, LUGAR, VIENTO, INDICEUV, HORA, HUMEDAD]\n"	);
				retval = 1;
			}
			if	(	!strcmp(	Buff	,	COM42	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"\nSET + [BRILLO, HORA, MIN TEMP, MAX TEMP, MIN PRES, MAX PRES, TEMPERATURA, PRESION]\n"	);
				retval = 1;
			}
			/**	CONTROL DE ERROR:	*/
			if (	!retval	)
			{
				strcpy(	UART0_BUFFER_TX,	"Error: comando no definido, escriba 'HELP' para ver la lista.\n");
			}
			/** SECCIÓN PARA LOS COMANDOS DE TIPO 2:	SET	*/
			if	(	!strcmp(	Buff	,	COM20	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza los segundos de brillo: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_BRILLO;
			}
			if	(	!strcmp(	Buff	,	COM21	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza la fecha separada por espacios: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_HORA;
			}
			if	(	!strcmp(	Buff	,	COM22	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza el valor minimo de temperatura: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_MINT;
			}
			if	(	!strcmp(	Buff	,	COM23	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza el valor maximo de temperatura: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_MAXT;
			}
			if	(	!strcmp(	Buff	,	COM24	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza el valor minimo de presion: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_MINP;
			}
			if	(	!strcmp(	Buff	,	COM25	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Introducza el valor maximo de presion: \n"	);
				retval = 1;
				EstadoUART0 = UART_RX_MAXP;
			}
			if	(	!strcmp(	Buff	,	COM27	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Ahora medimos presion... \n"	);
				retval = 1;
				MODIFICABLES.Var_medida = 1;
			}
			if	(	!strcmp(	Buff	,	COM26	)	)
			{
				strcpy(	UART0_BUFFER_TX	,	"Ahora medimos temperatura... \n"	);
				retval = 1;
				MODIFICABLES.Var_medida = 0;
			}
			break;
			
		case UART_RX_BRILLO:
			sscanf(	bufferx	,	"%d"	,	&MODIFICABLES.TiempoBrillo);
			strcpy(	UART0_BUFFER_TX		,	"Tiempo de hold cambiado.\n"	);
			EstadoUART0 = UART_TX;
			break;
		case UART_RX_MINT:
			sscanf(	bufferx	,	"%f"	,	&MODIFICABLES.Min_servo_t);
			strcpy(	UART0_BUFFER_TX		,	"Cota minima de temperatura cambiada.\n"	);
			EstadoUART0 = UART_TX;
			break;
		case UART_RX_MAXT:
			sscanf(	bufferx	,	"%f"	,	&MODIFICABLES.Max_servo_t);
			strcpy(	UART0_BUFFER_TX		,	"Cota maxima de temperatura cambiada.\n"	);
			EstadoUART0 = UART_TX;
			break;
		case UART_RX_MINP:
			sscanf(	bufferx	,	"%f"	,	&MODIFICABLES.Min_servo_p);
			strcpy(	UART0_BUFFER_TX		,	"Cota minima de presion cambiada.\n"	);
			EstadoUART0 = UART_TX;
			break;
		case UART_RX_MAXP:
			sscanf(	bufferx	,	"%f"	,	&MODIFICABLES.Max_servo_p);
			strcpy(	UART0_BUFFER_TX		,	"Cota maxima de presion cambiada.\n"	);
			EstadoUART0 = UART_TX;
			break;
		case UART_RX_HORA:
			sscanf(	bufferx	,	"%d %d %d %d %d %d"	,	(int *)&LPC_RTC->DOM , (int *)&LPC_RTC->MONTH, (int *)&LPC_RTC->YEAR, (int *)&LPC_RTC->HOUR, (int *)&LPC_RTC->MIN, (int *)&LPC_RTC->SEC);
			strcpy(	UART0_BUFFER_TX		,	"Hora cambiada...\n"	);
			EstadoUART0 = UART_TX;
			break;
			
	}
	tx_cadena_UART0(UART0_BUFFER_TX);
	/**	ZONA RETURN	*/
	return retval;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																															//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

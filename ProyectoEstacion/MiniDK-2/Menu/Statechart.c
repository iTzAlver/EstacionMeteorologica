/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		main.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente correspondiente a la máquina de estados que compone el menú.					//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@global																		//
//					@function																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el statechart.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	STATECHART
#define	STATECHART
#include 	"Statechart.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@global		Estas son las variables globales pertenecientes al statechart.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
extern uint8_t 		Clock[23];
extern State_t		*	ESTADO;
extern misDatos_t	*	DATOS;
extern actualizador_t	*	ACTUALIZADOR;
extern uint8_t 			OWEjecutameExterno;
uint8_t	pressedTouchPanel;
uint8_t	__brilloAuto = 0;
uint8_t	Aux8;
//	ZONA DE PANTALLA DE INICIO.
screenZone_t 	zona_0	=	{	0			,		0		,	MAXIMOX		,	MAXIMOY*0.2	,	0	};	//	Marco del reloj y botones de alante y atrás.
screenZone_t 	zona_1	=	{	MAXIMOX*0.15	,  		0		, 	MAXIMOX*0.7	, 	MAXIMOY*0.2	,	0	};	//	Reloj.
screenZone_t 	zona_2	=	{	MAXIMOX*0.85 	,		0		,	MAXIMOX*0.15	,	MAXIMOY*0.2	, 	0	};	//	Derecha.
screenZone_t 	zona_3	=	{ 	MAXIMOX*0 	,  		0 		, 	MAXIMOX*0.15	, 	MAXIMOY*0.2	, 	0	};	//	Izquierda.
screenZone_t 	zona_4	=	{ 	MAXIMOX*0		,	MAXIMOY*0.2	, 	MAXIMOX*0.5	, 	MAXIMOY*0.3	, 	0	};	//	Primer botón.
screenZone_t 	zona_5	=	{ 	MAXIMOX*0.5	,  	MAXIMOY*0.2	, 	MAXIMOX*0.5	, 	MAXIMOY*0.3	, 	0	};	//	Segundo botón.
screenZone_t 	zona_6	=	{ 	MAXIMOX*0		,	MAXIMOY*0.5	, 	MAXIMOX		, 	MAXIMOY*0.15	, 	0	};	//	Brillo info.
screenZone_t 	zona_7	=	{ 	MAXIMOX*0		,	MAXIMOY*0.65	, 	MAXIMOX*0.2	, 	MAXIMOY*0.15	, 	0	};	//	Primer botón de brillo.
screenZone_t 	zona_8	=	{ 	MAXIMOX*0.2	,	MAXIMOY*0.65	, 	MAXIMOX*0.2	, 	MAXIMOY*0.15	, 	0	};	//	Segundo botón de brillo.
screenZone_t 	zona_9	=	{ 	MAXIMOX*0.4	,	MAXIMOY*0.65	, 	MAXIMOX*0.2	, 	MAXIMOY*0.15	, 	0	};	//	Tercer botón de brillo.
screenZone_t 	zona_10	=	{ 	MAXIMOX*0.6	,	MAXIMOY*0.65	, 	MAXIMOX*0.2	, 	MAXIMOY*0.15	, 	0	};	//	Cuarto botón de brillo.
screenZone_t 	zona_11	=	{ 	MAXIMOX*0.8	,	MAXIMOY*0.65	, 	MAXIMOX*0.2	, 	MAXIMOY*0.15	, 	0	};	//	Brillo automático.
screenZone_t 	zona_12	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX*0.2	, 	MAXIMOY*0.2	, 	0	};	//	Botón de audio.
screenZone_t 	zona_13	=	{ 	MAXIMOX*0.2	,	MAXIMOY*0.8	, 	MAXIMOX*0.2	, 	MAXIMOY*0.2	, 	0	};	//	Volumen = 1.
screenZone_t 	zona_14	=	{ 	MAXIMOX*0.4	,	MAXIMOY*0.8	, 	MAXIMOX*0.2	, 	MAXIMOY*0.2	, 	0	};	//	Volumen = 2.
screenZone_t 	zona_15	=	{ 	MAXIMOX*0.6	,	MAXIMOY*0.8	, 	MAXIMOX*0.2	, 	MAXIMOY*0.2	, 	0	};	//	Volumen = 3.
screenZone_t 	zona_16	=	{ 	MAXIMOX*0.8	,	MAXIMOY*0.8	, 	MAXIMOX*0.2	, 	MAXIMOY*0.2	, 	0	};	//	Botón de load.
//	ZONA DE MEDIDAS.
screenZone_t 	zona_17	=	{ 	MAXIMOX*0		,	MAXIMOY*0.2	, 	MAXIMOX		, 	MAXIMOY*0.1	, 	0	};	//	Información de página, medidas.
screenZone_t 	zona_18	=	{ 	MAXIMOX*0		,	MAXIMOY*0.3	, 	MAXIMOX		, 	MAXIMOY*0.1	, 	0	};	//	Localización.
screenZone_t 	zona_19	=	{ 	MAXIMOX*0		,	MAXIMOY*0.4	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Temperatura.
screenZone_t 	zona_20	=	{ 	MAXIMOX*0		,	MAXIMOY*0.55	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Humedad.
screenZone_t 	zona_21	=	{ 	MAXIMOX*0		,	MAXIMOY*0.70	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Presión.
screenZone_t 	zona_22	=	{ 	MAXIMOX*0		,	MAXIMOY*0.85	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	IndiceUV.
//	ZONAS DE DATOS.
screenZone_t 	zona_23	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.4	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Valor de temperatura.
screenZone_t 	zona_24	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.55	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Valor de humedad.
screenZone_t 	zona_25	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.70	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Valor de presión.
screenZone_t 	zona_26	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.85	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Valor de IndiceUV.
//	ZONAS DE AJUSTES.
screenZone_t 	zona_27	=	{ 	MAXIMOX*0		,	MAXIMOY*0.2	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Horas.
screenZone_t 	zona_28	=	{ 	MAXIMOX*0		,	MAXIMOY*0.35	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Minutos.
screenZone_t 	zona_29	=	{ 	MAXIMOX*0		,	MAXIMOY*0.5	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Segundos.
screenZone_t 	zona_30	=	{ 	MAXIMOX*0		,	MAXIMOY*0.65	, 	MAXIMOX*0.5	, 	MAXIMOY*0.15	, 	0	};	//	Dia.
screenZone_t	zona_31	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX		, 	MAXIMOY*0.2	, 	0	};	//	Slot libre.
screenZone_t 	zona_27m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.2	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta horas.
screenZone_t 	zona_28m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.35	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta minutos.
screenZone_t 	zona_29m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.5	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta segundos.
screenZone_t 	zona_30m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.65	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta dia.
screenZone_t 	zona_27M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.2	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma horas.
screenZone_t 	zona_28M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.35	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma minutos.
screenZone_t 	zona_29M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.5	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma segundos.
screenZone_t 	zona_30M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.65	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma dia.
//	ZONAS DE MEDIDAS 2 (VIENTO)
screenZone_t	zona_32	=	{ 	MAXIMOX*0		,	MAXIMOY*0.2	, 	MAXIMOX		, 	MAXIMOY*0.2	, 	0	};	//	Velocidad del viento.
screenZone_t	zona_33	=	{ 	MAXIMOX*0		,	MAXIMOY*0.4	, 	MAXIMOX		, 	MAXIMOY*0.2	, 	0	};	//	Velocidad del viento.
screenZone_t	zona_34	=	{ 	MAXIMOX*0		,	MAXIMOY*0.6	, 	MAXIMOX		, 	MAXIMOY*0.2	, 	0	};	//	Cantidad de brillo.
screenZone_t	zona_35	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX		, 	MAXIMOY*0.2	, 	0	};	//	Cantidad de brillo.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__mainLoop__()																	//
//																								//
//		@brief		Esta función es la que se ejecuta en el bucle principal del main. Debe contener				//
//					todo el código ejecutable por el loop principal.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__mainLoop__(	void	)
{
	alimentaWDT();
	checkTouchPanel();
	if ( __brilloAuto && (SysTick->CTRL & 0x10000))	//	Cada 100 ms si el brillo auto está activado.
	{
		goto_LUT( DATOS->Brillo, BRILLO2CICLO_LDR , none , &Aux8 , none , none);
		modificaPulso(	PWM6	,	MODO_CICLO	,	Aux8	,	none	,	none	,	none	);	/**	@TODO: Cambiar por brillo automático. */
	}
	switch(	ESTADO->CHART	)
	{
		case	PANTALLA_INICIO:
			__pintaInicio__();
			if (zoneNewPressed(	&zona_2))
			{
				ESTADO->CHART = PANTALLA_MEDIDAS1;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_3))
			{
				ESTADO->CHART = PANTALLA_MEDIDAS2;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_5))
			{
				ESTADO->CHART = PANTALLA_AJUSTES;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_7))
			{
				__brilloAuto = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	1	,	none	,	none	,	none	);
			}
			if (zoneNewPressed(	&zona_8))
			{
				__brilloAuto = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	20	,	none	,	none	,	none	);
			}
			if (zoneNewPressed(	&zona_9))
			{
				__brilloAuto = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	40	,	none	,	none	,	none	);
			}
			if (zoneNewPressed(	&zona_10))
			{
				modificaPulso(	PWM6	,	MODO_CICLO	,	60	,	none	,	none	,	none	);
				__brilloAuto = 0;
			}
			if (zoneNewPressed(	&zona_11))
			{
				__brilloAuto = 1;
			}
			if (zoneNewPressed(	&zona_12))
			{
				if	(	ACTUALIZADOR->Audiorev	)
				{
					ACTUALIZADOR->Audiorev = 0;
					activarDac();
				}
			}
			if (zoneNewPressed(	&zona_16))
			{
				if	(	ACTUALIZADOR->Audiorev	)
				{
					ACTUALIZADOR->Audiorev = 0;
					lanzaUFONO();
				}
			}
			break;
			
		case	PANTALLA_MEDIDAS1:
			__pintaMedidas1__();
			if (zoneNewPressed(	&zona_2))
			{
				ESTADO->CHART = PANTALLA_MEDIDAS2;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_3))
			{
				ESTADO->CHART = PANTALLA_INICIO;
				LCD_Clear(Black);
			}
			break;
			
		case	PANTALLA_MEDIDAS2:
			__pintaMedidas2__();
			if (zoneNewPressed(	&zona_2))
			{
				ESTADO->CHART = PANTALLA_INICIO;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_3))
			{
				ESTADO->CHART = PANTALLA_MEDIDAS1;
				LCD_Clear(Black);
			}
			break;
			
		case	PANTALLA_AJUSTES:
			__pintaAjustes__();
			if (zoneNewPressed(	&zona_2))
			{
				ESTADO->CHART = PANTALLA_INICIO;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_3))
			{
				ESTADO->CHART = PANTALLA_INICIO;
				LCD_Clear(Black);
			}
			if (zoneNewPressed(	&zona_27m))
			{
				LPC_RTC->HOUR--;
			}
			if (zoneNewPressed(	&zona_28m))
			{
				LPC_RTC->MIN--;
			}
			if (zoneNewPressed(	&zona_29m))
			{
				LPC_RTC->SEC--;
			}
			if (zoneNewPressed(	&zona_30m))
			{
				LPC_RTC->DOM--;
			}
			if (zoneNewPressed(	&zona_27M))
			{
				LPC_RTC->HOUR++;
			}
			if (zoneNewPressed(	&zona_28M))
			{
				LPC_RTC->MIN++;
			}
			if (zoneNewPressed(	&zona_29M))
			{
				LPC_RTC->SEC++;
			}
			if (zoneNewPressed(	&zona_30M))
			{
				LPC_RTC->DOM++;
			}
			break;
			
		case	PANTALLA_LOADING:
			break;
		default:
			break;
	};
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraLCD__()																//
//																								//
//		@brief		Esta función configura el TFT HY32B conectado al driver ILI9325C							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraLCD__(	void	)
{
	TP_Init();
	LCD_Initializtion();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__pintaInicio__()																//
//																								//
//		@brief		Esta función pinta la pantalla de inicio.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__pintaInicio__(	void	)
{
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_4	,	"Info."			,	Yellow	,	Green	);
	squareButton(	&zona_5	,	"Ajustes"			,	Yellow	,	Green	);
	squareButton(	&zona_6	,	"Nivel de brillo:"	,	Yellow	,	Green	);
	squareButton(	&zona_7	,	"1"				,	Yellow	,	Green	);
	squareButton(	&zona_8	,	"2"				,	Yellow	,	Green	);
	squareButton(	&zona_9	,	"3"				,	Yellow	,	Green	);
	squareButton(	&zona_10	,	"4"				,	Yellow	,	Green	);
	squareButton(	&zona_11	,	"A"				,	Yellow	,	Green	);
	squareButton(	&zona_12	,	"Play"			,	Yellow	,	Green	);
	squareButton(	&zona_13	,	"Vol.1"			,	Yellow	,	Green	);
	squareButton(	&zona_14	,	"Vol.2"			,	Yellow	,	Green	);
	squareButton(	&zona_15	,	"Vol.3"			,	Yellow	,	Green	);
	squareButton(	&zona_16	,	"Load"			,	Yellow	,	Green	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__pintaAjustes__()																//
//																								//
//		@brief		Esta función pinta la pantalla de ajustes.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__pintaAjustes__(	void	)
{
	uint8_t buffer[23];
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_27	,	"Horas"			,	Yellow	,	Green	);
	squareButton(	&zona_28	,	"Minutos"			,	Yellow	,	Green	);
	squareButton(	&zona_29	,	"Segundos"		,	Yellow	,	Green	);
	squareButton(	&zona_30	,	"Dias"			,	Yellow	,	Green	);
	sprintf((char *)buffer	,	"IP:%d.%d.%d.%d"	,	__IP1B	,	__IP2B	,	__IP3B	,	__IP4B	);
	squareButton(	&zona_31	,	(char*)buffer		,	Yellow	,	Green	);
	squareButton(	&zona_27m	,	"-"				,	Yellow	,	Green	);
	squareButton(	&zona_28m	,	"-"				,	Yellow	,	Green	);
	squareButton(	&zona_29m	,	"-"				,	Yellow	,	Green	);
	squareButton(	&zona_30m	,	"-"				,	Yellow	,	Green	);
	squareButton(	&zona_27M	,	"+"				,	Yellow	,	Green	);
	squareButton(	&zona_28M	,	"+"				,	Yellow	,	Green	);
	squareButton(	&zona_29M	,	"+"				,	Yellow	,	Green	);
	squareButton(	&zona_30M	,	"+"				,	Yellow	,	Green	);
	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__pintaMedidas1__()																//
//																								//
//		@brief		Esta función pinta la primera pantalla de medidas.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__pintaMedidas1__(	void	)
{
	uint8_t buffer[23];
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_17	,	"MEDIDAS ACTUALES"	,	Yellow	,	Green	);
	sprintf((char*)buffer,"X:%.02f Y:%.02f Z:%.02f",	DATOS->Lugar.Longitud	,	DATOS->Lugar.Latitud	,	DATOS->Lugar.Altura);
	squareButton(	&zona_18	,	(char *)buffer		,	Yellow	,	Green	);
	squareButton(	&zona_19	,	"Temperatura:"		,	Yellow	,	Green	);
	squareButton(	&zona_20	,	"Humedad:"		,	Yellow	,	Green	);
	squareButton(	&zona_21	,	"Presion:"		,	Yellow	,	Green	);
	squareButton(	&zona_22	,	"Incide UV:"		,	Yellow	,	Green	);
	sprintf((char*)buffer,"%.02f dC",	DATOS->Temperatura);
	squareButton(	&zona_23	,	(char *)buffer		,	Yellow	,	Green	);
	sprintf((char*)buffer,"%.02f %%",	DATOS->Humedad);
	squareButton(	&zona_24	,	(char *)buffer		,	Yellow	,	Green	);
	sprintf((char*)buffer,"%.02f Pas.",DATOS->Presion);
	squareButton(	&zona_25	,	(char *)buffer		,	Yellow	,	Green	);
	sprintf((char*)buffer,"%.02f UVs",	DATOS->IndiceUV);
	squareButton(	&zona_26	,	(char *)buffer		,	Yellow	,	Green	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__pintaMedidas2__()																//
//																								//
//		@brief		Esta función pinta la segunda pantalla de medidas.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__pintaMedidas2__(	void	)
{
	uint8_t buffer[23];
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_32	,	"Vel. del viento:"	,	Yellow	,	Green	);
	sprintf((char*)buffer, "%.02f metros/seg." ,	DATOS->VelViento);
	if (	ACTUALIZADOR->Anemometro	)
	{
		sprintf((char*)buffer, "%.02f metros/seg." ,	DATOS->VelViento);
		squareButton(	&zona_33	,	CLEAR_BUFFER		,	Yellow	,	Green	);
		ACTUALIZADOR->Anemometro = 0;						//	Digo que toca medir.
		squareButton(	&zona_33	,	(char *)buffer		,	Yellow	,	Green	);
	}
	squareButton(	&zona_34	,	"Claridad:"		,	Yellow	,	Green	);
	sprintf((char*)buffer,"%.02f LUX",	DATOS->Brillo);
	squareButton(	&zona_35	,	CLEAR_BUFFER		,	Yellow	,	Green	);
	squareButton(	&zona_35	,	(char *)buffer		,	Yellow	,	Green	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		squareButton()																	//
//																								//
//		@brief		Dibuja un botón cuadrado, con texto y colores.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void squareButton(screenZone_t* zone, char * text, uint16_t textColor, uint16_t lineColor)
{
	LCD_DrawLine( zone->x, zone->y, zone->x + zone->size_x, zone->y, lineColor);
	LCD_DrawLine( zone->x, zone->y, zone->x, zone->y + zone->size_y, lineColor);
	LCD_DrawLine( zone->x, zone->y + zone->size_y, zone->x + zone->size_x, zone->y + zone->size_y, lineColor);
	LCD_DrawLine( zone->x + zone->size_x, zone->y, zone->x + zone->size_x, zone->y + zone->size_y, lineColor);
	GUI_Text(zone->x + zone->size_x/2 - (strlen(text)/2)*8, zone->y + zone->size_y/2 - 8, (uint8_t*) text, textColor, Black);	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		checkTouchPanel()																//
//																								//
//		@brief		Verifica se si ha tocado la pantalla.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void checkTouchPanel(void)
{
	Coordinate* coord;
	
	coord = Read_Ads7846();
	
	if (coord > 0) {
	  getDisplayPoint(&display, coord, &matrix );
     pressedTouchPanel = 1;
   }   
   else
     pressedTouchPanel = 0;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		zoneNewPressed()																//
//																								//
//		@brief		Verifica si se ha presionado una cierta zona de la pantalla.							//
//																								//
//				@zone	Zona a comprobar.															//
//																								//
//				@return	0 - Si no se ha producido un toque.											//
//						1 - Si se ha producido un toque.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
int8_t zoneNewPressed(screenZone_t * zone)
{
	if (pressedTouchPanel == 1) {

		if ((display.x > zone->x) && (display.x < zone->x + zone->size_x) && 
			  (display.y > zone->y) && (display.y < zone->y + zone->size_y))
      {
         if (zone->pressed == 0)
         {   
            zone->pressed = 1;
            return 1;
         }
		   return 0;
      }
	}

   zone->pressed = 0;
	return 0;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

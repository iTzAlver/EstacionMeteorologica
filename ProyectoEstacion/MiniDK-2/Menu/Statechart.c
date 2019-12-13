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
extern uint16_t			contadorLUZ;
modificables_t		MODIFICABLES;
char buffer[23];
uint8_t	Modo_energetico=0;
uint8_t	Modo_brillo=3;
uint8_t	pressedTouchPanel;
uint8_t	__brilloFade = 0;
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
screenZone_t 	zona_18	=	{ 	MAXIMOX*0		,	MAXIMOY*0.3	, 	MAXIMOX 		, 	MAXIMOY*0.1	, 	0	};	//	Localización.
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
screenZone_t	zona_31	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX 		, 	MAXIMOY*0.2	, 	0	};	//	Slot libre.
screenZone_t 	zona_27m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.2	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta horas.
screenZone_t 	zona_28m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.35	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta minutos.
screenZone_t 	zona_29m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.5	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta segundos.
screenZone_t 	zona_30m	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.65	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Resta dia.
screenZone_t 	zona_27M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.2	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma horas.
screenZone_t 	zona_28M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.35	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma minutos.
screenZone_t 	zona_29M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.5	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma segundos.
screenZone_t 	zona_30M	=	{ 	MAXIMOX*0.75	,	MAXIMOY*0.65	, 	MAXIMOX*0.25	, 	MAXIMOY*0.15	, 	0	};	//	Suma dia.
//	ZONAS DE MEDIDAS 2 (VIENTO)
screenZone_t	zona_32	=	{ 	MAXIMOX*0		,	MAXIMOY*0.2	, 	MAXIMOX*0.5	, 	MAXIMOY*0.2	, 	0	};	//	Velocidad del viento.
screenZone_t	zona_32n	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.2	, 	MAXIMOX*0.5	, 	MAXIMOY*0.2	, 	0	};	//	Velocidad del viento.
screenZone_t	zona_33	=	{ 	MAXIMOX*0		,	MAXIMOY*0.4	, 	MAXIMOX 		, 	MAXIMOY*0.2	, 	0	};	//	Velocidad del viento.
screenZone_t	zona_34	=	{ 	MAXIMOX*0		,	MAXIMOY*0.6	, 	MAXIMOX*0.5	, 	MAXIMOY*0.2	, 	0	};	//	Cantidad de brillo.
screenZone_t	zona_34n	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.6	, 	MAXIMOX*0.5	, 	MAXIMOY*0.2	, 	0	};	//	Cantidad de brillo.
screenZone_t	zona_35	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX 		, 	MAXIMOY*0.2	, 	0	};	//	Cantidad de brillo.
//	Display de barras.
screenZone_t	zona_350	=	{ 	MAXIMOX*0		,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_351	=	{ 	MAXIMOX*0.1	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_352	=	{ 	MAXIMOX*0.2	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_353	=	{ 	MAXIMOX*0.3	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_354	=	{ 	MAXIMOX*0.4	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_355	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_356	=	{ 	MAXIMOX*0.6	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_357	=	{ 	MAXIMOX*0.7	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_358	=	{ 	MAXIMOX*0.8	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_359	=	{ 	MAXIMOX*0.9	,	MAXIMOY*0.8	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
//	Display de barras.
screenZone_t	zona_330	=	{ 	MAXIMOX*0.0	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_331	=	{ 	MAXIMOX*0.1	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_332	=	{ 	MAXIMOX*0.2	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_333	=	{ 	MAXIMOX*0.3	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_334	=	{ 	MAXIMOX*0.4	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_335	=	{ 	MAXIMOX*0.5	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_336	=	{ 	MAXIMOX*0.6	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_337	=	{ 	MAXIMOX*0.7	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_338	=	{ 	MAXIMOX*0.8	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
screenZone_t	zona_339	=	{ 	MAXIMOX*0.9	,	MAXIMOY*0.4	, 	MAXIMOX*0.1	, 	MAXIMOY*0.2	, 	0	};
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
	/**	@LOOP:	Primera parte del programa.	*/
	alimentaWDT();
	checkTouchPanel();
	if ( __brilloAuto && (SysTick->CTRL & 0x10000))	//	Cada 100 ms si el brillo auto está activado.
	{
		goto_LUT( DATOS->Brillo, BRILLO2CICLO_LDR , none , &Aux8 , none , none);
		modificaPulso(	PWM6	,	MODO_CICLO	,	Aux8	,	none	,	none	,	none	);	/**	@TODO: Cambiar por brillo automático. */
	}
	/**	@LOOP:	Máquina de estados LCD.		*/
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
				__brilloFade = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	1	,	none	,	none	,	none	);
				Modo_brillo = 0;
				Modo_energetico	=	0;	//	HP.
			}
			if (zoneNewPressed(	&zona_8))
			{
				__brilloAuto = 0;
				__brilloFade = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	20	,	none	,	none	,	none	);
				Modo_brillo = 1;
				Modo_energetico	=	0;	//	HP.
			}
			if (zoneNewPressed(	&zona_9))
			{
				__brilloAuto = 0;
				__brilloFade = 0;
				modificaPulso(	PWM6	,	MODO_CICLO	,	40	,	none	,	none	,	none	);
				Modo_brillo = 2;
				Modo_energetico	=	0;	//	HP.
			}
			if (zoneNewPressed(	&zona_10))
			{
				modificaPulso(	PWM6	,	MODO_CICLO	,	60	,	none	,	none	,	none	);
				__brilloAuto = 0;
				__brilloFade = 0;
				Modo_brillo = 3;
				Modo_energetico	=	0;	//	HP.
			}
			if (zoneNewPressed(	&zona_11))
			{
				__brilloAuto = 1;
				__brilloFade = 0;
				Modo_brillo = 4;
				Modo_energetico	=	1;	//	LP.
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
			
			
			if (zoneNewPressed(	&zona_13))
			{
				Modo_energetico	=	0;	//	HP.
				__brilloAuto		=	0;	//	No hay brillo auto.
				Modo_brillo		=	3;	//	Brillo a tope.
				modificaPulso(	PWM6	,	MODO_CICLO	,	60	,	none	,	none	,	none	);
				__brilloFade		=	0;
			}
			if (zoneNewPressed(	&zona_14))
			{
				Modo_energetico	=	1;	//	LP.
				Modo_brillo		=	4;	//	Brillo auto.
				__brilloAuto		=	1;	//	Activo el brillo automático.
				__brilloFade		=	0;	//	No pueda apagarse la pantalla.	
			}
			if (zoneNewPressed(	&zona_15))
			{
				Modo_energetico	=	2;	//	ULP.
				Modo_brillo		=	4;	//	Brillo auto.
				__brilloAuto		=	1;	//	Activo el brillo automático.
				__brilloFade		=	1;	//	Que pueda apagarse la pantalla.
				
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
	switch	(	Modo_brillo	)
	{
		case 0:
			squareButton(	&zona_7	,	"1"				,	White	,	White	);
			squareButton(	&zona_8	,	"2"				,	Yellow	,	Green	);
			squareButton(	&zona_9	,	"3"				,	Yellow	,	Green	);
			squareButton(	&zona_10	,	"4"				,	Yellow	,	Green	);
			squareButton(	&zona_11	,	"A"				,	Yellow	,	Green	);
			break;
		case 1:
			squareButton(	&zona_7	,	"1"				,	Yellow	,	Green	);
			squareButton(	&zona_8	,	"2"				,	White	,	White	);
			squareButton(	&zona_9	,	"3"				,	Yellow	,	Green	);
			squareButton(	&zona_10	,	"4"				,	Yellow	,	Green	);
			squareButton(	&zona_11	,	"A"				,	Yellow	,	Green	);
			break;
		case 2:
			squareButton(	&zona_7	,	"1"				,	Yellow	,	Green	);
			squareButton(	&zona_8	,	"2"				,	Yellow	,	Green	);
			squareButton(	&zona_9	,	"3"				,	White	,	White	);
			squareButton(	&zona_10	,	"4"				,	Yellow	,	Green	);
			squareButton(	&zona_11	,	"A"				,	Yellow	,	Green	);
			break;
		case 3:
			squareButton(	&zona_7	,	"1"				,	Yellow	,	Green	);
			squareButton(	&zona_8	,	"2"				,	Yellow	,	Green	);
			squareButton(	&zona_9	,	"3"				,	Yellow	,	Green	);
			squareButton(	&zona_10	,	"4"				,	White	,	White	);
			squareButton(	&zona_11	,	"A"				,	Yellow	,	Green	);
			break;
		case 4:
			squareButton(	&zona_7	,	"1"				,	Yellow	,	Green	);
			squareButton(	&zona_8	,	"2"				,	Yellow	,	Green	);
			squareButton(	&zona_9	,	"3"				,	Yellow	,	Green	);
			squareButton(	&zona_10	,	"4"				,	Yellow	,	Green	);
			squareButton(	&zona_11	,	"A"				,	White	,	White	);
			break;
	}
	squareButton(	&zona_12	,	"Play"			,	Yellow	,	Green	);
	switch	(	Modo_energetico	)
	{
		case 0:
			squareButton(	&zona_13	,	"HP"				,	Red		,	Red		);
			squareButton(	&zona_14	,	"LP"				,	Yellow	,	Green	);
			squareButton(	&zona_15	,	"ULP"			,	Yellow	,	Green	);
			break;
		case 1:
			squareButton(	&zona_13	,	"HP"				,	Yellow	,	Green	);
			squareButton(	&zona_14	,	"LP"				,	Blue		,	Blue		);
			squareButton(	&zona_15	,	"ULP"			,	Yellow	,	Green	);
			break;
		case 2:
			squareButton(	&zona_13	,	"HP"				,	Yellow	,	Green	);
			squareButton(	&zona_14	,	"LP"				,	Yellow	,	Green	);
			squareButton(	&zona_15	,	"ULP"			,	White	,	White	);
			break;
	}
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
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_17	,	"MEDIDAS ACTUALES"	,	Yellow	,	Green	);
	if	(	ACTUALIZADOR->TempRev	)
	{
		sprintf((char*)buffer,"Altura: %.02f m.",	DATOS->Lugar.Altura);
		squareButton(	&zona_18	,	(char *)buffer		,	Yellow	,	Green	);
	}
	squareButton(	&zona_19	,	"Vel. v.:"		,	Yellow	,	Green	);
	squareButton(	&zona_20	,	"Humedad:"		,	Yellow	,	Green	);
	squareButton(	&zona_21	,	"Claridad:"		,	Yellow	,	Green	);
	squareButton(	&zona_22	,	"Incide UV:"		,	Yellow	,	Green	);
	if	(	ACTUALIZADOR->Anemometro )
	{
		sprintf((char*)buffer,"%.02f mps",	DATOS->VelViento);
		squareButton(	&zona_23	,	(char *)buffer		,	Yellow	,	Green	);
		ACTUALIZADOR->Anemometro = 0;
	}
	
	if	(	ACTUALIZADOR->TempRev	)
	{
		sprintf((char*)buffer,"%.02f %%",	DATOS->Humedad);
		squareButton(	&zona_24	,	(char *)buffer		,	Yellow	,	Green	);
		ACTUALIZADOR->TempRev = 0;
	}
	sprintf((char*)buffer,"%.02f LUX",DATOS->Brillo);
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
	squareButton(	&zona_1	,	(char *)Clock		,	Yellow	,	Green	);
	squareButton(	&zona_2	,	"->"				,	Yellow	,	Green	);
	squareButton(	&zona_3	,	"<-"				,	Yellow	,	Green	);
	squareButton(	&zona_32	,	"Temperatura:"		,	Yellow	,	Green	);
	if	(	ACTUALIZADOR->TempRev	)
	{
		sprintf((char*)buffer,"%.02f dC",	DATOS->Temperatura);
		squareButton(	&zona_32n	,	(char *)buffer		,	Yellow	,	Green	);
		sprintf((char*)buffer,"%.02f mBar.",	DATOS->Presion);
		squareButton(	&zona_34n	,	(char *)buffer		,	Yellow	,	Green	);
		ACTUALIZADOR->TempRev = 0;
	}						//	Digo que toca medir.
	switch	(	(int)(10*(DATOS->Temperatura - MIN_TEMP)/(MAX_TEMP - MIN_TEMP))	)
	{
		case 0:
			squareBox( &zona_330 , Black);
			squareBox( &zona_331 , Black);
			squareBox( &zona_332 , Black);
			squareBox( &zona_333 , Black);
			squareBox( &zona_334 , Black);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 1:
			squareBox( &zona_330 , White);
			squareBox( &zona_331 , Black);
			squareBox( &zona_332 , Black);
			squareBox( &zona_333 , Black);
			squareBox( &zona_334 , Black);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 2:
			squareBox( &zona_330 , White);
			squareBox( &zona_331 , White);
			squareBox( &zona_332 , Black);
			squareBox( &zona_333 , Black);
			squareBox( &zona_334 , Black);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 3:
			squareBox( &zona_330 , Yellow);
			squareBox( &zona_331 , Yellow);
			squareBox( &zona_332 , Yellow);
			squareBox( &zona_333 , Black);
			squareBox( &zona_334 , Black);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 4:
			squareBox( &zona_330 , Yellow);
			squareBox( &zona_331 , Yellow);
			squareBox( &zona_332 , Yellow);
			squareBox( &zona_333 , Yellow);
			squareBox( &zona_334 , Black);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 5:
			squareBox( &zona_330 , Blue);
			squareBox( &zona_331 , Blue);
			squareBox( &zona_332 , Blue);
			squareBox( &zona_333 , Blue);
			squareBox( &zona_334 , Blue);
			squareBox( &zona_335 , Black);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 6:
			squareBox( &zona_330 , Blue);
			squareBox( &zona_331 , Blue);
			squareBox( &zona_332 , Blue);
			squareBox( &zona_333 , Blue);
			squareBox( &zona_334 , Blue);
			squareBox( &zona_335 , Blue);
			squareBox( &zona_336 , Black);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 7:
			squareBox( &zona_330 , Green);
			squareBox( &zona_331 , Green);
			squareBox( &zona_332 , Green);
			squareBox( &zona_333 , Green);
			squareBox( &zona_334 , Green);
			squareBox( &zona_335 , Green);
			squareBox( &zona_336 , Green);
			squareBox( &zona_337 , Black);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 8:
			squareBox( &zona_330 , Green);
			squareBox( &zona_331 , Green);
			squareBox( &zona_332 , Green);
			squareBox( &zona_333 , Green);
			squareBox( &zona_334 , Green);
			squareBox( &zona_335 , Green);
			squareBox( &zona_336 , Green);
			squareBox( &zona_337 , Green);
			squareBox( &zona_338 , Black);
			squareBox( &zona_339 , Black);
			break;
		case 9:
			squareBox( &zona_330 , Red);
			squareBox( &zona_331 , Red);
			squareBox( &zona_332 , Red);
			squareBox( &zona_333 , Red);
			squareBox( &zona_334 , Red);
			squareBox( &zona_335 , Red);
			squareBox( &zona_336 , Red);
			squareBox( &zona_337 , Red);
			squareBox( &zona_338 , Red);
			squareBox( &zona_339 , Black);
			break;
		case 10:
			squareBox( &zona_330 , Red);
			squareBox( &zona_331 , Red);
			squareBox( &zona_332 , Red);
			squareBox( &zona_333 , Red);
			squareBox( &zona_334 , Red);
			squareBox( &zona_335 , Red);
			squareBox( &zona_336 , Red);
			squareBox( &zona_337 , Red);
			squareBox( &zona_338 , Red);
			squareBox( &zona_339 , Red);
			break;
		default:
			if ( DATOS->Temperatura > MIN_TEMP)
			{
				squareBox( &zona_330 , Red);
				squareBox( &zona_331 , Red);
				squareBox( &zona_332 , Red);
				squareBox( &zona_333 , Red);
				squareBox( &zona_334 , Red);
				squareBox( &zona_335 , Red);
				squareBox( &zona_336 , Red);
				squareBox( &zona_337 , Red);
				squareBox( &zona_338 , Red);
				squareBox( &zona_339 , Red);
			}
			if ( DATOS->Temperatura < MIN_TEMP)
			{
				squareBox( &zona_330 , Black);
				squareBox( &zona_331 , Black);
				squareBox( &zona_332 , Black);
				squareBox( &zona_333 , Black);
				squareBox( &zona_334 , Black);
				squareBox( &zona_335 , Black);
				squareBox( &zona_336 , Black);
				squareBox( &zona_337 , Black);
				squareBox( &zona_338 , Black);
				squareBox( &zona_339 , Black);
			}
	};
	
	squareButton(	&zona_34	,	"Presion:"		,	Yellow	,	Green	);
	switch	(	(int)(10*(DATOS->Presion - MIN_PRES)/(MAX_PRES - MIN_PRES))	)
	{
		case 0:
			squareBox( &zona_350 , Black);
			squareBox( &zona_351 , Black);
			squareBox( &zona_352 , Black);
			squareBox( &zona_353 , Black);
			squareBox( &zona_354 , Black);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 1:
			squareBox( &zona_350 , White);
			squareBox( &zona_351 , Black);
			squareBox( &zona_352 , Black);
			squareBox( &zona_353 , Black);
			squareBox( &zona_354 , Black);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 2:
			squareBox( &zona_350 , White);
			squareBox( &zona_351 , White);
			squareBox( &zona_352 , Black);
			squareBox( &zona_353 , Black);
			squareBox( &zona_354 , Black);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 3:
			squareBox( &zona_350 , Yellow);
			squareBox( &zona_351 , Yellow);
			squareBox( &zona_352 , Yellow);
			squareBox( &zona_353 , Black);
			squareBox( &zona_354 , Black);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 4:
			squareBox( &zona_350 , Yellow);
			squareBox( &zona_351 , Yellow);
			squareBox( &zona_352 , Yellow);
			squareBox( &zona_353 , Yellow);
			squareBox( &zona_354 , Black);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 5:
			squareBox( &zona_350 , Blue);
			squareBox( &zona_351 , Blue);
			squareBox( &zona_352 , Blue);
			squareBox( &zona_353 , Blue);
			squareBox( &zona_354 , Blue);
			squareBox( &zona_355 , Black);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 6:
			squareBox( &zona_350 , Blue);
			squareBox( &zona_351 , Blue);
			squareBox( &zona_352 , Blue);
			squareBox( &zona_353 , Blue);
			squareBox( &zona_354 , Blue);
			squareBox( &zona_355 , Blue);
			squareBox( &zona_356 , Black);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 7:
			squareBox( &zona_350 , Green);
			squareBox( &zona_351 , Green);
			squareBox( &zona_352 , Green);
			squareBox( &zona_353 , Green);
			squareBox( &zona_354 , Green);
			squareBox( &zona_355 , Green);
			squareBox( &zona_356 , Green);
			squareBox( &zona_357 , Black);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 8:
			squareBox( &zona_350 , Green);
			squareBox( &zona_351 , Green);
			squareBox( &zona_352 , Green);
			squareBox( &zona_353 , Green);
			squareBox( &zona_354 , Green);
			squareBox( &zona_355 , Green);
			squareBox( &zona_356 , Green);
			squareBox( &zona_357 , Green);
			squareBox( &zona_358 , Black);
			squareBox( &zona_359 , Black);
			break;
		case 9:
			squareBox( &zona_350 , Red);
			squareBox( &zona_351 , Red);
			squareBox( &zona_352 , Red);
			squareBox( &zona_353 , Red);
			squareBox( &zona_354 , Red);
			squareBox( &zona_355 , Red);
			squareBox( &zona_356 , Red);
			squareBox( &zona_357 , Red);
			squareBox( &zona_358 , Red);
			squareBox( &zona_359 , Black);
			break;
		case 10:
			squareBox( &zona_350 , Red);
			squareBox( &zona_351 , Red);
			squareBox( &zona_352 , Red);
			squareBox( &zona_353 , Red);
			squareBox( &zona_354 , Red);
			squareBox( &zona_355 , Red);
			squareBox( &zona_356 , Red);
			squareBox( &zona_357 , Red);
			squareBox( &zona_358 , Red);
			squareBox( &zona_359 , Red);
			break;
		default:
			if ( DATOS->Presion > MAX_PRES)
			{
				squareBox( &zona_350 , Red);
				squareBox( &zona_351 , Red);
				squareBox( &zona_352 , Red);
				squareBox( &zona_353 , Red);
				squareBox( &zona_354 , Red);
				squareBox( &zona_355 , Red);
				squareBox( &zona_356 , Red);
				squareBox( &zona_357 , Red);
				squareBox( &zona_358 , Red);
				squareBox( &zona_359 , Red);
			}
			if ( DATOS->Presion < MIN_PRES)
			{
				squareBox( &zona_350 , Black);
				squareBox( &zona_351 , Black);
				squareBox( &zona_352 , Black);
				squareBox( &zona_353 , Black);
				squareBox( &zona_354 , Black);
				squareBox( &zona_355 , Black);
				squareBox( &zona_356 , Black);
				squareBox( &zona_357 , Black);
				squareBox( &zona_358 , Black);
				squareBox( &zona_359 , Black);
			}
	}
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
	LCD_DrawLine( zone->x, zone->y, zone->x + zone->size_x - 1, zone->y, lineColor);
	LCD_DrawLine( zone->x, zone->y, zone->x, zone->y + zone->size_y - 1, lineColor);
	LCD_DrawLine( zone->x, zone->y + zone->size_y - 1, zone->x + zone->size_x - 1, zone->y + zone->size_y - 1, lineColor);
	LCD_DrawLine( zone->x + zone->size_x - 1, zone->y, zone->x + zone->size_x - 1, zone->y + zone->size_y - 1, lineColor);
	GUI_Text(zone->x + zone->size_x/2 - (strlen(text)/2)*8, zone->y + zone->size_y/2 - 8, (uint8_t*) text, textColor, Black);	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		squareBox()																	//
//																								//
//		@brief		Dibuja un cuadrado de un color.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void squareBox(screenZone_t* zone, uint16_t color)
{
	int i;
	for (i = 0; i < (zone->size_x - 4) ; i++)
	{
		LCD_DrawLine( zone->x + i + 2, zone->y + 2, zone->x + i + 2, zone->y + zone->size_y - 2, color);
	}
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
	 /**	@MOD:	Esto lo he añadido yo	*/
	 if (contadorLUZ	>=	(FREQ_OVERFLOW_SYSTICK * MODIFICABLES.TiempoBrillo))	//	Si se ha activado el apagar pantalla...
	 {
		modificaPulso		(	PWM6,	MODO_CICLO	,	60	,	none	,	none			,	none			);	//	La enciendo como si hubiese habido un reset.
		Modo_brillo = 3;
		if	(	Modo_energetico > 1	)
		{
			__brilloAuto = 1;
			Modo_brillo = 4;
			if	(	Modo_energetico == 2 )
			{
				__brilloFade = 1;
			}
		}

	}
	 contadorLUZ = 0;		//	Reseteo el contador de apagar la pantalla.
	}

   zone->pressed = 0;
	return 0;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

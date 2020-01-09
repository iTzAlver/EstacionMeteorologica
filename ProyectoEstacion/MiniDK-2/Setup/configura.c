/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		configura.c																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que configura y llama a las funciones de configuración para hacer un Setup del programa.//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el código de configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef 	CONFIGURA
#define	CONFIGURA
#include "configura.h"
#endif
extern State_t		*	ESTADO;
extern misDatos_t	*	DATOS;
extern modificables_t	MODIFICABLES;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		Esta función configura el programa entero.											//
//																								//
//		@ref			__configuraPWM__		->	PWM.h												//
//					modificaPulso			->	PWM.h												//
//					__configuraLCD__		->	Statechart.h											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraPrograma__(	void	)	
{
	__configuraLCD__		();
	LCD_Clear(Black);
	__pintaCargandoInicio__	();
	__iniciaVariables__		();
	LCD_Clear(Black);
	__pintaCargandoSeno__	();
	//crearSeno				();
	LCD_Clear(Black);
	__pintaCargandoConexion__();
	__configuraWEB__		();
	LCD_Clear(Black);
	__pintaCargandoIniciando__();
	__configuraSysTick__	();
	__configuraTimer0__		();
	__configuraLDR__		();
	__configuraUVA30A__		();
	__configuraUFONO__		();
	__configuraRTC__		();
	__configuraPWM__	(	Fpwm	,	ACTIVOS_2_1 | ACTIVOS_6_1	);
	modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	90	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
	modificaPulso		(	PWM6,	MODO_CICLO	,	50	,	none	,	none			,	none			);
	//__configuraWDT__		();
	__configuraDAC__		();
	__configuraDMA__		();
	__configuraOW__		();
	__configuraAnemometro__	();
	__configuraUART0__		();
//	__configuraUART3__		();
	__configuraI2C__		();
#ifndef	DEBUG
// 	TouchPanel_Calibrate();
#endif
	LCD_Clear(Black);
	__pintaCargandoDone__	();
	LCD_Clear(Black);
	ESTADO->CHART = PANTALLA_INICIO;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__iniciaVariables__()															//
//																								//
//		@brief		Esta función inicia las variables del sistema para que tengan un momento inicial.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __iniciaVariables__()
{
	ESTADO->CHART = PANTALLA_LOADING;
	DATOS->Temperatura 		= 0;
	DATOS->Humedad 		= 0;
	DATOS->Presion 		= 0;
	DATOS->VelViento 		= 0;
	DATOS->IndiceUV 		= 0;
	DATOS->Lugar.Altura		= 0;	
	DATOS->Lugar.Longitud	= 0;	
	DATOS->Lugar.Latitud	= 0;
	
	MODIFICABLES.Max_servo_t	=	(float)MAXIMO_TEMPERATURA;
	MODIFICABLES.Min_servo_t	= 	(float)MINIMO_TEMPERATURA;
	MODIFICABLES.Max_servo_p	=	(float)MAXIMO_PRESION;
	MODIFICABLES.Min_servo_p	=	(float)MINIMO_PRESION;
	MODIFICABLES.TiempoBrillo 	=	10;
	MODIFICABLES.Var_medida		=	0;		//	0 la temperatura, 1 la presión.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

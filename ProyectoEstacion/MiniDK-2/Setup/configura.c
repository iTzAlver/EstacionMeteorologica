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
extern modificables_t	*	MODIFICABLES;
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
	__iniciaVariables__		();
//	crearSeno				();
//	__configuraWEB__		();
	__configuraSysTick__	();
	__configuraTimer0__		();
	__configuraLDR__		();
	__configuraUVA30A__		();
	__configuraUFONO__		();
	__configuraLCD__		();
	__configuraRTC__		();
	__configuraPWM__	(	Fpwm	,	ACTIVOS_2_1 | ACTIVOS_6_1	);
	modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	90	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
	modificaPulso		(	PWM6,	MODO_CICLO	,	50	,	none	,	none			,	none			);
//	__configuraWDT__		();
	__configuraDMA__		();
	__configuraDAC__		();
	__configuraOW__		();
	__configuraAnemometro__	();
//	__configuraUART0__		();
//	__configuraUART3__		();
	__configuraI2C__		();
#ifndef	DEBUG
// 	TouchPanel_Calibrate();
#endif
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
	DATOS->Temperatura 		= 24.00;
	DATOS->Humedad 		= 1.55;
	DATOS->Presion 		= 1.55;
	DATOS->VelViento 		= 3.33;
	DATOS->IndiceUV 		= 1.20;
	DATOS->Lugar.Altura		= 2.1;	
	DATOS->Lugar.Longitud	= 2.1;	
	DATOS->Lugar.Latitud	= 2.1;
	
	MODIFICABLES->Max_servo_t	=	MAXIMO_SERVO;
	MODIFICABLES->Min_servo_t	= 	MINIMO_SERVO;
	MODIFICABLES->Max_servo_p	=	MAXIMO_PRESION;
	MODIFICABLES->Min_servo_p	=	MINIMO_PRESION;
	MODIFICABLES->Max_temp_alarma = 	50;
	MODIFICABLES->Min_temp_alarma = 	-10;
	MODIFICABLES->Max_pres_alarma = 	1000;
	MODIFICABLES->Min_pres_alarma = 	20;
	MODIFICABLES->TiempoBrillo 	=	10;
	MODIFICABLES->Var_medida		=	0;		//	0 la temperatura, 1 la presión.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

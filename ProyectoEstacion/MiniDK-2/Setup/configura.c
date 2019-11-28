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
	__configuraWEB__		();
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
	__configuraUART0__		();
	__configuraUART3__		();
	__configuraI2C__		();
#ifndef	DEBUG
 	TouchPanel_Calibrate();
#endif
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
	DATOS->Lugar.Altura		= 500.12;	
	DATOS->Lugar.Longitud	= 74.33;	
	DATOS->Lugar.Latitud	= 74.33;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

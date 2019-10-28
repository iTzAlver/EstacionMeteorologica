/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		main.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente del programa principal.												//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@global																		//
//					@main																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código fuente.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	HEADER
#define	HEADER
#include	"header.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@global		Programa principal, variables globales.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
misDatos_t		objDATOS;					//	Objeto.
misDatos_t	*	DATOS = &objDATOS;			//	Mis datos almacenados en la variable objDATOS.
State_t 			objESTADO;				//	Objeto.
State_t		*	ESTADO = &objESTADO;		//	Declarar como extern. (Hey, compilador, creeme que hay una variable por ahí que se llama ESTADO)
Counters_t 		objCOUNTERS;				//	Objeto.
Counters_t	*	COUNTERS = &objCOUNTERS;		//	Declarar como extern. (Hey, compilador, creeme que hay una variable por ahí que se llama COUNTERS)
actualizador_t		objACTUALIZADOR;			//	Objeto.
actualizador_t	*	ACTUALIZADOR = &objACTUALIZADOR; //	Declarar como extern. (Hey, compilador, creeme que hay una variable por ahí que se llama ACTUALIZADOR)
uint16_t			AUDIO[200];				//   Audio.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@main		Programa principal, inicio after-reset.												//
//																								//
//		@ref			__configuraPrograma__	->	configura.h											//
//					__mainLoop__			->	statechart.h											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
int main	()
{
	__configuraPrograma__();
	while (	1	)
	{
		__mainLoop__();
		__mantenerTCP__();
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

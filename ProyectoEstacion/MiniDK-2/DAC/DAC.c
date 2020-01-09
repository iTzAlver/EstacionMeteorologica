/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente que contiene las funciones para audio (DAC).								//
//																								//
//		@category		Periférico.																	//
//																								//
//		@map			@include																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el código de LDR.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	DAC
#define	DAC
#include	"DAC.h"
#endif
extern actualizador_t *	ACTUALIZADOR;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraDAC__()																//
//																								//
//		@brief		Función de configuración del DAC y su timer (Timer2).									//
//																								//
//		@REMARK:		Para activar un periodo del DAC (2 segundos)											//													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraDAC__()
{
	//	Se configura en el DMA.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		activarDac()																	//
//																								//
//		@brief		Señal de activar el timer del DAC.													//
//																								//
//		@REMARK:		En nuestro sistema de muestreos que se 'suicidan' al acabar, es necesario definir 			//
//					también para las muestras que no encajan del todo con nuestra folosofía de trabajo			//
//					alguna vía para activar ese 'suicidio' , en este caso al ser un revividor asíncrono			//
//					no definido en nuestro Timer0 debemos llamar esta función desde el Statechart (menú)			//
//					y comprobar el estado del DAC antes de revivirlo por si acaso se está ejecutando el			//
//					audio o el usuario está en ese mismo momento grabandolo tener algún mecanismo de 			//
//					proección; que es este caso son los ACTUALIZADORES, que nos marcan el estado de la medida.	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void activarDac()
{
	/**	@TODO:	DMA*/
	LPC_GPDMACH0->DMACCConfig	|=	1;								//	Activo el DMA.
	LPC_TIM1->MCR				=	(1	<<3	)	|	(1	<<	4);		//	Activo la interrupción por MR1 y reset por MR1.
	LPC_TIM1->MR1				=	(Fclk*DURACION_AUDIO) - 1;			//	Valor de MR1.
	LPC_TIM1->TCR				=	0x2;								//	Reset del timer.
	LPC_TIM1->TCR				=	0x1;								//	El timer cuenta.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		activarDac()																	//
//																								//
//		@brief		Señal de activar el timer del DAC.													//
//																								//
//		@REMARK:		Activador del DAC.																//		
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void desactivarDAC()
{
	LPC_GPDMACH0->DMACCConfig	&=	~0x1;			//	Desactivo el DMA.
	ACTUALIZADOR->Audiorev		=	1;				//	Señalizo el fin del DAC.
	LPC_TIM1->MCR				&=	~(7	<<	3);		//	Desactivo la interrupción por MR1 y reset tras MR1.
	LPC_DAC->DACR				=	0;				//	No hay señal de salida.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

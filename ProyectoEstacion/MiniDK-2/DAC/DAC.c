/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.c																		//
//		@version		6.01																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente que contiene las funciones para audio (DAC).								//
//																								//
//		@category		Periférico.																	//
//																								//
//		@map			@include																		//
//					@variables																	//
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
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@variables		Variables del fichero.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
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
	LPC_GPIO3->FIODIR	|=	(1	<<	LECTURA_AUDIO	) | (1	<<	ESCRITURA_AUDIO);		// Leds de lectura / escritura de audio.
	LPC_GPIO3->FIOCLR	=  	(1	<<	LECTURA_AUDIO);								//Turn ON LED1
	LPC_GPIO3->FIOCLR	=  	(1	<<	ESCRITURA_AUDIO);								//Turn ON LED2
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		activarDac()																	//
//																								//
//		@brief		Señal de activar el timer del DAC.													//
//																								//
//		@REMARK:		Utiliza DMA.																	//
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
	ACTUALIZADOR->Audiorev		=	0;								//	Señalizo el bloqueo de audio.
	LPC_GPIO3->FIOSET			=	(	1	<<	ESCRITURA_AUDIO);		//	Señaizo escritura de audio.
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
	LPC_GPDMACH0->DMACCConfig	&=	~0x1;							//	Desactivo el DMA.
	ACTUALIZADOR->Audiorev		=	1;								//	Señalizo el fin del DAC.
	LPC_GPIO3->FIOCLR			=	(	1	<<	ESCRITURA_AUDIO);		//	Señaizo escritura de audio.
	LPC_TIM1->MCR				&=	~(7	<<	3);						//	Desactivo la interrupción por MR1 y reset tras MR1.
	LPC_DAC->DACR				=	0;								//	No hay señal de salida.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

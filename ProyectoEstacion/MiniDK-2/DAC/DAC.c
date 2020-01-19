/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.c																		//
//		@version		6.01																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		C�digo fuente que contiene las funciones para audio (DAC).								//
//																								//
//		@category		Perif�rico.																	//
//																								//
//		@map			@include																		//
//					@variables																	//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el c�digo de LDR.									//
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
//		@brief		Funci�n de configuraci�n del DAC y su timer (Timer2).									//
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
//		@brief		Se�al de activar el timer del DAC.													//
//																								//
//		@REMARK:		Utiliza DMA.																	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void activarDac()
{
	/**	@TODO:	DMA*/
	LPC_GPDMACH0->DMACCConfig	|=	1;								//	Activo el DMA.
	LPC_TIM1->MCR				=	(1	<<3	)	|	(1	<<	4);		//	Activo la interrupci�n por MR1 y reset por MR1.
	LPC_TIM1->MR1				=	(Fclk*DURACION_AUDIO) - 1;			//	Valor de MR1.
	LPC_TIM1->TCR				=	0x2;								//	Reset del timer.
	LPC_TIM1->TCR				=	0x1;								//	El timer cuenta.
	ACTUALIZADOR->Audiorev		=	0;								//	Se�alizo el bloqueo de audio.
	LPC_GPIO3->FIOSET			=	(	1	<<	ESCRITURA_AUDIO);		//	Se�aizo escritura de audio.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		activarDac()																	//
//																								//
//		@brief		Se�al de activar el timer del DAC.													//
//																								//
//		@REMARK:		Activador del DAC.																//		
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void desactivarDAC()
{
	LPC_GPDMACH0->DMACCConfig	&=	~0x1;							//	Desactivo el DMA.
	ACTUALIZADOR->Audiorev		=	1;								//	Se�alizo el fin del DAC.
	LPC_GPIO3->FIOCLR			=	(	1	<<	ESCRITURA_AUDIO);		//	Se�aizo escritura de audio.
	LPC_TIM1->MCR				&=	~(7	<<	3);						//	Desactivo la interrupci�n por MR1 y reset tras MR1.
	LPC_DAC->DACR				=	0;								//	No hay se�al de salida.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

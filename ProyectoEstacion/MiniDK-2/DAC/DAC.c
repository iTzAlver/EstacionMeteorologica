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
#include  "DAC.h"
#endif
extern	actualizador_t		*	ACTUALIZADOR;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraDAC__()																//
//																								//
//		@brief		Función de configuración del DAC y su timer (Timer2).									//
//																								//
//		@REMARK:		Para activar un periodo del DAC (2 segundos)											//													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraDAC__()
{
	LPC_PINCON->PINSEL1		|=	(2	<<	(26-16)*2);
	LPC_DAC->DACCTRL	=	(1	<<	1)							//	Activo la modalidad de doble buffer.
					|	(1	<<	2)							//	Activo la acción por timeout.
					|	(1	<<	3);							//	Salida en ráfaga.	
	LPC_DAC->DACCNTVAL	=	(uint32_t)(0x61A);						//	Ajusto la frecuencia del DAC.
	//LPC_DAC->DACCNTVAL	=	(uint32_t)(Fclk*TsAudio - 1);				//	Ajusto la frecuencia del DAC.
	ACTUALIZADOR->Audiorev	=	1;								//	Señal de activación de audio..
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		escribirEnDac()																//
//																								//
//		@brief		Interfaz de escritura en el DAC.													//
//																								//
//					@Valor		Valor a escribir en el DAC.											//
//					@Cutoff		Valor de reducción de formato: Elimina Cutoff LSB bits.					//
//								Si viene del ADC: Cutoff debe de ser 2 por la diferencia del formato.			//
//								Si Cutoff es mayor que 10, se desplaza las posiciones excedidas en 			//
//								sentido contrario.													//
//																								//
//					BIAS_DAC:		Ver manual, settling time de 2.5us y corriente limitada en 350mA.			//
//								Con las BIAS activadas, nos vale para audio.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void escribirEnDac(	uint16_t	Valor	,	uint8_t	Cutoff	)
{
	if ( Cutoff > 10 )
	{
		Valor	=	Valor << (Cutoff-10);	//	Desplazo los bits de corte.
	}
	else
	{
		Valor	=	Valor >> Cutoff;		//	Desplazo los bits de corte.
	}
	LPC_DAC->DACR	&=	~BORRAR_DAC;			//	Borro del valor del DAC anterior.
	LPC_DAC->DACR	|=	DAC_BIAS | (Valor << 6);	//	Escribo el nuevo valor del DAC con DAC Bias activado.
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
	//LPC_GPDMACH0->DMACCConfig	|=	1;								//	Activo el DMA.
	LPC_TIM1->MCR				=	(1	<<3	)	|	(1	<<	4);		//	Activo la interrupción por MR1 y reset por MR1.
	LPC_TIM1->MR1				=	(Fclk*DURACION_AUDIO) - 1;			//	Valor de MR1.
	LPC_TIM1->TCR				=	0x2;								//	Reset del timer.
	LPC_TIM1->TCR				=	0x1;								//	El timer cuenta.
}

void desactivarDAC()
{
	LPC_GPDMACH0->DMACCConfig	&=	~0x1;			//	Desactivo el DMA.
	ACTUALIZADOR->Audiorev		=	1;				//	Señalizo el fin del DAC.
	LPC_TIM1->MCR				&=	~(7	<<	3);		//	Desactivo la interrupción por MR1 y reset tras MR1.
	LPC_DAC->DACR				=	0;				//	No hay señal de salida.
	__configuraDAC__();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

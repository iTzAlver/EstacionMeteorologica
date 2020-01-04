/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DAC.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		C�digo fuente que contiene las funciones para audio (DAC).								//
//																								//
//		@category		Perif�rico.																	//
//																								//
//		@map			@include																		//
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
#include  "DAC.h"
#endif
extern	actualizador_t		*	ACTUALIZADOR;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraDAC__()																//
//																								//
//		@brief		Funci�n de configuraci�n del DAC y su timer (Timer2).									//
//																								//
//		@REMARK:		Para activar un periodo del DAC (2 segundos)											//													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraDAC__()
{
	LPC_PINCON->PINSEL1		|=	(2	<<	(26-16)*2);
	LPC_DAC->DACCTRL	=	(1	<<	1)							//	Activo la modalidad de doble buffer.
					|	(1	<<	2)							//	Activo la acci�n por timeout.
					|	(1	<<	3);							//	Salida en r�faga.	
	LPC_DAC->DACCNTVAL	=	(uint32_t)(0x61A);						//	Ajusto la frecuencia del DAC.
	//LPC_DAC->DACCNTVAL	=	(uint32_t)(Fclk*TsAudio - 1);				//	Ajusto la frecuencia del DAC.
	ACTUALIZADOR->Audiorev	=	1;								//	Se�al de activaci�n de audio..
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		escribirEnDac()																//
//																								//
//		@brief		Interfaz de escritura en el DAC.													//
//																								//
//					@Valor		Valor a escribir en el DAC.											//
//					@Cutoff		Valor de reducci�n de formato: Elimina Cutoff LSB bits.					//
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
//		@brief		Se�al de activar el timer del DAC.													//
//																								//
//		@REMARK:		En nuestro sistema de muestreos que se 'suicidan' al acabar, es necesario definir 			//
//					tambi�n para las muestras que no encajan del todo con nuestra folosof�a de trabajo			//
//					alguna v�a para activar ese 'suicidio' , en este caso al ser un revividor as�ncrono			//
//					no definido en nuestro Timer0 debemos llamar esta funci�n desde el Statechart (men�)			//
//					y comprobar el estado del DAC antes de revivirlo por si acaso se est� ejecutando el			//
//					audio o el usuario est� en ese mismo momento grabandolo tener alg�n mecanismo de 			//
//					proecci�n; que es este caso son los ACTUALIZADORES, que nos marcan el estado de la medida.	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void activarDac()
{
	/**	@TODO:	DMA*/
	//LPC_GPDMACH0->DMACCConfig	|=	1;								//	Activo el DMA.
	LPC_TIM1->MCR				=	(1	<<3	)	|	(1	<<	4);		//	Activo la interrupci�n por MR1 y reset por MR1.
	LPC_TIM1->MR1				=	(Fclk*DURACION_AUDIO) - 1;			//	Valor de MR1.
	LPC_TIM1->TCR				=	0x2;								//	Reset del timer.
	LPC_TIM1->TCR				=	0x1;								//	El timer cuenta.
}

void desactivarDAC()
{
	LPC_GPDMACH0->DMACCConfig	&=	~0x1;			//	Desactivo el DMA.
	ACTUALIZADOR->Audiorev		=	1;				//	Se�alizo el fin del DAC.
	LPC_TIM1->MCR				&=	~(7	<<	3);		//	Desactivo la interrupci�n por MR1 y reset tras MR1.
	LPC_DAC->DACR				=	0;				//	No hay se�al de salida.
	__configuraDAC__();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

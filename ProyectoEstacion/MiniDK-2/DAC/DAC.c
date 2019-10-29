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
//		@REMARK:		Para activar un periodo del DAC (2 segundos)																						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraDAC__()
{
	LPC_SC->PCONP 	|= 	0x400000;			//	Activo el m�dulo del timer 2.
	LPC_PINCON->PINSEL1	|=	(	DAC_FUNC	<< 	2*DAC_PIN);
	LPC_TIM2->MCR 	=	TIMER2_MCR_MASK;		//	Activo el ISR y reseteo TC. 
	LPC_TIM2->TCR	|=	ACTIVAR_TIMER;			//	Activo el timer.
	LPC_TIM2->MR0	=	Ftick * TsAudio - 1;	//	Cargo para que interrumpa cada 5s.
	NVIC_SetPriority(	TIMER2_IRQn	,	0	);
	ACTUALIZADOR->Audiorev	=	1;			//	Sistema listo para emitir/recibir el audio.
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
//																								//
//					BIAS_DAC:		Ver manual, settling time de 2.5us y corriente limitada en 350mA.			//
//								Con las BIAS activadas, nos vale para audio y consume menos que sin ellas.		//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void escribirEnDac(	uint16_t	Valor	,	uint8_t	Cutoff	)
{
	Valor		=	Valor >> Cutoff;		//	Desplazo los bits de corte.
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
	NVIC_EnableIRQ(	TIMER2_IRQn	);		//	Activo el timer del DAC.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		uFono.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que contiene todo lo relaccionado con el micrófono.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados para el auido del micrófono.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	UFONO
#define	UFONO
#include	"uFono.h"
#endif

extern uint8_t	Timer2_MODO;
uint8_t	YaPuedesMedir = 1;
uint32_t	ADC_ConfigBuffer;
uint32_t  ADC_IntenBuffer;

void __configuraUFONO__()
{
//	LPC_PINCON->PINSEL1 |= ~(0x3 << (2*PIN_UFONO));
	LPC_PINCON->PINSEL1 |= (FUNC_ADC << (2*PIN_UFONO));
	
	//	NEW:
	LPC_TIM1->MR0	=	Fclk*TsAudio - 1;	//	Cada MR0 se genera una interrupción de leer el audio.
	LPC_TIM1->TCR	=	0x2;				//	Reset al contador.
	LPC_TIM1->TCR  =	0x1;				//	Activo contador.
	LPC_TIM1->MCR  =    0x0;				//	MR0 que NO genera la interrupción.
	NVIC_EnableIRQ(	TIMER0_IRQn	);	//	Activo interrupción.
}

void	lanzaUFONO()
{
	//	Preparo el contexto.
	YaPuedesMedir 		= 	0;					//	Bloqueo el ADC para el audio.
	Timer2_MODO		=	MODO_ENTRADA;			//	Indico que el audio está siendo grabado.
	ADC_ConfigBuffer 	= 	LPC_ADC->ADCR;			//	Guardo el contexto de la configuración.
	ADC_IntenBuffer 	=	LPC_ADC->ADINTEN;		//	Guardo el contexto de la configuración de interrupciones.
	//	Configurar ADC.
	LPC_ADC->ADINTEN 	= 	1;					//	No quiero interrupciones por conversión excepto en AD0.0.
	LPC_ADC->ADCR		&=	~0xFF;				//	Borro el sel entero, sólo voy a usar un canal.
	LPC_ADC->ADCR		|=	CANAL_ADC_UF;			//	Canal para el audio.
	//
	LPC_ADC->ADCR		&=	~(0xFF << 8);			//	Borro el clkdiv.
	LPC_ADC->ADCR		|=	(0x1 << 8);			//	CLKDiv a 1.
	//	Empiezo con la conversión.
	LPC_ADC->ADCR	&=	~BRUST_PIN;				//	QUITO EL MODO BURST.			//	Reanimo el timer.
	LPC_ADC->ADCR	&=	~(0x7 << 24);				//	Configuro el start.
	LPC_ADC->ADCR	|=	ADC_START;				//	Configuro el start.
	//	Activo el timer.
	LPC_TIM1->MCR	=	0x2;						//	Reset on match.
	LPC_TIM1->TCR	=	0x2;						//	Que resetee.
	LPC_TIM1->TCR	=	0x1;						//	Que cuente.
	LPC_TIM1->EMR	=	0x31;					//	Activo el Match0 en modo toogle.
}

void recuperaContexto()
{
	//	Recupero el contexto.
	if (	Timer2_MODO == MODO_ENTRADA	)			//	Si toca recuperar...
	{
		LPC_ADC->ADCR		=	ADC_ConfigBuffer;	//	Cargo el contexto de la configuración.
		LPC_ADC->ADINTEN	=	ADC_IntenBuffer;	//	Cargo el contexto de la configuración de interrupciones.
		LPC_ADC->ADCR		&=	(0x7 << 24);		//	Borro el START del ADC.
		LPC_ADC->ADCR		|=	(0xFF << 8);		//	CLKDIV max.
		YaPuedesMedir 		= 	1;				//	Desbloqueo el ADC.
		Timer2_MODO 		= 	MODO_SALIDA;		//	Default modo salida.
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

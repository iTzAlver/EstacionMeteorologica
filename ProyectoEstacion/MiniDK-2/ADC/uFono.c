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
}

void	lanzaUFONO()
{
	//	Preparo el contexto.
	YaPuedesMedir 		= 	0;					//	Bloqueo el ADC para el audio.
	Timer2_MODO		=	MODO_ENTRADA;			//	Indico que el audio está siendo grabado.
	ADC_ConfigBuffer 	= 	LPC_ADC->ADCR;			//	Guardo el contexto de la configuración.
	ADC_IntenBuffer 	=	LPC_ADC->ADINTEN;		//	Guardo el contexto de la configuración de interrupciones.
	//	Configurar ADC.
	LPC_ADC->ADINTEN 	= 	0;					//	No quiero interrupciones por conversión.
	LPC_ADC->ADCR		&=	~0xFF;				//	Borro el sel entero, sólo voy a usar un canal.
	LPC_ADC->ADCR		|=	CANAL_ADC_UF;			//	Canal para el audio.
	//	Empiezo con la conversión.
	LPC_ADC->ADCR	&=	~BRUST_PIN;				//	QUITO EL MODO BURST.
	NVIC_EnableIRQ(	TIMER2_IRQn	);			//	Reanimo el timer.
	LPC_ADC->ADCR	&=	~ADC_START;				//	Lanzo la primera muestra.
	LPC_ADC->ADCR	|=	ADC_START;				//	Lanzo la primera muestra.
}

void recuperaContexto()
{
	//	Recupero el contexto.
	LPC_ADC->ADCR		=	ADC_ConfigBuffer;	//	Cargo el contexto de la configuración.
	LPC_ADC->ADINTEN	=	ADC_IntenBuffer;	//	Cargo el contexto de la configuración de interrupciones.
	LPC_ADC->ADCR		&=	~ADC_START;		//	Borro el START del ADC.
	YaPuedesMedir 		= 	1;				//	Desbloqueo el ADC.
	Timer2_MODO 		= 	MODO_SALIDA;		//	Default modo salida.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

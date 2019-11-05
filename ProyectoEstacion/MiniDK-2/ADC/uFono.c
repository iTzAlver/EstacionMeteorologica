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

void __configuraUFONO__()
{
	
}

void	lanzaUFONO()
{
	YaPuedesMedir = 0;
	//	Configurar ADC.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	LPC_ADC->ADCR	&=	~BRUST_PIN;			//	QUITO EL MODO BRUST.
	Timer2_MODO	=	MODO_ENTRADA;			//	Indico que el audio está siendo grabado.
	NVIC_EnableIRQ(	TIMER2_IRQn	);		//	Reanimo el timer.
	LPC_ADC->ADCR	|=	ADC_START;			//	Lanzo la primera muestra.
}

void recuperaContexto()
{
	LPC_ADC->ADCR	&=	~ADC_START;			//	Borro el START del ADC.
	YaPuedesMedir = 1;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

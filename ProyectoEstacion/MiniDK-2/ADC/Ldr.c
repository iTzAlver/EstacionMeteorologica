/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LDR.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente que contiene las funciones para LDR (ADC).								//
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
#ifndef	LDR
#define	LDR
#include	"LDR.h"
#endif
uint32_t	ELBUFF;
extern actualizador_t	*	ACTUALIZADOR;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion																					//
//																								//
//		@ref																						//
//																								//
//																								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraLDR__()
{
	LPC_SC->PCONP 			|=	PCONP_ADC_ON;		//	Enciendo el ADClock.
	LPC_PINCON->PINSEL1		|=	PINSEL_ADC01;		//	AD0.1
	LPC_ADC->ADCR			|=	BRUST_PIN			//	Modo ráfaga.
						|	SEL_CANAL1		//	AD0.1 activado.
						|	ADC_POWER;		//	Empiezo apagando el ADC.
	LPC_ADC->ADINTEN		|=	SEL_CANAL1;		//	Genera interrupción el canal 1.	(Debería ser el penúltimo)
	NVIC_EnableIRQ(	ADC_IRQn	);
}
void	ADC_IRQHandler()
{
	LPC_SC->PCONP			&=	~PCONP_ADC_ON;		//	Mato el ADC.
	ELBUFF = LPC_ADC->ADDR1;						//	Leo el ADC.
	ACTUALIZADOR->LDRrev	=	0;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

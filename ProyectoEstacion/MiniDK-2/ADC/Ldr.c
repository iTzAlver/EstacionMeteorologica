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
extern	misDatos_t	*	DATOS;
float	BUFFER_BRILLO = 0;
extern 	actualizador_t	*	ACTUALIZADOR;
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
	ACTUALIZADOR->LDRrev	=	1;				//	Inicia para activar.
	NVIC_EnableIRQ(	ADC_IRQn	);
}
void	ADC_IRQHandler()
{
	LPC_ADC->ADCR			&=	~BRUST_PIN;													//	Mato el BURST.
	BUFFER_BRILLO			=	(float)((LPC_ADC->ADDR1&(0xFFF0)) >> 4);							//	Empieza a partir del bit 4.
	BUFFER_BRILLO			= 	(float)RESISTENCIA_PULL*(BUFFER_BRILLO)/(float)((float)0xFFF - BUFFER_BRILLO);	//	Leo el ADC. (Ressitencia del LDR en kOhms)
	goto_LUT(	BUFFER_BRILLO	,	BRILLO_LDR	,	(float *)&DATOS->Brillo	,	none	,	none	,	none	);	//	Traduzco resistencias a LUX.
	ACTUALIZADOR->LDRrev	=	1;															//	Digo que el LDR ha sido leido.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LDR.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		C�digo fuente que contiene las funciones para LDR (ADC).								//
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
#ifndef	LDR
#define	LDR
#include	"LDR.h"
#endif
extern	misDatos_t	*	DATOS;
float	BUFFER_BRILLO = 0;
float	BUFFER_UVA    = 0;
extern 	actualizador_t	*	ACTUALIZADOR;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion	__configuraLDR__()																	//
//																								//
//		@brief	Esta funci�n configura el ADC y el LDR													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraLDR__()
{
	LPC_SC->PCONP 			|=	PCONP_ADC_ON;		//	Enciendo el ADClock.
	LPC_PINCON->PINSEL1		|=	PINSEL_ADC01;		//	AD0.1
	LPC_PINCON->PINMODE1	&=	~PINMODE_ADC01;	//	AD0.1
	LPC_ADC->ADCR			|=	BRUST_PIN			//	Modo r�faga.
						|	SEL_CANAL1		//	AD0.1 activado.
						|	ADC_POWER			//	Empiezo ENCENDIENDO el ADC.
						|	CLK_DIV_MAX;		//	Clkdiv hace que Fadc = 12.5, inferior al umbral de 13MHz. (Ojo: clkdiv = 0 implica que no funcione en placa).
	LPC_ADC->ADINTEN		|=	SEL_CANAL1;		//	Genera interrupci�n el canal 1.	(Deber�a ser el pen�ltimo)
	ACTUALIZADOR->LDRrev	=	1;				//	Inicia para activar.
	LPC_ADC->ADINTEN		&=	~(SEL_CANAL_GLOBAL);//	Apago la interrupci�n global.
	NVIC_EnableIRQ(	ADC_IRQn	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER	ADC_IRQHandler()																	//
//																								//
//		@brief	Esta funci�n gestiona la interrupci�n del ADC.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	ADC_IRQHandler()
{
	LPC_ADC->ADCR			&=	~BRUST_PIN;														//	Mato el BURST.
	BUFFER_BRILLO			=	(float)((LPC_ADC->ADDR1&(0xFFF0)) >> 4);								//	Empieza a partir del bit 4.
	BUFFER_BRILLO			/=	(float)0xFFF;														//	Relacci�n de c�digo. (C�digo/C�digo m�ximo)
	BUFFER_BRILLO			= 	RESISTENCIA_PULL*(BUFFER_BRILLO)/(BUFFER_BRILLO - 1.00);					//	Leo el ADC. (Ressitencia del LDR en kOhms)
	goto_LUT(	BUFFER_BRILLO	,	BRILLO_LDR	,	(float *)&DATOS->Brillo	,	none	,	none	,	none	);	//	Traduzco resistencias a LUX.
	BUFFER_UVA			=	(float)((LPC_ADC->ADDR2&(0xFFF0)) >> 4);								//	Empieza a partir del bit 4.
	DATOS->IndiceUV		= 	(float)VINDICE*VREF*BUFFER_UVA/(float)(0xFFF);							//	Traducci�n del c�digo al �ndice.
	ACTUALIZADOR->LDRrev	=	1;																//	Digo que el LDR ha sido leido.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Timers.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que configura y programa los manejadores de los timers.							//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados para los timers.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	TIMERS
#define	TIMERS
#include	"Timers.h"
#endif
uint8_t					TIM0_ticks = 0;
extern	Counters_t	*	COUNTERS;
extern	misDatos_t	*	DATOS;
extern	actualizador_t	*	ACTUALIZADOR;
extern	uint8_t		*	AUDIO;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraSysTick__()															//
//																								//
//		@brief		Configura el systick para desbordar cada 100 ms.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraSysTick__()
{
	SysTick->LOAD = (SystemCoreClock / FREQ_OVERFLOW_SYSTICK) - 1;	//	SysTick configurado a desbordar cada 100 ms para TcpNet.
	SysTick->CTRL = MASCARA_CTRL_SYSTICK;				//	Fcpu como clock y no activo la interrupción del SysTickTimer.
	SysTick_Config( SystemCoreClock / FREQ_OVERFLOW_SYSTICK);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer0__()															//
//																								//
//		@brief		Configura el Timer0 para nterrumpir cada Ts0 segundos.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraTimer0__()
{
	LPC_SC->PCONP 	|= 	TIMER0_BIT;				//	Activo el módulo del timer 0.
	LPC_TIM0->MCR 	=	TIMER0_MCR_MASK;			//	Activo el ISR y reseteo TC.
	LPC_TIM0->PR	=	0;						//	Sin prescaler.
	LPC_TIM0->TCR	|=	ACTIVAR_TIMER;				//	Activo el timer.
	LPC_TIM0->MR0	=	Ftick * Ts0 - 1;			//	Cargo para que interrumpa cada 5s.
	NVIC_SetPriority(	TIMER0_IRQn	,	1	);	//	Para que el ADC interrumpa bien.
	NVIC_EnableIRQ(	TIMER0_IRQn	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer1__()															//
//																								//
//		@GOTO		¡DEFINIDO EN EL OW! (OneWire.c)													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer2__()															//
//																								//
//		@GOTO		¡DEFINIDO EN EL DAC! (DAC.c)														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer3__()															//
//																								//
//		@brief																					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		SysTick_Handler()																//
//																								//
//		@brief		Manejador de la interrupción del SysTick. Cada 100 ms se realizan acciones.				//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void SysTick_Handler()
{
	timer_tick();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER0_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del Timer0. Reanima el muestreo de los sensores.				//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void TIMER0_IRQHandler(	void	)
{
	LPC_TIM0->IR	=	LPC_TIM0->IR;
	if( 	!(TIM0_ticks % (uint8_t)CsAnemometro)	)
	{
		LPC_TIM1->CCR	=	CCR_MASCARA_EN;
		if ( !ACTUALIZADOR->AnemometroRev )
		{
			DATOS->VelViento = 0;
			ACTUALIZADOR->Anemometro = 1;
		}
		ACTUALIZADOR->AnemometroRev = 0;
	}
	
	if(	!(TIM0_ticks % (uint8_t)CsLDR)	)	//	LDR + UVA van el BURST.
	{
		if(	ACTUALIZADOR->LDRrev	)
		{
			LPC_SC->PCONP	|=	PCONP_ADC_ON;
			ACTUALIZADOR->LDRrev = 0;
			LPC_ADC->ADCR	&=	~ADC_START;	//	Ojito que es modo ráfaga, no hay start.
			LPC_ADC->ADCR	|=	BRUST_PIN;	//	Ráfaga.
		}
	}
	if(	!(TIM0_ticks % (uint8_t)CsTnH)	)	//	Sensor de humedad y temperatura.
	{
		
	}
	TIM0_ticks++;
	modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	(180*(DATOS->Temperatura - TEMP_MIN)/(TEMP_MAX - TEMP_MIN))	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER1_IRQHandler()																//
//																								//
//		@brief																					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER2_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del DAC. Hecha para generar el audio.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void TIMER2_IRQHandler()
{
	LPC_TIM2->IR	|=	LPC_TIM2->IR;							//	Borro flag de interrupción.
	escribirEnDac(AUDIO[COUNTERS->Audio]	,	2	);			//	Escribo el valor del audio en el DAC.
	if ( COUNTERS->Audio++ == MUESTRAS_AUDIO - 1	)				//	Reset y fin al audio.
	{
		COUNTERS->Audio = 0;								//	Reset al contador.
		NVIC_DisableIRQ(	TIMER2_IRQn	);					//	Desactivo el timer del DAC cuando finaliza el audio.
		ACTUALIZADOR->Audiorev	=	1;						//	Le digo al sistema que ya ha acabado el DAC.
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER3_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del DAC. Hecha para generar el audio.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


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
uint8_t					TIM0_ticks 	= 	0;
uint8_t					Timer2_MODO	=	MODO_SALIDA;
uint32_t					CAP11_BUFF	=	0;

uint16_t					contadorLUZ	=	0;

float					TEMP_min		=	TEMP_MIN;
float					TEMP_max		=	TEMP_MAX;

extern 	uint8_t			__brilloAuto;			//	Esta línea no me gusta nada, pero era mucho mejor que complicarlo.
extern	uint8_t			YaPuedesMedir;
extern	Counters_t	*	COUNTERS;
extern	misDatos_t	*	DATOS;
extern	actualizador_t	*	ACTUALIZADOR;
extern	uint8_t		*	AUDIO;
extern	uint8_t		*	CAPcont;
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
	SysTick->CTRL = MASCARA_CTRL_SYSTICK;						//	Fcpu como clock y no activo la interrupción del SysTickTimer.
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
	LPC_SC->PCONP |= 	0x1 << 22 | 0x1 << 23 | 1 << 16;	//	Todos los timer.
	LPC_SC->PCONP 	|= 	TIMER0_BIT;					//	Activo el módulo del timer 0.
	LPC_TIM0->MCR 	=	TIMER0_MCR_MASK;				//	Activo el ISR y reseteo TC.
	LPC_TIM0->PR	=	0;							//	Sin prescaler.
	LPC_TIM0->TCR	|=	ACTIVAR_TIMER;					//	Activo el timer.
	LPC_TIM0->MR0	=	Ftick * Ts0 - 1;				//	Cargo para que interrumpa cada 0.5s.
	NVIC_SetPriority(	TIMER0_IRQn	,	1	);		//	Para que el ADC interrumpa bien.
	NVIC_EnableIRQ(	TIMER0_IRQn	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer1__()															//
//																								//
//		@GOTO		¡DEFINIDO EN EL OW O EN EL ANEMOMETRO! (Anemometro.c o OneWire.c)						//
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
	if (contadorLUZ 	<	SYST_BRILLO)
	{
		contadorLUZ++;
	}
	else
	{
		if (!__brilloAuto)									//	Si pasan 60s y el brillo automático está desactivado...
		{
			modificaPulso(	PWM6	,	MODO_CICLO	,	1	,	none	,	none	,	none	);	//	Apago la pantalla.
		}
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER0_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del Timer0. Reanima el muestreo de los sensores.				//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	Bloque 1:	Apoyo del timer 1:
//							Temperatura + Humedad + Vel.Viento.
static void	_subAnemoTempe()
{
	LPC_TIM0->IR	=	LPC_TIM0->IR;				//	Borro interrupción.
	if( 	!(TIM0_ticks % (uint8_t)CsCAP)	)		//	Si toca muestrear captures...
	{
		LPC_TIM1->CCR	|=	CCR_MASCARA_EN;		//	Genera interrupción el CAP1.0, ojo que se mata así en el timer 1.
		LPC_TIM1->CCR	|=	OW_CCR_MASCARA_EN;		//	Genera interrupción el CAP1.1, ojo que se mata así en el timer 1.
		mideTemperatura();						//	Le digo a la placa que lanze la señal de request.
		medirBMP();							//	Leo el sensor de presión atmosférica.
		if ( !ACTUALIZADOR->AnemometroRev && YaPuedesMedir)		//	Si el actualizador está a 0 (Es decir, no hay datos capturados).
		{
			DATOS->VelViento = 0;				//	No hay viento.
			ACTUALIZADOR->Anemometro = 1;			//	Ya está medido, es 0 m/s.
		}
		ACTUALIZADOR->AnemometroRev = 0;			//	Digo que ya he medido.
		ACTUALIZADOR->TempRev	=	1;
	}	
}
//	Bloque 2:	ADC burst:
//						UVA + LDR.
static void 	_subBurst()
{
	if(	!(TIM0_ticks % (uint8_t)CsADC)	)			//	LDR + UVA van el BURST.
	{
		if(	ACTUALIZADOR->LDRrev && YaPuedesMedir	)	//	Es bloqueable por el audio.
		{
			LPC_SC->PCONP			|=	PCONP_ADC_ON;	//	Enciendo el ADC.
			ACTUALIZADOR->LDRrev 	= 	0;			//	Aviso que no he medido aún.
			LPC_ADC->ADCR			&=	~ADC_START;	//	Ojito que es modo ráfaga, no hay start.
			LPC_ADC->ADCR			|=	BRUST_PIN;	//	Ráfaga.
		}
	}	
}
//	Ahora sí, el handler:	Ojo que aquí es donde actualizo el servo.
void TIMER0_IRQHandler(	void	)
{
	_subAnemoTempe();
	_subBurst();
	TIM0_ticks++;
	modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	(180*(DATOS->Temperatura - TEMP_min)/(TEMP_max - TEMP_min))	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER1_IRQHandler()																//
//																								//
//		@ref			Ir a Anemómetro.c (comparte con OneWire.c)											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void TIMER1_IRQHandler()
{
	uint8_t SWART	=	(uint8_t)(LPC_TIM1->IR);

	if	(SWART	&	CAP10_IR)
	{
		mideAnemometro();
	}
	if	(SWART	&	MR1_IR)
	{
		desactivarDAC();
	}
	LPC_TIM1->IR	=	LPC_TIM1->IR;			//	No pierdo nada en asegurarme que se cierra el timer.			
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER2_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del DAC Y ADC. Hecha para generar y recibir el audio.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void TIMER2_IRQHandler()
{
	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER3_IRQHandler()																//
//																								//
//		@brief		Manejador de la interrupción del DAC. Hecha para generar el audio.						//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	USADO POR EL MONOHILO.
void	TIMER3_IRQHandler()
{
	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Timers.c																		//
//		@version		7.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que configura y programa los manejadores de los timers.							//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@variables																	//
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
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@variables		Variables del fichero.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t					TIM0_ticks 	= 	0;
uint8_t					Timer2_MODO	=	MODO_SALIDA;
uint32_t					CAP11_BUFF	=	0;
//	Contador.
uint16_t					contadorLUZ	=	0;
//	Externos.
extern 	uint8_t			__brilloAuto;
extern	uint8_t			__brilloFade;
extern	uint8_t			YaPuedesMedir;
extern	Counters_t	*	COUNTERS;
extern	misDatos_t	*	DATOS;
extern	actualizador_t	*	ACTUALIZADOR;
extern	uint8_t		*	AUDIO;
extern	uint8_t		*	CAPcont;
extern	modificables_t	MODIFICABLES;
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
//		@GOTO		¡DEFINIDO EN EL ANEMOMETRO! (Anemometro.c)											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer3__()															//
//																								//
//		@GOTO		¡DEFINIDO EN EL ONEWIRE! (OneWire.c)												//
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
	if (contadorLUZ 	<	FREQ_OVERFLOW_SYSTICK * (MODIFICABLES.TiempoBrillo))
	{
		contadorLUZ++;
	}
	else
	{
		if (__brilloFade)									//	Si pasan 60s y el brillo automático está desactivado...
		{
			__brilloAuto = 0;
			__brilloFade = 0;
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
//	Actualizo el servo.
void __subServo(	void	)
{
	if (	!MODIFICABLES.Var_medida	)
	{
		if (DATOS->Temperatura >= MODIFICABLES.Max_servo_t)
		{
			modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	180	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
			if (ACTUALIZADOR->Audiorev)
			{
				ACTUALIZADOR->Audiorev = 0;
				__configuraTono__();
				activarDac();
			}
		}
		if (DATOS->Temperatura <= MODIFICABLES.Min_servo_t)
		{
			modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	0	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
			if (ACTUALIZADOR->Audiorev)
			{
				ACTUALIZADOR->Audiorev = 0;
				__configuraAudio__();
				activarDac();
			}
		}
		modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	(180*(DATOS->Temperatura - MIN_TEMP)/(MAX_TEMP - MIN_TEMP))	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
	}
	else
	{
		if (DATOS->Presion >= MODIFICABLES.Max_servo_p)
		{
			modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	180	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
			if (ACTUALIZADOR->Audiorev)
			{
				ACTUALIZADOR->Audiorev = 0;
				__configuraTono__();
				activarDac();
			}
		}
		if (DATOS->Presion <= MODIFICABLES.Min_servo_p)
		{
			modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	0	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
			if (ACTUALIZADOR->Audiorev)
			{
				ACTUALIZADOR->Audiorev = 0;
				__configuraAudio__();
				activarDac();
			}
		}
		modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	(180*(DATOS->Presion - MIN_PRES)/(MAX_PRES - MIN_PRES))	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
	}
}
//	Ahora sí, el handler:	Ojo que aquí es donde actualizo el servo.
void TIMER0_IRQHandler(	void	)
{
	_subAnemoTempe();
	_subBurst();
	TIM0_ticks++;
	__subServo();
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
//		@brief		N/A																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void TIMER2_IRQHandler()
{
	//	NO USADO.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		TIMER3_IRQHandler()																//
//																								//
//		@brief		Timer de apoyo para el monohilo.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
//	USADO POR EL MONOHILO.
void	TIMER3_IRQHandler()
{
	//	NO USADO.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


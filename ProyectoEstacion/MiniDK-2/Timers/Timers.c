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
	LPC_SC->PCONP 	|= 	TIMER0_BIT;				//	Activo el módulo del timer 0.
	LPC_TIM0->MCR 	=	TIMER0_MCR_MASK;			//	Activo el ISR y reseteo TC.
	LPC_TIM0->PR	=	0;						//	Sin prescaler.
	LPC_TIM0->TCR	|=	ACTIVAR_TIMER;				//	Activo el timer.
	LPC_TIM0->MR0	=	Ftick * Ts0 - 1;			//	Cargo para que interrumpa cada 0.5s.
	NVIC_SetPriority(	TIMER0_IRQn	,	1	);	//	Para que el ADC interrumpa bien.
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
		activaMedidaOW();						//	Le digo a la placa que lanze la señal de request.
		if ( !ACTUALIZADOR->AnemometroRev && YaPuedesMedir)		//	Si el actualizador está a 0 (Es decir, no hay datos capturados).
		{
			DATOS->VelViento = 0;				//	No hay viento.
			ACTUALIZADOR->Anemometro = 1;			//	Ya está medido, es 0 m/s.
		}
		ACTUALIZADOR->AnemometroRev = 0;			//	Digo que ya he medido.
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
	modificaPulso		(	PWM2,	MODO_SERVO	,	none	,	(180*(DATOS->Temperatura - TEMP_MIN)/(TEMP_MAX - TEMP_MIN))	,	MINIMO_SERVO	,	MAXIMO_SERVO	);
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
	switch(	SWART	)
	{
		case	CAP10_IR:
			mideAnemometro();
			break;
		case	CAP11_IR:
			//mideTemperatura();
			break;
		case MR1_IR:
			desactivarDAC();
			break;
		default:
			/**	@TOUSE:	Puedo configurar el timer por match.	*/
			break;
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
	LPC_TIM2->IR	|=	LPC_TIM2->IR;								//	Borro flag de interrupción.
	switch(	Timer2_MODO	)
	{
		case	MODO_SALIDA:
			escribirEnDac(AUDIO[COUNTERS->Audio]	,	12	);		//	Escribo el valor del audio en el DAC, con un cutoff de 2 dado que las muestras son de 8 bits.
			break;
		case	MODO_ENTRADA:
			AUDIO[COUNTERS->Audio]	=	(uint8_t)((0xFF) & (LPC_ADC->ADDR0 >> (4+4)));		//	El ADC es de 12 bits y las muestras de 8 bits, por lo que hay que reducir los 4 LSB.
			LPC_ADC->ADCR	&=	~ADC_START;											//	Lanzar siguiente muestra.		
			LPC_ADC->ADCR	|=	ADC_START;											//	Lanzar siguiente muestra.
			break;
		default:
			/**	@TODO:	Añaidr códigos de error.	*/
			break;
	}
	if ( COUNTERS->Audio++ == MUESTRAS_AUDIO - 1	)				//	Reset y fin al audio.
	{
		COUNTERS->Audio = 0;								//	Reset al contador.
		NVIC_DisableIRQ(	TIMER2_IRQn	);					//	Desactivo el timer del DAC cuando finaliza el audio.
		ACTUALIZADOR->Audiorev	=	1;						//	Le digo al statechart que ya ha acabado el ciclo de audio.
		recuperaContexto();									//	Recupero el contexto del micrófono en el ADC.
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


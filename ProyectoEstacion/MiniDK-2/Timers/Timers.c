
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
extern	misDatos_t	*	DATOS;
uint8_t					TIM0_ticks = 0;
extern	actualizador_t	*	ACTUALIZADOR;
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
//	NVIC_EnableIRQ(	SysTick_IRQn	);
	SysTick_Config( SystemCoreClock / FREQ_OVERFLOW_SYSTICK);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraTimer0__()															//
//																								//
//		@brief		Configura el Timer0 para muestrear cada TIEMPO_MUESTRO segundos.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraTimer0__()
{
	LPC_SC->PCONP 	|= 	TIMER0_BIT;		//	Activo el módulo del timer 0.
	LPC_TIM0->MCR 	=	TIMER0_MCR_MASK;	//	Activo el ISR y reseteo TC.
	LPC_TIM0->PR	=	0;				//	Sin prescaler.
	LPC_TIM0->TCR	|=	ACTIVAR_TIMER;		//	Activo el timer.
	LPC_TIM0->MR0	=	Ftick * Ts0 - 1;	//	Cargo para que interrumpa cada 5s.
	NVIC_SetPriority(	TIMER0_IRQn	,	0	);
	NVIC_EnableIRQ(	TIMER0_IRQn	);
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
	
	if(	!(TIM0_ticks % (uint8_t)CsLDR)	)
	{
		if(	ACTUALIZADOR->LDRrev	)
		{
			LPC_SC->PCONP	|=	PCONP_ADC_ON;
		}
	}
	
	if(	!(TIM0_ticks % (uint8_t)CsUVA)	)
	{
		
	}
	TIM0_ticks++;
}
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
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


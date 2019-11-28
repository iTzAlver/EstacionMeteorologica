/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Timers.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para configurar los timers.												//
//																								//
//		@category		Principal.																	//
//																								//
//		@map			@include																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados para los timers.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	RTL
#define	RTL
#include	"RTL.h"
#endif
#ifndef	LPC17XX
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
#ifndef	ANEMOMETRO
#define	ANEMOMETRO
#include	"Anemometro.h"
#endif
#ifndef	LDR
#define	LDR
#include	"LDR.h"
#endif
#ifndef	DAC
#define	DAC
#include	"DAC.h"
#endif
#ifndef	PWM
#define	PWM
#include	"PWM.h"
#endif
#ifndef	UFONO
#define	UFONO
#include	"uFono.h"
#endif
#ifndef	ONEWIRE
#define	ONEWIRE
#include	"OneWire.h"
#endif
#ifndef	I2C
#define	I2C
#include	"I2C.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes a los timers.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	FREQ_OVERFLOW_SYSTICK	10							//	Frecuencia en Hz de overflow o fin de cuenta del SysTick.
#define	ENABLEBIT_SYST			0x1
#define	FCPUBIT_SYST			0x4
#define	ENABLEINTBIT_SYST		0x2
#define	MASCARA_CTRL_SYSTICK	FCPUBIT_SYST | ENABLEBIT_SYST | ENABLEINTBIT_SYST
#define	SYSTICK_COUNTFLAG		0x1 << 16
//	Para cada timer.
#define	ACTIVAR_TIMER			0x1
#define	RESET_TIMER_TCR		0x2
#define	TIMER0_BIT			(0x1 << 1)
#define	TIMER1_BIT			(0x1 << 2)
#define	TIMER2_BIT			(0x1 << 22)
#define	TIMER3_BIT			(0x1 << 23)
#define	TIMER0_MCR_MASK		0x3 << (0*3)					//	Activo la interrupción y reseteo el contador.
#define	TIMER1_MCR_MASK		0x3 << (0*3)					//	No usado.
#define	TIMER2_MCR_MASK		0x3 << (0*3)
#define	TIMER3_MCR_MASK		0x1 << (0*3)

#define	MODO_ENTRADA			1
#define	MODO_SALIDA			0	
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes a los timers.	      							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraSysTick__	(	void	);	//	TCP.
void __configuraTimer0__		(	void	);	//	Muestreo.
void __configuraTimer1__		(	void	);	//	...
void __configuraTimer2__		(	void	);	//	Audio.
void __configuraTimer3__		(	void	);	//	...
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

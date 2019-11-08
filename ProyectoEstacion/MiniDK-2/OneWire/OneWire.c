/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		OneWire.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código que configura el protocolo monohilo del sensor de temperatura y humedad.				//
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
//		@include		Estos son los archivos utilizados para el protocolo OneWire.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	ONEWIRE
#define	ONEWIRE
#include	"OneWire.h"
#endif
uint8_t	OW_TramaRx[SIZEOF_TRAMA];
uint32_t	TramaRx;
uint8_t	CheckSum;
uint8_t	MySum;
uint8_t	QueViene = 0;
extern	Counters_t	*	COUNTERS;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraOW__()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraOW__()
{
	LPC_PINCON->PINMODE3     &=   ~(OW_PULL_UP << (2*3));		//	PULL_UP
	LPC_PINCON->PINMODE3	|=	OW_PULL_UP << (2*3);		// 	PULL_UP
	LPC_PINCON->PINSEL3     	&=   ~((OW_CAPTURE_FUNC) << (2*3));//	CAPTURE1.1
	LPC_PINCON->PINSEL3		|=	(OW_CAPTURE_FUNC) << (2*3);	//	CAPTURE1.1
	LPC_TIM1->CTCR 		|= 	OW_CTCR_MASCARA;			//	Flanco de subida.
	LPC_TIM1->CCR			|=	OW_CCR_MASCARA_EN;			//	Inicio con interrupción.
	//	Necesario para la señal de inicio.
	LPC_RIT->RICOMPVAL		=	(uint32_t)((float)Fclk*0.005);//	Interrumpe el RIT en 5 ms.
	NVIC_EnableIRQ(	RIT_IRQn	);						//	Activo el RIT interrupt.
	LPC_SC->PCONP 			|=	1 << 16;					//	Su clk.
	LPC_RIT->RICTRL		|=	1 << 1;					//	Reset al contador.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		mideTemperatura()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void mideTemperatura()
{
	LPC_TIM1->IR 	= 	CAP11_IR;						//	Desactivo la interrupción.
	LPC_TIM1->CCR	&=	~OW_CCR_MASCARA_DIS;			//	Cuando termino la medida desactivo el capture.
}
void activaMedidaOW()
{
	//Configurar RIT para dentro de 5000 us.
	LPC_RIT->RICTRL		=	0;
	LPC_RIT->RICTRL		|=	0x1 << 3;					//	Activo el RIT.
	LPC_PINCON->PINSEL3		&=	~(0X3 << (2*3));			// 	GPIO.
	LPC_GPIO1->FIODIR		|=	1 << 19;					//	SALIDA.
	LPC_GPIO1->FIOCLR		|=	(0x1 << 19);				//	Lo pongo a 0.
	
}
void RIT_IRQHandler()
{
	COUNTERS->RITicks++;								//	Incremento el contador del RIT.
	LPC_PINCON->PINMODE3     &=   ~(0x3 << (2*3));			//	PULL_UP
	LPC_GPIO1->FIOSET		|=	(0x1 << 19);				//	Lo pongo a 0.
	LPC_PINCON->PINSEL3     	&=   ~((OW_CAPTURE_FUNC) << (2*3));//	CAPTURE1.1
	LPC_PINCON->PINSEL3		|=	(OW_CAPTURE_FUNC) << (2*3);	//	CAPTURE1.1
	LPC_RIT->RICTRL		&=	~(0x1 << 3);				//	Desactivo el RIT.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


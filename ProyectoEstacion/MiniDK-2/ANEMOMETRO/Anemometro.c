/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Anemometro.c																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa donde se encuentran las funciones correspondientes al					//
//					anemómetro de la estación.														//
//																								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del anemómetro.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	ANEMOMETRO
#define	ANEMOMETRO
#include	"Anemometro.h"
#endif
uint8_t	CAPcont		=	2*PULSOS_VUELTA;
uint8_t	SLAYERcont	=	0;
uint32_t	CLKbuff[]		=	{0 , 0};
extern	misDatos_t	*	DATOS;
extern	actualizador_t	*	ACTUALIZADOR;
float	aux_viento	=	0;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraAnemometro__()														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraAnemometro__()
{
	LPC_PINCON->PINMODE3     &=   ~(PULL_UP << (2*2));		// 	PULL_UP
	LPC_PINCON->PINMODE3	|=	PULL_UP << (2*2);			// 	PULL_UP
	LPC_PINCON->PINSEL3     	&=   ~((CAPTURE_FUNCION) << (2*2));//	CAPTURE1.0
	LPC_PINCON->PINSEL3		|=	(CAPTURE_FUNCION) << (2*2);	//	CAPTURE1.0
	LPC_TIM1->CTCR 		|= 	CTCR_MASCARA;				//	Flanco de subida.
	LPC_TIM1->CCR			|=	CCR_MASCARA_EN;			//	Inicio con interrupción.
	LPC_SC->PCONP 			|= 	TIMER1_BIT;				//	Activo el módulo del timer 1.
	LPC_TIM1->PR			=	0;						//	Sin prescaler.
	LPC_TIM1->TCR			|=	RESET_TIMER_TCR;			//	Reseteo el contador.
	LPC_TIM1->TCR			&=   ~RESET_TIMER_TCR;			//	Reseteo el contador.
	LPC_TIM1->TCR			|=	0x1;						//  	Que cuente.
	LPC_PINCON->PINSEL3		|=	0x3	<<	4;				//	Entrada como CAP1.0.
	NVIC_EnableIRQ(	TIMER1_IRQn	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@HANDLER		mideAnemometro()																//
//																								//
//		@brief		Es la medidas del anemómetro, se suicida al acabar y es reanimada por el reanimador cada 5s.	//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void mideAnemometro()
{
					/**	@WARNING:	Esto me parece un poco sucio, pero es la única manera de que no se generen 
								interrupciones espúrias utilizando únicamente recursos sorftware. Idealmente
								no debería usar delays y mucho menos en interrupciones. Si no uso esto se generan
								varias interrupciones por flanco debido al ruido. Esto se arregla con un condensador
								a masa en la entrada, pero es perder recursos hardware y he decidido perderlos 
								mediante software.*/
					int i;
					for(i = 0; i < 30000; i++) {}		
					/**	@TODO Poner condensadores entre Vin y masa del capture 1.0 para evitar doble int en flancos ascendentes.*/
		
		
	LPC_TIM1->IR = 1 << 4;						//	Desactivo la interrupción.
	CAPcont++;								//	Incremento el contador de pulsos.
	if 	(	CAPcont 	>=	PULSOS_VUELTA	)	/**	@WARNING: Se generan __UN__ interrupciones por pulso y 2*PULSOS_VUELTA por vuelta.*/
	{
		CLKbuff[1] = CLKbuff[0];					//	Almaceno el valor anterior.
		CLKbuff[0] = LPC_TIM1->CR0;				//	Cargo el valor actual.
		CAPcont = 0;							//	Reseteo el contador de pulsos.
		aux_viento 	= 	Ftick*(float)PI*(float)DIAMETRO_ANEMOMETRO/((float)1000*(float)((uint32_t)CLKbuff[0] - (uint32_t)CLKbuff[1]));	// Metros / segundo.
		SLAYERcont++;							//	Hay warmup, aumento el slayer.
		if (	SLAYERcont == WARMUP_CICLOS )
		{
			LPC_TIM1->CCR	|=	~CCR_MASCARA_DIS;	//	Slay capture. OJO: QUE HAY QUE REVIVIRLO.
			SLAYERcont = 0;					//	Reseteo el slayer.
			DATOS->VelViento = aux_viento;		//	Guardo el valor calentado.
			ACTUALIZADOR->AnemometroRev = 0;		//	Digo que he medido al timer.
			ACTUALIZADOR->Anemometro = 1;			//	Digo que he medido al statechart.
		}
		else
		{
			LPC_TIM1->CCR	|=	CCR_MASCARA_EN;	//	Si no, está activado.
		}
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

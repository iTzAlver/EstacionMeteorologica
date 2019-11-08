#ifdef	DEBUG

#include	"DEBUG.h"

void ON_DEBUG_SETUP()
{
	LPC_PINCON->PINSEL4	|=	(0x1	<< (10*2));	//	EINT0
	LPC_SC->EXTINT		|=	0x1;				//	EINT0
	LPC_SC->EXTMODE	|=	0x1;				//	Flanco de bajada.
	NVIC_EnableIRQ(	EINT0_IRQn	);
}



void ON_DEBUG()
{
	//	Idle
}


void	EINT0_IRQHandler()
{
	uint32_t	VAL;
	LPC_SC->EXTINT	=	0x1;
	VAL  =    LPC_GPIO2->FIOPIN;
	VAL	=	((LPC_GPIO2->FIOPIN)&(0x3 << 11)) >> 11;
	switch(	VAL	)
	{
		case	3:
			
			break;
		case 2:
			activarDac();
			break;
		case 1:
			lanzaUFONO();
			break;
		case 0:
			break;
		default:
			break;
	}
}





















#endif

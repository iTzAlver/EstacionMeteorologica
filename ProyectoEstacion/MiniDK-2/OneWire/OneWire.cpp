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

extern	Counters_t	*	COUNTERS;
extern	uint8_t			sigInit;
uint8_t	OWESTADO	=	OWDEEPSLEEP;

class OW {
	public:
		
	void ConfiguraEntrada()
	{
	
	}
	void SetPin(	uint8_t	Nivel)
	{
	
	}
	
	void	StateChart()
	{
		switch(	OWESTADO	)
		{
			case	OWDEEPSLEEP:
				if	(	sigInit	)	
				{
					sigInit 	= 	0;			//	Pongo la señal de inicio a 0.
					OWESTADO 	= 	OWINICIO0;	//	Cambio a empezar transimisión.
					Tick 	= 	0;			//	Pongo el contador de ticks a 0.
					ConfiguraEntrada();			//	Configuro el onewire como entrada.
				}
				break;
			case	OWINICIO0:
				if (Tick >= 400)				//	Si pasan 2ms.
				{
					Tick = 0;					//	Pongo el contador de ticks a 0.
					SetPin(1);				//	Pongo el pin a 1.
					OWESTADO	=	OWINICIO1;	//	Paso a la segunda fase de inicio.
				}
				else
				{
					SetPin(0);				//	Pongo el pin a 0.
				}
				break;
			case OWINICIO1:
				if	(Tick >= 16)				//	Si pasan 
			case	OWESPERANDO1:
				break;
			case	OWESPERANDO2:
				break;
		}
	}
};

void RIT_IRQHandler()
{
	COUNTERS->RITicks++;
}

void __configuraOW__(){}
	
void activaMedidaOW(){}
	
	
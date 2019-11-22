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
extern	misDatos_t	*	DATOS;
extern 	actualizador_t	*	ACTUALIZADOR;
uint8_t	sigInit	=	0;
uint8_t	OWEjecutameExterno = 0;
uint8_t	OWESTADO	=	OWDEEPSLEEP;

uint64_t  buffex	=	0;
uint32_t	Medidas	=	0;
uint8_t	ChecksumCalculado	=	0;

uint8_t	BitsTotal	=	0;
uint8_t   NumeroDeFallos	=	0;

	
void	StateChartOneWire(	uint32_t	DeltaCap	)
{
	int i;
	switch	(	OWESTADO	)
	{	
		case OWDEEPSLEEP:
			if (sigInit)					//	Si hay señal de inicio...
			{
				OWConfiguraSalida();		//	Configuro como salida.
				sigInit = 0;				//	Borro el flag de inicio.
				OWSetPin(0);				//	Pongo un 0. (Ya habrá un match que me llame para ponerlo a 1)
				OWESTADO	=	OWGENERA;		//	Paso a generar la señal de start.
			}
			break;
		
		case OWGENERA:
			OWSetPin(1);					//	Hago un pull a 1.
			OWConfiguraEntrada();			//	Ahora lo que viene entra.
			OWESTADO	=	OWESPERANDO;		//	Paso a esperar la secuencia.
			LPC_TIM1->MCR	&=	~(0x7 << 6);	//	Que el MR2 no interrumpa ni haga reset del contador.
			break;
			
		case	OWESPERANDO:
			OWESTADO	=	OWESPERANDO_SEQ;
			break;
		
		case OWESPERANDO_SEQ:
			if(	DeltaCap/Fclk	> 100e-6	&&	DeltaCap/Fclk	<	140e-6)
			{
				OWESTADO	=	OWESPERANDO_BIT;
			}
			else
			{
				ErrorRx();
			}
			break;
		
		case OWESPERANDO_BIT:
			if (	DeltaCap/Fclk	<	100e-6	)
			{
				buffex++;
			}
			buffex = buffex << 1;
			BitsTotal++;
			if ( BitsTotal >= 40 )
			{
				Medidas	=	buffex >> 8;
				BitsTotal = 0;
				OWESTADO	=	OWCHECKSUM;
			}
			break;
			
		case OWCHECKSUM:
			ChecksumCalculado = 0;									//	Inicio el checksum.
			Medidas = buffex >> 8;									//	Medidas de temperatura y humedad.
			for (i = 0; i<32; i++)									//	Durante 32 iteraciones haz:
			{	
				if (Medidas & (1 << i))								//	Si el bit i es 1...
				{
					ChecksumCalculado++;							//	Aumento el checksum.
				}
			}
			if (ChecksumCalculado != (buffex & (0xFF)))					//	Si no coincide el Checksum...
			{
				InvalidChecksum();									//	Checksum inválido.
			}
			else
			{
				OWESTADO	=	OWDEEPSLEEP;							//	A dormir.
				DATOS->Humedad		=	(Medidas >> 12) 		/ 10;	//	Parte de humedad.
				DATOS->Temperatura	=	(Medidas & (0xFFFF) ) 	/ 10;	//	Parte de temperatura.
				ACTUALIZADOR->TempRev	=	1;						//	Le digo al LCD que sí hay una temperatura válida.	
				LPC_RIT->RICTRL		&=	~(1 << 3);				//	Desactivo el RIT.
				NumeroDeFallos		=	0;							//	Reset al contador de fallos.
			}
			break;
			
	}
}

void OWSetPin(	uint8_t	Nivel)
{
	switch (Nivel)
	{
		case 0:
			LPC_GPIO1->FIOCLR	=	(1 << BITOW);		//	Poner a 0 el bit BITOW del puerto 2.
			break;
		case 1:
			LPC_GPIO1->FIOSET	=	(1 << BITOW);		//	Poner a 1 el bit BITOW del puerto 2.
			break;
	}
}

void OWConfiguraEntrada()
{
	LPC_PINCON->PINSEL3	&=	    ~(0x3 << (2*(BITOW - 16)));		//	Eint0.
	LPC_PINCON->PINSEL3	|=		(0x1 << (2*(BITOW - 16)));		//	Eint0.
}

void OWConfiguraSalida()
{
	LPC_PINCON->PINSEL3	&=	    ~(0x3 << (2*(BITOW - 16)));		//	Gpio.
	LPC_GPIO2->FIODIR	|=		1 << BITOW;					//	Salida.
}

void ErrorRx()
{
	//OWESTADO	=	OWINICIO;
}

void InvalidChecksum()
{
	NumeroDeFallos++;
	OWESTADO = OWINICIO;
	if (	LIMITE_FALLOS	>=	NumeroDeFallos)
	{
		ErrorRx();
	}
}

void mideTemperatura()
{
//	sigInit = 1;						//	Doy señal para iniciar la máquina de estados.
//	if (	OWESTADO == OWDEEPSLEEP )		//	Si está sin hacer nada...
//	{
//		StateChartOneWire(0);			//	Ejecútala.
//	}
//	ACTUALIZADOR->TempRev	=	0;		//	Le digo al LCD que no hay temperatura medida.
//	LPC_TIM1->MCR			=	(1 << 3*2) | (1 <  (3*2)+1);	//	Activo interrupción por MR2 y reset tras MR2.
//	LPC_TIM1->TCR			=	2;
//	LPC_TIM1->TCR			=	1;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraOW__()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraOW__()
{
	LPC_TIM1->MR2	=	(Fclk*0.002) -	1;	//	Interrumpe en 2ms.
	OWESTADO		=	OWDEEPSLEEP;		//	El estado pasa a ser deepsleep.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		mideTemperatura()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


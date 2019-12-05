/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		OneWire.c																		//
//		@version		2.01																			//
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


#define	US_AHORA		(LPC_TIM3->TC)
#define	PIN_OWp		19
#define	PIN_OW		(1	<<	19)
#define	CONFIG_OUT	(LPC_GPIO1->FIODIR |= PIN_OW)
#define	CONFIG_IN		(LPC_GPIO1->FIODIR &= ~(PIN_OW)) 
#define	CLEAR_PIN		(LPC_GPIO1->FIOCLR = PIN_OW)
#define	SET_PIN		(LPC_GPIO1->FIOSET = PIN_OW)
#define	ENTRADA		((LPC_GPIO1->FIOPIN >> PIN_OWp) & 1)

uint32_t reiniciaCuenta		(	void	);
void	inicializaT3			(	void	);
void _delayUS				(	uint16_t usegundos	);
uint8_t 	compruebaRespuesta	(	void	);
uint8_t	leerByte			(	void	);

extern misDatos_t *	DATOS;

/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraOW__()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraOW__()
{
	inicializaT3();
	reiniciaCuenta();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		mideTemperatura()																//
//																								//
//		@brief		Configura los pines y los recursos utilizados para el protocolo OneWire.					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	mideTemperatura	(	void	)
{
	int i;
	uint64_t Rx		=	0;
	uint8_t Checksum	=	0;
	/**	@state:	Estado en el que mandamos la señal de petición.	*/
	CONFIG_OUT;
	CLEAR_PIN;
	_delayUS(18000);
	CONFIG_IN;
	/**	@state:	Esperamos la respuesta.						*/
	if (	compruebaRespuesta()	)
	{
		//	ERROR A AL ESPERAR LA RESPUESTA DEL SENSOR...
		return;
	}
	/**	@state:	Leemos los 5 bytes...						*/
	for(i = 0; i < 5; i++)
	{
		Rx |= (leerByte() << i*8);
	}
	/**	@state:	Procesamos Rx.								*/
	for(i = 0; i < 32; i++)
	{
		if(	Rx & (1 << (i+8)))
		{
			Checksum ++;
		}
	}
	if( Checksum == (Rx & 0xFF) )
	{
		DATOS->Humedad 	= (float)((Rx >> 24) & 0xFF);
		DATOS->Temperatura 	= (float)((Rx >> 16) & 0xFF);
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		reiniciaCuenta()																//
//																								//
//		@brief		Reinicia el contador del timer 3.													//
//																								//
//		@ret			Retorna el valor de la cuenta antes de reiniciarla.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint32_t reiniciaCuenta()
{
	uint32_t retval = 	US_AHORA; 
	LPC_TIM3->TCR	=	2;	//	Reinicia timer.
	LPC_TIM3->TCR	=	1;	//	Activa cuentas.
	return retval;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		inicializaT3()																	//
//																								//
//		@brief		Configura el timer 3 para utilizarlo para el OneWire.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void inicializaT3()
{
	LPC_SC->PCONP	|=	(1	<<	23);	//	Activo el timer 3.
	LPC_TIM3->CTCR	=	0;			//	Contar por prescaler.
	LPC_TIM3->PR	=	24;			//	Cuentas cada 1us.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		_delayUS()																	//
//																								//
//		@brief		Espera activa de [ usegundos ] microsegundos.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	_delayUS(	uint16_t	usegundos	)
{
	reiniciaCuenta();
	while	(US_AHORA < usegundos) {}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		compruebaRespuesta()															//
//																								//
//		@brief		Comprueba si el sensor ha respondido apropiadamente.									//
//																								//
//		@ret			Retorna 0 si todo ha ido bien, 1 si no.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	compruebaRespuesta()
{
	uint32_t 	Tiempo = 0;
	/**	@state:	Esperamos que el sensor responda con un pull down...	*/
	reiniciaCuenta();
	while	(	ENTRADA	&&	US_AHORA < 45)			//	Si la entrada está a nivel alto y no han pasado 45 us...
	{
												//	Mantente en espera.
	}
	Tiempo = reiniciaCuenta();						//	Me quedo con cuentos us han pasado.
	if (	Tiempo < 5 || Tiempo > 45)					//	Si el márgen de pull down del sensor no es el adecuado.
	{
		return 1;									//	Exit error code.
	}
	/**	@state:	Esperamos la respuesta del sensor...				*/
	reiniciaCuenta();
	while	(	ENTRADA == 0	&&	US_AHORA < 100)	//	Tiempo nivel bajo...
	{
		
	}
	Tiempo = reiniciaCuenta();
	if (	Tiempo < 70 || Tiempo > 90)					//	Si el tiempo de pull down no es adecuado...
	{
		return 1;									//	Exit error code.
	}
	reiniciaCuenta();
	while	(	ENTRADA 		&&	US_AHORA < 100)	//	Tiempo nivel alto...
	{
		
	}
	Tiempo = reiniciaCuenta();
	if (	Tiempo < 70 || Tiempo > 90)					//	Si el tiempo de pull down no es adecuado...
	{
		return 1;									//	Exit error code.
	}
	return 0;										//	Respuesta correcta.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		leerByte()																	//
//																								//
//		@brief		Lee 8 bits en ráfaga del sensor.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	leerByte(	void	)
{
	int i;
	uint8_t Rx=0;
	uint32_t Tiempo = 0;
	for (i = 0; i < 8; i++)
	{
		reiniciaCuenta();
		while (	ENTRADA == 0	&&	US_AHORA < 100)		//	Mientras la entrada valga 0...
		{
													//	Mantenernos esperando.
		}
		Tiempo = reiniciaCuenta();
		if (Tiempo < 40 || Tiempo > 60)					//	Si el tiempo está fuera del margen.
		{
			return 0;									//	Error al leer el bit, retorna 0.
		}
		Tiempo = 0;
		reiniciaCuenta();
		while	(	ENTRADA	&&	US_AHORA	<	100)		//	Mientras la entrada valga 1...
		{
													//	Mantenernos esperando.
		}
		Tiempo = reiniciaCuenta();
		if (	Tiempo > 60 && Tiempo < 80)					//	Si entra en el márgen del 1...
		{
			Rx	|=	1 << i;							//	Añadimos un 1.
		}
		else
		{
			if ( Tiempo < 10 || Tiempo >  100)				//	Si se ha salido del márgen...
			{
				return 0;								//	Error al leer el bit, retorna 0.
			}
		}
		
	}
	return Rx;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

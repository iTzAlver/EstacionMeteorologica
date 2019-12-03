/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		I2C.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que recoge la comunicación por I2C.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes a la comunicación por I2C.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	I2C
#define	I2C
#include	"I2C.h"
#endif	
//	Variables globales y externas.
BMP_t	COEF			;
extern 	misDatos_t	*	DATOS;
uint8_t	TemperaturaConBmp	=	0;
uint8_t	LecturaBMP0	;
uint8_t	LecturaBMP1	;
uint16_t	LecturaBMP	;
float temperatura;
float presion;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraI2C__()																//
//																								//
//		@brief		Esta función es la que configura el protocolo I2C.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraI2C__	(	void	)
{
	__calibraBMP();
}
void __calibraBMP()
{
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	AC1	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.ac1	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.ac1	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	AC2	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.ac2	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.ac2	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	AC3	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.ac3	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.ac3	|=	I2CGetByte(	NACK	);	
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	AC4	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.ac4	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.ac4	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	B1	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.b1	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.b2	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	B2	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.b2	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.b2	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	MB	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.mb	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.mb	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	MC	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.mc	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.mc	|=	I2CGetByte(	NACK	);
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	MD	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	COEF.md	=	I2CGetByte(	SACK	)	<< 8;	
	COEF.md	|=	I2CGetByte(	NACK	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		procesarDato()																	//
//																								//
//		@brief		Procesa el dato guardado en la variable LecturaBMP.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	procesarDato	(	uint8_t	Tipo	)
{
	medirBMP();
	if (	Tipo	==	PRESION_BMP	)
	{
		DATOS->Presion		=	presion;		/**	@TODO:	Comprobar que el chino no me engaña.	*/
	}
	if (	Tipo	==	TEMPERATURA_BMP	)
	{
		DATOS->Temperatura	=	temperatura;		/**	@TODO:	Rellenar esta fórmula.	*/
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		pedirDatoReg()																	//
//																								//
//		@brief		Pide un dato al sensor I2C de 16 bits especificando el registro.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	pedirDatoReg	(	uint8_t	REG	)
{
	irRegistro(	REG	);
	pedirDato	();
	procesarDato(	PRESION_BMP	);
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		pedirDato()																	//
//																								//
//		@brief		Pide un dato al sensor I2C de 16 bits.												//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	pedirDato	(	void	)
{
	I2CSendAddr(	BMP_ADD	,	READ	)		;		//	Mandar la dirección en modo lectura.
	LecturaBMP0	=	I2CGetByte (	SACK	)	;		//	Leo el primer byte.
	LecturaBMP1	=	I2CGetByte (	NACK )	;		//	Leo el segundo byte.
	I2CSendStop()							;		//	Mando el fin de la comunicación.					
	LecturaBMP	=	(LecturaBMP0 << 8) | LecturaBMP1;	//	Todo al buffer de 16 bits.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		irRegistro()																	//
//																								//
//		@brief		Accede al registro REG de la memoria EPROM.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void irRegistro	(	uint8_t	REG	)	//	Acceso al registro REG del sensor.
{
	I2CSendAddr(	BMP_ADD	,	WRITE);	//	Selecciono BMP.
	I2CSendByte(		REG		);		//	Selecciono el registro de presión.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		bmp180_get_pressure()															//
//																								//
//		@brief		No hablo el mismo idioma que el creador del driver, pero parece que devuelve la presión.		//
//																								//
//		@ref			Extraido de https://github.com/BoschSensortec/BMP180_driver; referido por la datasheet.		//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint16_t obtenerDato	(	uint8_t	REG	)
{
	uint16_t	RETVAL;
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	REG	);
	I2CSendAddr(	BMP_ADD	,	READ	);
	RETVAL	=	I2CGetByte(	SACK	)	<< 8;	
	RETVAL	|=	I2CGetByte(	NACK	);
	return RETVAL;
}
void	mandaDato	(	uint8_t	REG	,	uint8_t	DATA)
{
	I2CSendAddr(	BMP_ADD	,	WRITE	);
	I2CSendByte(	REG	);
	I2CSendByte(	DATA	);
}

void medirBMP()
{
	int i;
	long	UT, UP , X1 , X2 , X3 , B3 , B5 , B6 , T , p;
	unsigned long B4, B7;
	mandaDato		(	0xF4	,	0x2E	);
	//Espera 4.7ms.
	for ( i = 0; i < 1000; i++)
	{
		I2Cdelay();
	}
	//Espera activa corta!
	UT = obtenerDato	(	0xF6);
	mandaDato		(	0xF4	,	0x34	);
	//Esperar 4.7ms.
		for ( i = 0; i < 1000; i++)
	{
		I2Cdelay();
	}
	//Espera activa corta!
	UP = obtenerDato	(	0xF6);
	X1 = ((UT - COEF.ac6) * COEF.ac5) >> 15;
	X2 = (COEF.mc << 11) / (X1 + COEF.md);
	B5 = X1 + X2;
	T  = ((B5 + 8) >> 4);
	
	B6 = B5 - 4000;
	X1 = (COEF.b2 * ((B6 * B6) >> 12)) >> 11;
	X2 = (COEF.ac2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = ((COEF.ac1 * 4 + X3) + 2) / 4;
	X1 = (COEF.ac3 * B6) >> 13;
	X2 = (COEF.b1 * ((B6 * B6) >> 12)) >> 16;
	X3 = (X1 + X2 + 2) >> 2;
	B4 = COEF.ac4 * (unsigned long)((X3 + 32768) >> 15);
	B7 = ((unsigned long)UP - B3)*(50000);
	
	if	(B7 < 0x80000000)
	{
		p = (B7*2) / B4;
	}
	else
	{
		p = (B7 / B4) * 2;
	}
	
	X1 = (p >> 8)*(p >> 8);
	X1 = (X1 * 3038 >> 16);
	X2 = (-7357 * p) >> 16;
	p = p + ((X1 + X2 + 3791) >> 4);
	temperatura 	= (float)T;
	presion		= (float)p;	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																															//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

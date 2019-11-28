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
extern 	misDatos_t	*	DATOS;
uint8_t	TemperaturaConBmp	=	0;
uint8_t	LecturaBMP0	;
uint8_t	LecturaBMP1	;
uint16_t	LecturaBMP	;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraI2C__()																//
//																								//
//		@brief		Esta función es la que configura el protocolo I2C.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraI2C__	(	void	)
{
	//	Creo que no hay que tocar nada...
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
	if (	Tipo	==	PRESION_BMP	)
	{
		DATOS->Presion	=	(float)bmp180_get_pressure( (uint32_t)LecturaBMP );	/**	@TODO:	Comprobar que el chino no me engaña.	*/
	}
	if (	Tipo	==	TEMPERATURA_BMP	)
	{
		DATOS->Temperatura;		/**	@TODO:	Rellenar esta fórmula.	*/
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
struct bmp180_t * p_bmp180;
int32_t bmp180_get_pressure(uint32_t v_uncomp_pressure_u32)
{
	int32_t v_pressure_s32, v_x1_s32, v_x2_s32,
	v_x3_s32, v_b3_s32, v_b6_s32 = 0;
	uint32_t v_b4_u32, v_b7_u32 = 0;

		v_b6_s32 = p_bmp180->param_b5 - 4000;
	/*****calculate B3************/
	v_x1_s32 = (v_b6_s32*v_b6_s32)
	>> 12;
	v_x1_s32 *= p_bmp180->calib_param.b2;
	v_x1_s32 >>= 11;

	v_x2_s32 = (p_bmp180->calib_param.ac2*v_b6_s32);
	v_x2_s32 >>= 11;

	v_x3_s32 = v_x1_s32 + v_x2_s32;
	v_b3_s32 = (((((int32_t)p_bmp180->calib_param.ac1)*4 + v_x3_s32) <<
	p_bmp180->oversamp_setting) + 2)
	>> 2;

	/*****calculate B4************/
	v_x1_s32 = (p_bmp180->calib_param.ac3 * v_b6_s32)
	>> 13;
	v_x2_s32 = (p_bmp180->calib_param.b1 *
	((v_b6_s32 * v_b6_s32) >> 12))
	>> 16;
	v_x3_s32 = ((v_x1_s32 + v_x2_s32) + 2)
	>> 2;
	v_b4_u32 = (p_bmp180->calib_param.ac4 * (uint32_t)
	(v_x3_s32 + 32768)) >> 15;

	v_b7_u32 = ((uint32_t)(v_uncomp_pressure_u32 - v_b3_s32) *
	(50000 >> p_bmp180->oversamp_setting));
	if (v_b7_u32 < 0x80000000) {
		if (v_b4_u32 != 0)
			v_pressure_s32 =
			(v_b7_u32
			<< 1) / v_b4_u32;
		 else
			return 0;
	} else {
		if (v_b4_u32 != 0)
			v_pressure_s32 = (v_b7_u32 / v_b4_u32)
			<< 1;
		else
			return 0;
	}

		v_x1_s32 = v_pressure_s32
		>> 8;
		v_x1_s32 *= v_x1_s32;
		v_x1_s32 =
		(v_x1_s32 * 3038)
		>> 16;
		v_x2_s32 = (v_pressure_s32 * -7357)
		>> 16;
		/*pressure in Pa*/
		v_pressure_s32 += (v_x1_s32 + v_x2_s32 + 3791)
		>> 4;
	return v_pressure_s32;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																															//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

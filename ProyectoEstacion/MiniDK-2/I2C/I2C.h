/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		I2C.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Esta es la cabecera que recoge la comunicación por I2C.								//
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
#ifndef	LPC17XX
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif

typedef struct 
{
	uint16_t ac1;
	uint16_t ac2;
	uint16_t ac3;
	int16_t  ac4;
	int16_t  ac5;
	int16_t  ac6;
	uint16_t b1;
	uint16_t b2;
	uint16_t mb;
	uint16_t mc;
	uint16_t md;
}BMP_t;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al protocolo I2C.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define 	SDA 0 				//	Pin 0
#define 	SCL 1 				//	Pin 1
#define	DELAYTOTAL	100		//	Ajustar.

#define	BMP_ADD			119		//	Cambia en función del sensor.
#define	REGISTRO_PRESION		0xF6		//	Acceso al registro de presión.
#define	REGISTRO_TEMPERATURA	0x

#define	READ				1
#define	WRITE			0
#define	SACK				0
#define	NACK				1
#define	PRESION_BMP		10
#define	TEMPERATURA_BMP	11

#define	AC1				0xAA
#define	AC2				0xAC
#define	AC3				0xAE
#define	AC4				0xB0
#define	AC5				0xB2
#define	AC6				0xB4
#define	B1				0xB6
#define	B2				0xB8
#define	MB				0xBA
#define	MC				0xBC
#define	MD				0xBE
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo I2C.		      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraI2C__	(	void	)		;
void	irRegistro		(	uint8_t	REG)	;
void	pedirDato			(	void	)		;
void pedirDatoReg		(	uint8_t	REG)	;
void __calibraBMP		(	void	)		;
int32_t calculaTemperatura(	void	)		;
int32_t calculaPresion	(	void	)		;
void	medirBMP			(	void	)		;
uint16_t obtenerDato	(	uint8_t	REG	);
void	mandaDato			(	uint8_t	REG	,	uint8_t	DATA);

void I2Cdelay		(	void	)			;
void I2CSendAddr	(	uint8_t	addr	,	uint8_t	rw	);
void	I2CSendByte	(	uint8_t	byte)	;
uint8_t I2CGetByte	(	uint8_t	ACK)		;
void I2CSendStop	(	void	)			;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

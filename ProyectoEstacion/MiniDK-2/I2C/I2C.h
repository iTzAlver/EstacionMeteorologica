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

/**	@REMARK:	Yo no he hecho esto, sólo lo he adaptado.	*/
#define	u8	uint8_t
#define	u16	uint16_t
#define	s8	int8_t
#define	s32	int32_t
#define	s16	int16_t

#define BMP180_WR_FUNC_PTR s8 (*bus_write)(u8, u8, u8 *, u8)

#define BMP180_RD_FUNC_PTR s8 (*bus_read)(u8, u8, u8 *, u8)

struct bmp180_calib_param_t {
	s16 ac1;/**<calibration ac1 data*/
	s16 ac2;/**<calibration ac2 data*/
	s16 ac3;/**<calibration ac3 data*/
	u16 ac4;/**<calibration ac4 data*/
	u16 ac5;/**<calibration ac5 data*/
	u16 ac6;/**<calibration ac6 data*/
	s16 b1;/**<calibration b1 data*/
	s16 b2;/**<calibration b2 data*/
	s16 mb;/**<calibration mb data*/
	s16 mc;/**<calibration mc data*/
	s16 md;/**<calibration md data*/
};
struct bmp180_t {
	struct bmp180_calib_param_t calib_param;/**<calibration data*/
	u8 mode;/**<power mode*/
	u8 chip_id; /**<chip id*/
	u8 ml_version;/**<ml version*/
	u8 al_version;/**<al version*/
	u8 dev_addr;/**<device address*/
	u8 sensortype;/**< sensor type*/

	s32 param_b5;/**<pram*/
	s32 number_of_samples;/**<sample calculation*/
	s16 oversamp_setting;/**<oversampling setting*/
	s16 sw_oversamp;/**<software oversampling*/

	BMP180_WR_FUNC_PTR;/**< bus write function pointer*/
	BMP180_RD_FUNC_PTR;/**< bus read function pointer*/
	void (*delay_msec)(uint32_t);/**< delay function pointer*/
};
/**	@ENDREMARK:	Yo no he hecho esto, sólo lo he adaptado.	*/
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al protocolo I2C.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define 	SDA 0 				//	Pin 0
#define 	SCL 1 				//	Pin 1
#define	DELAYTOTAL	100		//	Ajustar.

#define	BMP_ADD			119		//	Cambia en función del sensor.
#define	REGISTRO_PRESION	0xF6		//	Acceso al registro de presión.

#define	READ				1
#define	WRITE			0
#define	SACK				0
#define	NACK				1
#define	PRESION_BMP		10
#define	TEMPERATURA_BMP	11

/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo I2C.		      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraI2C__	(	void	)		;
void	irRegistro		(	uint8_t	REG)	;
void	pedirDato			(	void	)		;
void pedirDatoReg		(	uint8_t	REG)	;

void I2CDelay		(	void	)			;
void I2CSendAddr	(	uint8_t	addr	,	uint8_t	rw	);
void	I2CSendByte	(	uint8_t	byte)	;
uint8_t I2CGetByte	(	uint8_t	ACK)		;
void I2CSendStop	(	void	)			;

int32_t bmp180_get_pressure(	uint32_t	dato	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

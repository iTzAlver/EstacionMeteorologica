/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		OneWire.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para configurar el protocolo OneWire.										//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados para el protocolo OneWire.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los s�mbolos correspondientes al protocolo OneWire.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	SIZEOF_TRAMA			40		//	Tama�o del array como buffer de 8 bits.
#define	SIZEOF_SLOT			8		//	Los �ltimos 8 bits son el checksum.

#define	OW_RESET_BAJO			0.018	//	Tiempo a nivel bajo de la se�al de start. (MCU -> Sensor)
					/** @CHANGE: 0.04*/
#define	OW_RESET_ALTO			0.02		//	Tiempo a nivel anto de la se�al de start. (MCU -> Sensor)		
#define	OW_RESPUESTA_BAJO		0.08		//	Se�al respuesta del sensor a nivel bajo.
#define	OW_RESPUESTA_ALTO		0.08		//	Se�al respuesta del sensor a nivel alto.
					/** @CHANGE: 0.078*/
#define	OW_MANDADO0			0.076	//	Duraci�n del tiempo de un bit = 0.
#define	OW_MANDADO1			0.120	//	Duraci�n del tiempo de un bit = 1.

#define	PERMISO_DIFERENCIAL		-0.005	//	Error que le permito tener al sensor.
#define	PERMISO_PROPORCIONAL	0.005	//	Error que le permito tener al sensor.

#define	OW_PULL_UP			0x0		//	Funci�n de pull up.
#define	OW_PULL_DOWN			0x3		//	Funci�n de pull down.
#define	OW_CAPTURE_FUNC		0x3		//	Funci�n capture.
#define	OW_CTCR_MASCARA		0x0		//	Dejar TC contando.
#define	OW_CCR_MASCARA_EN		0x30		//	Activo por flanco de bajada.
#define	OW_CCR_MASCARA_DIS		0x20		//	Desactivo por flanco.
#define	CAP11_IR				0x20		//	El IR de CAP1.1
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo OneWire.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraOW__(	void	);	//	Configuraci�n del protocolo OneWire.
void	mideTemperatura(	void	);	//	C�digo de medici�n de temperatura.
void	activaMedidaOW	(	void	);	//	Lanza el activador del one wire.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

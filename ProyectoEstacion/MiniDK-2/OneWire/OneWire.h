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
//		@private		Estos son los símbolos correspondientes al protocolo OneWire.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	SIZEOF_TRAMA			30		//	Tamaño del array como buffer de 8 bits.

#define	OW_RESET_BAJO			0.018	//	Tiempo a nivel bajo de la señal de start. (MCU -> Sensor)
					/** @CHANGE: 0.04*/
#define	OW_RESET_ALTO			0.02		//	Tiempo a nivel anto de la señal de start. (MCU -> Sensor)		
#define	OW_RESPUESTA_BAJO		0.08		//	Señal respuesta del sensor a nivel bajo.
#define	OW_RESPUESTA_ALTO		0.08		//	Señal respuesta del sensor a nivel alto.
					/** @CHANGE: 0.078*/
#define	OW_MANDADO0			0.076	//	Duración del tiempo de un bit = 0.
#define	OW_MANDADO1			0.120	//	Duración del tiempo de un bit = 1.

#define	PERMISO_DIFERENCIAL		-0.005	//	Error que le permito tener al sensor.
#define	PERMISO_PROPORCIONAL	0.005	//	Error que le permito tener al sensor.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al protocolo OneWire.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraOW__(	void	);	//	Configuración del protocolo OneWire.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
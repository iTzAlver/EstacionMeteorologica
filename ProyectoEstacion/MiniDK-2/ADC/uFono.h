/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		uFono.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para configurar el audio del micr�fono.										//
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
//		@include		Estos son los archivos utilizados para el audio del micr�fono.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
#ifndef	LPC17XX
#define	LPC17XX
#include	"LPC17XX.H"
#endif
#ifndef	TIMERS
#define	TIMERS
#include	"Timers.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los s�mbolos correspondientes al audio del micr�fono.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	FUNC_ADC		0x1
#define	PIN_UFONO		(23-16)
#define	CANAL_ADC_UF	0x1
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al audio del micr�fono.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraUFONO__	(	void	);	//	Configuramos el micr�fono.
void	lanzaUFONO		(	void	);	//	Lanzamos la carga de audio.
void recuperaContexto	(	void	);	//	Recupera el ADC para lanzar las muestras.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

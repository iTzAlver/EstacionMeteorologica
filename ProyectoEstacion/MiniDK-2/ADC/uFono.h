/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		uFono.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera para configurar el audio del micrófono.										//
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
//		@include		Estos son los archivos utilizados para el audio del micrófono.							//
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
//		@private		Estos son los símbolos correspondientes al audio del micrófono.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef		Estas son las funciones correspondientes al audio del micrófono.	      					//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraUFONO__	(	void	);	//	Configuramos el micrófono.
void	lanzaUFONO		(	void	);	//	Lanzamos la carga de audio.
void recuperaContexto	(	void	);	//	Recupera el ADC para lanzar las muestras.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

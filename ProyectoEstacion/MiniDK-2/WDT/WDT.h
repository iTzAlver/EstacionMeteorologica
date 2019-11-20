/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		WDT.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera del configurado del WDT.													//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código del WDT.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al WDT.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define	WATCHDOG_TIMEOUT	10			//	En segundos.
#define	Fwdt				Fclk/(float)4	//	Reloj seleccionado del WDT.
#define	WDMOD_MASK		0x03			//	Se activa y resetea el programa tras el timeout.
#define	WDCLKSEL_MASK		0x01			//	Se ha escogido el reloj Fclk.
#define	WDT_CODIGO1		0xAA			//	Primer código del WDT.
#define	WDT_CODIGO2		0x55			//	Segundo código del WDT.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef	Estas son las funciones que se usan en el WDT.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraWDT__	(	void	);
void alimentaWDT		(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

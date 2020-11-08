/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		WDT.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente del configurado del WDT.												//
//																								//
//		@category		Interno.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados con el código del WDT.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	WDT
#define	WDT
#include	"WDT.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function	__configuraWDT__()																	//
//																								//
//		@brief	Función que configura el WDT como un contador que observa si se ha bloqueado el programa.			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	__configuraWDT__()
{
	LPC_WDT->WDTC		=	Fwdt*WATCHDOG_TIMEOUT	;	//	Timeout de WATCHDOG_TIMEOUT segundos.
	LPC_WDT->WDCLKSEL	=	WDCLKSEL_MASK			;	//	Se selecciona el reloj que se desea para el WDT.	
	LPC_WDT->WDMOD		=	WDMOD_MASK			;	//	Se selecciona la acción a realizar si WDT llega a cero.
	alimentaWDT();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function	alimentaWDT()																		//
//																								//
//		@brief	Función que evita que el contador del WatchDogTimer llegue a 0.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	alimentaWDT()
{
	LPC_WDT->WDFEED	=	WDT_CODIGO1;
	LPC_WDT->WDFEED	=	WDT_CODIGO2;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DMA.h																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera del configurado del DMA.													//
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
//		@include		Estos son los archivos utilizados con el código del DMA.								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include	"Systemsymbols.h"
#endif
#ifndef	LDR
#define	LDR
#include	"LDR.h"
#endif
#ifndef	LUT
#define	LUT
#include	"LUT.h"
#endif
#include <LPC17xx.H>                               
#include <math.h>
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@private		Estos son los símbolos correspondientes al DMA.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#define 	N_samples_wave      32  // Nº de muestras por ciclo
#define	Ftono			400
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcdef	Estas son las funciones que se usan en el DMA.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraDMA__	(	void	);	//	Configurador del DMA.
void __configuraTono__	(	void	);	//	Configurador del tono.
void __configuraAudio__	(	void	);	//	Configurador del audio.
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

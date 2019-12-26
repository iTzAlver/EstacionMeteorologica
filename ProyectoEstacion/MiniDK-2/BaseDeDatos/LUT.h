/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LUT.g																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa donde se encuentra la cabecera de LUT.c								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@private																		//
//					@funcdef																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del anemómetro.										//
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
#ifndef	DMA
#define	DMA
#include	"DMA.h"
#endif
#ifndef	MATH
#define	MATH
#include	<math.h>
#endif

#define	BRILLO_LDR		0
#define	BRILLO2CICLO_LDR	1
#define	INDICE_UVA		2
#define	BRILLO_LDR_NOLUT	3

void goto_LUT(	float dato , uint8_t LUTn , float * ret_f , uint8_t * ret_8 , uint16_t * ret_16 , uint32_t * ret_32);
void crearSeno(	void	);
void ponTonoDMA(	void	);
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

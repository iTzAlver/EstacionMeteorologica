/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DMA.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que contiene el código fuente del DMA.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del anemómetro.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	DMA
#define	DMA
#include	"DMA.h"
#endif

LinkedModeDMA_t		LMDobj;
LinkedModeDMA_t	*	LMD	=	&LMDobj;
extern uint8_t	*	AUDIO;

void __configuraDMA__()
{
	LPC_SC->PCONP 			|= 	(1<<29);		//	Enciendo el DMA.
	LPC_GPDMA->DMACConfig 	= 	1;			//	Enciendo el controlador.
	LPC_GPDMA->DMACSync   	= 	(1<<6);		//	Sincronizo todos los registros.
	LPC_GPDMACH0->DMACCSrcAddr	=	LMD->Origen	=	(uint32_t)AUDIO;				//	Origen de la muestra.
	LPC_GPDMACH0->DMACCDestAddr	=	LMD->Destino	=	(uint32_t)((&LPC_DAC->DACR) + 8);	//	Destino de la muestra.
	LPC_GPDMACH0->DMACCLLI		=	LMD->Linked	=	(uint32_t)LMD;					//	Linkado a LMD.
	
	LMD->CR					=	LPC_GPDMACH0->DMACCControl	=	
							MUESTRAS_AUDIO			//	El número de muestras del audio.
							|	(0	<<	18)		//	Tamaño de 8 bits. (Tx)
							|	(0	<<	21)		//	Tamaño de 8 bits. (Rx)
							|	(1	<<	26)		//	Incremento origen.
							|	(0	<<	27);		//	No incremento destino.
	
	LPC_GPDMACH0->DMACCConfig	=	(0	<<	0)		//	EMPIEZA DESACTIVADO el canal.
							|	(0	<<	1)		//	Periférico origen. (Memoria)
							|	(7	<<	6)		//	Periférico destino. (DAC)
							|	(1	<<	11);		//	Tipo de flujo. (Mem-Perif)	
}











/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

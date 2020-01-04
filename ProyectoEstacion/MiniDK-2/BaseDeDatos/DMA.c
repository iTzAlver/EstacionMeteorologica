/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DMA.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa que contiene el c�digo fuente del DMA.								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al m�dulo del anem�metro.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	DMA
#define	DMA
#include	"DMA.h"
#endif

LinkedModeDMA_t		LMDobj;
LinkedModeDMA_t	*	LMD	=	&LMDobj;

void __configuraDMA__()
{
	LPC_SC->PCONP 			|= 	(1<<29);		//	Enciendo el DMA.
	LPC_GPDMA->DMACConfig 	= 	1;			//	Enciendo el controlador.
	LPC_GPDMA->DMACSync   	= 	(1<<6);		//	Sincronizo todos los registros.
	//ponAudioDMA();							//	Origen de la muestra.
	ponTonoDMA();							//	Origen de la muestra.
	LMD->Destino	=	(uint32_t)((&LPC_DAC->DACR) + 2);	//	Destino de la muestra.
	LMD->Linked	=	(uint32_t)LMD;					//	Linkado a LMD.
	LPC_GPDMACH0->DMACCDestAddr		=	(uint32_t)((&LPC_DAC->DACR) + 8);	//	Destino de la muestra.
	LPC_GPDMACH0->DMACCLLI			=	(uint32_t)LMD;					//	Linkado a LMD.
	
	LPC_GPDMACH0->DMACCControl	=	
							MUESTRAS_SENO			//	El n�mero de muestras del audio.
							|	(0	<<	18)		//	Tama�o de 8 bits. (Tx)
							|	(0	<<	21)		//	Tama�o de 8 bits. (Rx)
							|	(1	<<	26)		//	Incremento origen.
							|	(0	<<	27);		//	No incremento destino.
	
	LMD->CR					=	
							MUESTRAS_SENO			//	El n�mero de muestras del audio.
							|	(0	<<	18)		//	Tama�o de 8 bits. (Tx)
							|	(0	<<	21)		//	Tama�o de 8 bits. (Rx)
							|	(1	<<	26)		//	Incremento origen.
							|	(0	<<	27);		//	No incremento destino.	
	
	LPC_GPDMACH0->DMACCConfig	=	(1	<<	0)		//	EMPIEZA DESACTIVADO el canal.
							|	(0	<<	1)		//	Perif�rico origen. (Memoria)
							|	(7	<<	6)		//	Perif�rico destino. (DAC)
							|	(1	<<	11);		//	Tipo de flujo. (Mem-Perif)	
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

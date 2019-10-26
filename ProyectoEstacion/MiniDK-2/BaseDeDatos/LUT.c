/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		LUT.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa donde se encuentran las look up tables que optimizan					//
//					el uso de cpu sacrificando memoria, pero como uso una SD la memoria no es					//
//					un problema grande.																//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@LUT																			//
//					@function																		//
//					@end																			//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del anemómetro.										//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	LUT
#define	LUT
#include	"LUT.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@LUT			LookUpTables																	//
//																								//
//		@brief		Bases de datos.																//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	Brillo_LCR[] =
{
	13	,	20	,	25	,	30	,	35	,	40	,	45	,	50	,	55	,	60	,
	65	,	70	,	75	,	80
};
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		goto_LUT()																	//
//																								//
//		@brief		Esta función es la que mira las LUT y obtiene el dato que queremos de la base				//
//					de datos.																		//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void goto_LUT( float variable , uint8_t LUTn , float * ret_flotante , uint8_t * ret_int8 , uint16_t * ret_int16 , uint32_t * ret_int32)
{
	switch( LUTn )
	{
		case BRILLO_LCR:
			*ret_int8 = Brillo_LCR[(uint8_t)(variable/Brillo_LCR[0]) + 1];
			break;
		default:
			break;
	}
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

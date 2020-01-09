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
//					@variables																	//
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
//		@variables		Variables del fichero.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	PREGRABADA[MUESTRAS_SENO];
extern	uint8_t	*	AUDIO;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@LUT			LookUpTables																	//
//																								//
//		@brief		Bases de datos.																//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
uint8_t	Brillo2ciclo_LDR[] =
{
	13	,	20	,	25	,	30	,	35	,	40	,	45	,	50	,	55	,	60	,
	65	,	70	,	75	,	80														
																					};
uint8_t	Brillo_LDR[]	=
{
	21	,	1	,	5	,	10	,	15	,	20	,	25	,	30	,	35	,	40	,
	45	,	50	,	65	,	60	,	65	,	70	,	75	,	80	,	85	,	90	,
	95	,	100
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
		case BRILLO_LDR:
			*ret_flotante = Brillo_LDR[		(uint8_t)(((variable - LDRRESISTENCIA_MIN)	/(LDRRESISTENCIA_MAX - LDRRESISTENCIA_MIN))	*Brillo_LDR[0]) + 1];
			break;
		case	BRILLO2CICLO_LDR:
			*ret_int8	= Brillo2ciclo_LDR[		(uint8_t)(((variable - BRILLO_MIN)			/(BRILLO_MAX - BRILLO_MIN))				*Brillo2ciclo_LDR[0]) + 1];
			break;
		case	INDICE_UVA:
			*ret_flotante = variable;	//	El output DC corresponde al índice, es muy sencillo traducirlo, se recomienda no llamar a esta función en este modo.
			break;
		case BRILLO_LDR_NOLUT:
			*ret_flotante = -(1.0102)*variable + 102.0204;
			if (*ret_flotante < 0)
			{
				*ret_flotante = 0;
			}
		default:
			break;
	}
}
//**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

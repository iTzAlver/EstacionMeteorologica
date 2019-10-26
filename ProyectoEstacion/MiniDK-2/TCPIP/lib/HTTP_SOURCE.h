/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		HTTP_SOURCE.h																	//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Cabecera que configura la página WEB.												//
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
//		@include		Estos son los archivos utilizados en el código de configuración.							//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	NETCONFIG
#define	NETCONFIG
#include	<Net_Config.h>
#endif
#ifndef	STDIO
#define	STDIO
#include	<stdio.h>
#endif
#ifndef	LPC17XX
#define	LPC17XX
#include <LPC17XX.H>
#endif
#ifndef RTL
#define RTL
#include <RTL.h>
#endif

void 	__configuraWEB__	(	void	);
void		__mantenerTCP__	(	void	);


/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/


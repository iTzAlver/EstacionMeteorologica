/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		PWM.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el programa donde están definidas las funciones a utilizar en el módulo				//
//					PWM dedicado al proyecto de Sistemas electrónicos digitales avanzados (UAH - EPS).			//
//																								//
//																								//
//		@category		Opcional.																		//
//																								//
//		@map			@include																		//
//					@variables																	//
//					@function																		//
//					@end																			//
//																								//
//		|---|	|		|	|\	 /|																//
//		|   |	 |	    | 	| \  / |																//
//		|---|	  |	   |		|  \/  |																//
//		|		   |	| |		|	  |																//
//		|		    | |		|	  |																//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Includes pertenecientes al módulo del PWM.											//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	PWM
#define	PWM
#include "PWM.h"
#endif
#ifndef	SYSTEMSYMBOLS
#define	SYSTEMSYMBOLS
#include 	"Systemsymbols.h"
#endif
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@variables		Variables del fichero.														//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
extern Counters_t	*	COUNTERS;
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		__configuraPWM__()																//
//																								//
//		@brief		Configura el PWM en función de la frecuencia a utilizar y que PWM se quieren usar.			//
//					El primer byte activa las del puerto 2 y las del segundo las del otro puerto en orden		//
//					ascendente.																	//
//																								//
//			@FrecuenciaPWM		Frecuencia a la que se desea ajustar el ciclo PWM. En Hz.						//
//			@CualesPWM		Máscara que define los PWM a configurar, los 6 primeros bits corresponden al		//
//							puerto 2. Del 9º bit al 14º bit corresponden al puerto 1. En orden ascendente		//
//							desde del PWM1.1 al PWM1.6												//
//																								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraPWM__(	float	FrecuenciaPWM	,	uint16_t	CualesPWM	)
{
	LPC_SC->PCONP 		|= 	PCONP_MASK;								// Enciendo el PWM.
	LPC_PWM1->MR0 		= 	((uint32_t)(Ftick/FrecuenciaPWM) - 1);			// Configuro la frecuencia.
	LPC_PWM1->TCR 		|= 	TCR_MASK;									// Activo el PWM.
	LPC_PWM1->MCR 		&=	~TODO_1_32;								// Reset al MCR.
	LPC_PWM1->MCR       |=   0x2;										// Ahora el MR0 resetea el contador.
	LPC_PINCON->PINSEL4 &= 	~0xFFF;									// Reset en pines PWM puerto 2.
	LPC_PINCON->PINSEL3 &=	~0x33CF30;								// Reset en pines PWM puerto 1.
	
	for (COUNTERS->i = 0; COUNTERS->i < 6; (COUNTERS->i)++)				// Para el puerto 2: seleccionados.
	{
		if (	(CualesPWM >> COUNTERS->i) & ~0xFFFE)						// Miro si está seleccionado el iésimo.
		{
			LPC_PINCON->PINSEL4 	|= (FUNC1 	<< (2*COUNTERS->i));	// Pongo la función 1 en los pines PWM.
			LPC_PWM1->PCR |= (0x1 << (COUNTERS->i + 0x9));				// Pongo la función de enable output en el PWM.
		}
	}
	/**	@REMARK:	Esto se configuraría como open drain sobre todo por no perder potencia, pero prefiero aseugrar con pull.*/
	for (COUNTERS->i = 6; COUNTERS->i < 12; (COUNTERS->i)++)				// Para el otro puerto: seleccionados.
	{
		if (	(CualesPWM >> (COUNTERS->i + 2)) & ~0xFFFE)						// Miro si está seleccionado el iésimo.
		{
			LPC_PWM1->PCR |= (0x1 << (COUNTERS->i - 0x6 + 0x9));			// Pongo la función de enable output en el PWM.
			switch (COUNTERS->i)									// Pongo la función 2 en los pines PWM.
			{
				case 6:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*2;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*2;
					break;
				case 7:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*4;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*4;
					break;
				case 8:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*5;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*5;
					break;
				case 9:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*7;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*7;
					break;
				case 10:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*8;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*8;
					break;
				case 11:
					LPC_PINCON->PINSEL3 	|=	FUNC2 <<	2*10;
//					LPC_PINCON->PINMODE3 	|=	OPEN_DRAIN <<	2*8;
					break;
				default:
					break;
			}
		}
	}
	COUNTERS->i = 0;												// Dejo el contador a 0.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@function		modificaPulso()																//
//																								//
//		@brief		Configura el  pulso de PWM en función del ciclo de trabajo o de valores de oscilación		//
//					si se encuentra en modo servo.													//
//																								//
//				@PWMn	Selecciona el PWM1.n a modificar.												//
//				@Modo	Selecciona si modo servo (valores)o modo ciclo (en porcentaje).						//
//				@Ciclo	Selecciona el ciclo de trabajo para el modo ciclo.								//
//				@Grados	Selecciona los grados a rotar el servo en modo servo.								//
//				@Minimo	Selecciona el mínimo valor de Ton del ciclo PWM. En segundos.						//
//				@Maximo	Selecciona el máximo valor de Ton del ciclo PWM. En segundos.						//
//																								//
//																								//
//																								//
//																								//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void	modificaPulso(	uint32_t	PWMn	,	uint8_t Modo	,	uint8_t Ciclo	,	uint8_t	Grados,	float Minimo	,	float	Maximo	)
{
	if (PWMn > 3)
	{
		PWMn += 6;	//	Debido a la asimétrica distribución de los registros.
	}
	
	Minimo *= KMN;			//	Definitivamente había algo mal.
	Maximo *= KMX;			//	Estos servos utilizan la potencia del pulso y no precisamente su duración.
	
	/**	@REMARK:	La potencia entregada no es la debida. En la datasheet especifica pulsos del rango de 5V, se ofrece uno
				de 3.3V, se ha podido usar un transistor, pero deduzco que estos servos utilizan la potencia de la señal
				PWM para obtener el ángulo y modificando los tiempos podemos entregar más potencia de señal.*/
	
	switch(	Modo	)
	{
		case MODO_CICLO:	// Escribo en LPC_PWM1->MRn el valor correspondiente al porcentaje de MR0; < 1.
			*(__IO uint32_t *)((uint32_t)&(LPC_PWM1->MR0) + (uint32_t)(0x4*PWMn)) = (uint32_t)((float)(LPC_PWM1->MR0)*((float)Ciclo/(float)100));
			break;
		case MODO_SERVO:	// Escribo en LPC_PWM1->MRn el valor correspondiente al tiempo Ton en función del grado.
			*(__IO uint32_t *)((uint32_t)&(LPC_PWM1->MR0) + (uint32_t)(0x4*PWMn)) = (uint32_t)((Ftick*(Minimo + (Maximo - Minimo)*(float)(Grados/(float)(180)))- (float)1));			
			break;
		default:
			break;
	}
		if (PWMn > 3)
	{
		PWMn -= 6;	//	Devolvemos PWMn a su estado oriegen.
	}
	LPC_PWM1->LER |= 0x1 << PWMn | 0x1;		// Activo el load de los MR0 y MRn.
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

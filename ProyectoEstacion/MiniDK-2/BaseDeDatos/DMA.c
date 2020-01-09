/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		DMA.c																		//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Código fuente que contiene las funciones para audio (DMA).								//
//																								//
//		@category		Periférico.																	//
//																								//
//		@map			@include																		//
//					@funcion																		//
//					@end																			//
//																								//
//																								//
//----------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@include		Estos son los archivos utilizados en el código de LDR.									//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	DMA
#define	DMA
#include	"DMA.h"
#endif
extern actualizador_t	*	ACTUALIZADOR;
extern uint8_t	AUDIO[MUESTRAS_AUDIO];
DMA_t	LLI0;
uint8_t sinusoide[N_samples_wave];
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraDMA__()																//
//																								//
//		@brief		Función de configuración del DMA.													//
//																								//
//		@REMARK:		Para activar un periodo del DAC (2 segundos)											//													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraDMA__ (void)
{
	int i;
	for(i=0; i < N_samples_wave; i++)
	{
		sinusoide[i] = (int)(127 + 127*sin(2*PI*i/N_samples_wave)); // DACR bit 6-15 VALUE (valor ya desplazado!!!)
	}		
	LPC_PINCON->PINSEL1 |= (2<<20);							// enable AOUT (P0.26) pin
	__configuraTono__();
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraTono__()																//
//																								//
//		@brief		Función de configuración del tono.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraTono__()
{	
    // Linked CH0 
	LLI0.source      = (uint32_t) &sinusoide[0];
	LLI0.destination = (uint32_t) &(LPC_DAC->DACR);
	LLI0.next        = (uint32_t) &LLI0;
	LLI0.control     = 1<<26 | 2<<21 | 2<<18 | N_samples_wave; //Transfersize=  WAVE_SAMPLE_NUM, SWidth=32bits, DWidth=32bits, Source Increment
	
	
	
	LPC_SC->PCONP 	|= (1<<29);											// Power DMA
	LPC_GPDMA->DMACConfig = 1;                  		// enable the GPDMA controller
	LPC_GPDMA->DMACSync   = (1<<6);			       			// enable synchro logic for all reqs

	LPC_GPDMACH0->DMACCSrcAddr  = (uint32_t) &sinusoide[0];
	LPC_GPDMACH0->DMACCDestAddr = (uint32_t) &(LPC_DAC->DACR) + 2;
	LPC_GPDMACH0->DMACCLLI      = (uint32_t) &LLI0; // linked lists for ch0
	LPC_GPDMACH0->DMACCControl  = N_samples_wave   // transfer size (0 - 11) = 32 muestras /ciclo
                            | (0 << 12)            	// source burst size (12 - 14) = 1
                            | (0 << 15)            	// destination burst size (15 - 17) = 1
                            | (0 << 18)            	// source width (18 - 20) = 32 bit					CAMBIADO
                            | (0 << 21)            	// destination width (21 - 23) = 32 bit				NO CAMBIADO
                            | (0 << 24)            	// source AHB select (24) = AHB 0
                            | (0 << 25)            	// destination AHB select (25) = AHB 0
                            | (1 << 26)            	// source increment (26) = increment
                            | (0 << 27)            	// destination increment (27) = no increment
                            | (0 << 28)            	// mode select (28) = access in user mode
                            | (0 << 29)            	// (29) = access not bufferable
                            | (0 << 30)            	// (30) = access not cacheable
                            | (0 << 31);           	// terminal count interrupt disabled
	LPC_GPDMACH0->DMACCConfig   =  0   							// channel enabled (0)
			   | (0 << 1) 							// source peripheral (1 - 5) = none
			   | (7 << 6) 							// destination peripheral (6 - 10) = DAC
			   | (1 << 11)							// flow control (11 - 13) = MEM to PERF
			   | (0 << 14)							// (14) = mask out error interrupt
			   | (0 << 15)							// (15) = mask out terminal count interrupt
			   | (0 << 16)							// (16) = no locked transfers
			   | (0 << 18);						// (27) = no HALT

	//F_out (salida del DAC)
	LPC_DAC->DACCNTVAL = Fclk/N_samples_wave/Ftono -1;  // (Ts DAC = F_out/N_samples  < Tsetup DAC = 1useg. !!!!)
	
	/* DMA, timer running, dbuff */
	LPC_DAC->DACCTRL   = 1<<3 | 1<<2 | 1<<1;           
	ACTUALIZADOR->Audiorev = 1;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																														//
//		@funcion		__configuraAudio__()																//
//																								//
//		@brief		Función de configuración del audio.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
void __configuraAudio__()
{
	LPC_PINCON->PINSEL1 |= (2<<20);							// enable AOUT (P0.26) pin
	
	
    // Linked CH0 
	LLI0.source      = (uint32_t) &sinusoide[0];
	LLI0.destination = (uint32_t) &(LPC_DAC->DACR);
	LLI0.next        = (uint32_t) &LLI0;
	LLI0.control     = 1<<26 | 2<<21 | 2<<18 | N_samples_wave; //Transfersize=  WAVE_SAMPLE_NUM, SWidth=32bits, DWidth=32bits, Source Increment
	
	
	
	LPC_SC->PCONP 	|= (1<<29);											// Power DMA
	LPC_GPDMA->DMACConfig = 1;                  		// enable the GPDMA controller
	LPC_GPDMA->DMACSync   = (1<<6);			       			// enable synchro logic for all reqs

	LPC_GPDMACH0->DMACCSrcAddr  = (uint32_t) AUDIO;
	LPC_GPDMACH0->DMACCDestAddr = (uint32_t) &(LPC_DAC->DACR) + 2;
	LPC_GPDMACH0->DMACCLLI      = (uint32_t) &LLI0; // linked lists for ch0
	LPC_GPDMACH0->DMACCControl  = MUESTRAS_AUDIO   // transfer size (0 - 11) = 32 muestras /ciclo
                            | (0 << 12)            	// source burst size (12 - 14) = 1
                            | (0 << 15)            	// destination burst size (15 - 17) = 1
                            | (0 << 18)            	// source width (18 - 20) = 32 bit
                            | (2 << 21)            	// destination width (21 - 23) = 32 bit
                            | (0 << 24)            	// source AHB select (24) = AHB 0
                            | (0 << 25)            	// destination AHB select (25) = AHB 0
                            | (1 << 26)            	// source increment (26) = increment
                            | (0 << 27)            	// destination increment (27) = no increment
                            | (0 << 28)            	// mode select (28) = access in user mode
                            | (0 << 29)            	// (29) = access not bufferable
                            | (0 << 30)            	// (30) = access not cacheable
                            | (0 << 31);           	// terminal count interrupt disabled
	LPC_GPDMACH0->DMACCConfig   =  0   							// channel enabled (0)
			   | (0 << 1) 							// source peripheral (1 - 5) = none
			   | (7 << 6) 							// destination peripheral (6 - 10) = DAC
			   | (1 << 11)							// flow control (11 - 13) = MEM to PERF
			   | (0 << 14)							// (14) = mask out error interrupt
			   | (0 << 15)							// (15) = mask out terminal count interrupt
			   | (0 << 16)							// (16) = no locked transfers
			   | (0 << 18);						// (27) = no HALT

	//F_out (salida del DAC)
	LPC_DAC->DACCNTVAL = (Fclk/MUESTRAS_AUDIO/8000) - 1;  // (Ts DAC = F_out/N_samples  < Tsetup DAC = 1useg. !!!!)
	
	/* DMA, timer running, dbuff */
	LPC_DAC->DACCTRL   = 1<<3 | 1<<2 | 1<<1;           
	ACTUALIZADOR->Audiorev = 1;
}
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

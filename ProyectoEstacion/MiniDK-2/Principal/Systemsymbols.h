/**---------------------------------------------------------------------------------------------------------------------//
//		@filename		Systemsymbols.h																//
//		@version		0.00																			//
//		@author		Alberto Palomo Alonso															//
//																								//
//		@brief		Este es el archivo donde son guardados los símbolos del sistema utilizados para los			//
//					diferentes archivos que necesiten una llamada a este tipo de definiciones.					//
//																								//
//		@category		Esencial.																		//
//																								//
//		@map			@none																		//
//					@types																		//
//					@end																			//
//---------------------------------------------------------------------------------------------------------------------**/
#ifndef	LPC17XX
#define	LPC17XX
#include 	"LPC17XX.H"
#endif
//	Acopladores de código.
#ifndef 		null
#define		null				0
#endif
#ifndef		NULL
#define		NULL				0
#endif
#define		none				0
#define		NONE				0
#define		VOID				void
//	Símbolos prácticos de valores instantáneos.
#define		TODO_1_8			0xFFFF
#define		TODO_1_16			0xFFFFFFFF
#define		TODO_1_32			0xFFFFFFFFFFFFFFFF
//	Símbolos correspondientes a definiciones propias para facilitar lectura de código.
#define		SUBIDA				1
#define		BAJADA				0
#define		ALTO					1
#define		BAJO					0
#define		FLANCO				1
#define		NIVEL				0
#define		INICIALMENTE_ACTIVO 	1
#define		INICIALMENTE_INACTIVO	0
#define		FUNC0				0x0
#define		FUNC1				0x1
#define		FUNC2				0x2
#define		FUNC3				0x3
#define 		NOPIN 				0x00000000
#define 		PIN_00				0x00000001
#define 		PIN_01 				0x00000002
#define 		PIN_02 				0x00000004
#define 		PIN_03 				0x00000008
#define 		PIN_04 				0x00000010
#define 		PIN_05 				0x00000020
#define 		PIN_06 				0x00000040
#define 		PIN_07 				0x00000080
#define 		PIN_08 				0x00000100
#define 		PIN_09 				0x00000200
#define 		PIN_10 				0x00000400
#define 		PIN_11 				0x00000800
#define 		PIN_12 				0x00001000
#define 		PIN_13 				0x00002000
#define 		PIN_14 				0x00004000
#define 		PIN_15 				0x00008000
#define 		PIN_16 				0x00010000
#define 		PIN_17 				0x00020000
#define 		PIN_18 				0x00040000
#define 		PIN_19 				0x00080000
#define 		PIN_20 				0x00100000
#define 		PIN_21 				0x00200000
#define 		PIN_22 				0x00400000
#define 		PIN_23 				0x00800000
#define 		PIN_24 				0x01000000
#define 		PIN_25 				0x02000000
#define 		PIN_26 				0x04000000
#define 		PIN_27 				0x08000000
#define 		PIN_28 				0x10000000
#define 		PIN_29 				0x20000000
#define 		PIN_30 				0x40000000
#define 		PIN_31 				0x80000000
//	Símbolos correspondientes a relojes del sistema.
#define		Fcpu				100000000						//	100MHz velocidad de la cpu.
#define		APBvalue			4							//	Valor del primer prescaler, 4 afer-reset.
#define		Prescaler			0							//	Valor del prescaler, 0 after-reset.
#define		Fclk				(float)Fcpu/(float)APBvalue		//	Valor del reloj prescalado por APB.
#define		Ftick			Fclk/(float)(Prescaler+1)		//	Valor del reloj asociado a los contadores.

#define		Ts0				0.5							//	Tiempo de muestreo en segundos sin prescaler. (Muestras)
#define		Fs0				(float)1/(float)Ts0				//	Frecuencia de muestreo en Hz. (Muestras)
#define		CsADC			Fs0							//	Frecuencia de muestreo del LDR.
#define		CsCAP			5*Fs0						//	Frecuencia de muestreo del UVA.

#define		FsAudio			12000						//	3kHz de audio, Nyquist *= 2,	Yo *= 4.
#define		TsAudio			(float)1/(float)FsAudio			//	Periodo de muestreo del audio.
#define		DURACION_AUDIO		2							//	2 segundos de audio.
#define		MUESTRAS_AUDIO		DURACION_AUDIO*FsAudio			//	Muestras en los 2 segundos de audio.


#define	MAX_PRES		MODIFICABLES.Max_servo_p
#define	MAX_TEMP		MODIFICABLES.Max_servo_t
#define	MIN_PRES		MODIFICABLES.Min_servo_p
#define	MIN_TEMP		MODIFICABLES.Min_servo_t
//	Constantes universales.
#define		PI				3.141592
/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@types		Tipos utilizados para el programa.													//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/
typedef signed char				int8_t;
typedef signed short int 		int16_t;
typedef signed int 				int32_t;
typedef signed long long 		int64_t;

typedef unsigned char			uint8_t;
typedef unsigned short int 		uint16_t;
typedef unsigned       int 		uint32_t;
typedef unsigned long long 		uint64_t;

typedef 	struct {			//	Contadores de 8, 16 y 32 bits.
	__IO	uint8_t	i;
	__IO	uint8_t	j;
	__IO	uint16_t	k;
	__IO	uint32_t	Audio;
	__IO uint32_t  Segundos;
	__IO	uint32_t	RITicks;
}Counters_t;

typedef struct {
	uint8_t	CHART;
}State_t;

typedef struct {
		float	Longitud;
		float	Latitud;
		float	Altura;		
}locat_t;

typedef struct {
		float	Temperatura;	//	En grados celsius.
		float	Presion;		//	En pascales.
		float	Humedad;		//	En	%.
		float	IndiceUV;		//	En	UVs.
	locat_t	Lugar;		//	Sitio donde el GPS nos posiciona.
		float	VelViento;	//	En 	m/s.
		float	Brillo;		//	En 	LUX.
}misDatos_t;

typedef struct {
	__IO uint8_t	Anemometro:1;
	__IO uint8_t	AnemometroRev:1;
	__IO uint8_t	LDR:1;
	__IO	uint8_t	LDRrev:1;
	__IO	uint8_t	UVA:1;
	__IO	uint8_t	UVArev:1;
	__IO	uint8_t	Audio:1;
	__IO	uint8_t	Audiorev:1;
	__IO uint8_t	TempRev:1;
}actualizador_t;

typedef struct {
	uint32_t Origen;
	uint32_t Destino;
	uint32_t Linked;
	uint32_t CR;
}LinkedModeDMA_t;

typedef struct {
	float	Max_servo_t;		//	Done
	float	Min_servo_t;		//	Done
	float	Max_servo_p;		//	Done
	float	Min_servo_p;		//	Done
	
	uint8_t	Var_medida;		//	Done
	uint32_t	TiempoBrillo;		//	Done
}modificables_t;

/**---------------------------------------------------------------------------------------------------------------------//
//																								//																																												//
//		@end		ENDFILE.																			//
//																								//
//---------------------------------------------------------------------------------------------------------------------**/

/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               SPI_MSD_Driver.h
** Descriptions:            The SPI SD Card application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Ya Dan
** Created date:            2011-1-4
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef __SPI_MSD_DRIVER_H
#define __SPI_MSD_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

/* Private define ------------------------------------------------------------*/
#define CARDTYPE_MMC     	     0x00
#define CARDTYPE_SDV1      	     0x01
#define CARDTYPE_SDV2      	     0x02
#define CARDTYPE_SDV2HC    	     0x04

#define DUMMY_BYTE				 0xFF 
#define MSD_BLOCKSIZE			 512

/* SD/MMC command list - SPI mode */
#define CMD0                     0       /* Reset */
#define CMD1                     1       /* Send Operator Condition - SEND_OP_COND */
#define CMD8                     8       /* Send Interface Condition - SEND_IF_COND	*/
#define CMD9                     9       /* Read CSD */
#define CMD10                    10      /* Read CID */
#define CMD12                    12      /* Stop data transmit */
#define CMD16                    16      /* Set block size, should return 0x00 */ 
#define CMD17                    17      /* Read single block */
#define CMD18                    18      /* Read multi block */
#define ACMD23                   23      /* Prepare erase N-blokcs before multi block write */
#define CMD24                    24      /* Write single block */
#define CMD25                    25      /* Write multi block */
#define ACMD41                   41      /* should return 0x00 */
#define CMD55                    55      /* should return 0x01 */
#define CMD58                    58      /* Read OCR */
#define CMD59                    59      /* CRC disable/enbale, should return 0x00 */

/* Physical level marcos */
/* PORT number that SD_CD pin assigned on */
#define SD_CD_PORT_NUM		1
/* PIN number that  SD_CD pin assigned on */
#define SD_CD_PIN_NUM		25
/* PORT number that SD_CS pin assigned on */
#define SD_CS_PORT_NUM		1
/* PIN number that  SD_CS pin assigned on */
#define SD_CS_PIN_NUM		21

#define _card_enable()      	GPIO_ClearValue(SD_CS_PORT_NUM, (1<<SD_CS_PIN_NUM))  	
#define _card_disable()     	GPIO_SetValue(SD_CS_PORT_NUM, (1<<SD_CS_PIN_NUM))   
#define _card_power_on()		  	
#define _card_insert()        	(GPIO_ReadValue(SD_CD_PORT_NUM)&(1<<SD_CD_PIN_NUM))


/* Private typedef -----------------------------------------------------------*/
enum _CD_HOLD
{
	HOLD = 0,
	RELEASE = 1,
};

typedef struct               /* Card Specific Data */
{
  uint8_t  CSDStruct;            /* CSD structure */
  uint8_t  SysSpecVersion;       /* System specification version */
  uint8_t  Reserved1;            /* Reserved */
  uint8_t  TAAC;                 /* Data read access-time 1 */
  uint8_t  NSAC;                 /* Data read access-time 2 in CLK cycles */
  uint8_t  MaxBusClkFrec;        /* Max. bus clock frequency */
  uint16_t CardComdClasses;      /* Card command classes */
  uint8_t  RdBlockLen;           /* Max. read data block length */
  uint8_t  PartBlockRead;        /* Partial blocks for read allowed */
  uint8_t  WrBlockMisalign;      /* Write block misalignment */
  uint8_t  RdBlockMisalign;      /* Read block misalignment */
  uint8_t  DSRImpl;              /* DSR implemented */
  uint8_t  Reserved2;            /* Reserved */
  uint32_t DeviceSize;           /* Device Size */
  uint8_t  MaxRdCurrentVDDMin;   /* Max. read current @ VDD min */
  uint8_t  MaxRdCurrentVDDMax;   /* Max. read current @ VDD max */
  uint8_t  MaxWrCurrentVDDMin;   /* Max. write current @ VDD min */
  uint8_t  MaxWrCurrentVDDMax;   /* Max. write current @ VDD max */
  uint8_t  DeviceSizeMul;        /* Device size multiplier */
  uint8_t  EraseGrSize;          /* Erase group size */
  uint8_t  EraseGrMul;           /* Erase group size multiplier */
  uint8_t  WrProtectGrSize;      /* Write protect group size */
  uint8_t  WrProtectGrEnable;    /* Write protect group enable */
  uint8_t  ManDeflECC;           /* Manufacturer default ECC */
  uint8_t  WrSpeedFact;          /* Write speed factor */
  uint8_t  MaxWrBlockLen;        /* Max. write data block length */
  uint8_t  WriteBlockPaPartial;  /* Partial blocks for write allowed */
  uint8_t  Reserved3;            /* Reserded */
  uint8_t  ContentProtectAppli;  /* Content protection application */
  uint8_t  FileFormatGrouop;     /* File format group */
  uint8_t  CopyFlag;             /* Copy flag (OTP) */
  uint8_t  PermWrProtect;        /* Permanent write protection */
  uint8_t  TempWrProtect;        /* Temporary write protection */
  uint8_t  FileFormat;           /* File Format */
  uint8_t  ECC;                  /* ECC code */
  uint8_t  CSD_CRC;              /* CSD CRC */
  uint8_t  Reserved4;            /* always 1*/
}
MSD_CSD;

typedef struct				 /*Card Identification Data*/
{
  uint8_t  ManufacturerID;       /* ManufacturerID */
  uint16_t OEM_AppliID;          /* OEM/Application ID */
  uint32_t ProdName1;            /* Product Name part1 */
  uint8_t  ProdName2;            /* Product Name part2*/
  uint8_t  ProdRev;              /* Product Revision */
  uint32_t ProdSN;               /* Product Serial Number */
  uint8_t  Reserved1;            /* Reserved1 */
  uint16_t ManufactDate;         /* Manufacturing Date */
  uint8_t  CID_CRC;              /* CID CRC */
  uint8_t  Reserved2;            /* always 1 */
}
MSD_CID;

typedef struct
{
  MSD_CSD CSD;
  MSD_CID CID;
  uint32_t Capacity;              /* Card Capacity */
  uint32_t BlockSize;             /* Card Block Size */
  uint16_t RCA;
  uint8_t CardType;
  uint32_t SpaceTotal;            /* Total space size in file system */
  uint32_t SpaceFree;      	     /* Free space size in file system */
}
MSD_CARDINFO, *PMSD_CARDINFO;


/* Private function prototypes -----------------------------------------------*/

int MSD_Init(void);
int MSD_GetCardInfo(PMSD_CARDINFO cardinfo);
int MSD_ReadSingleBlock(uint32_t sector, uint8_t *buffer);
int MSD_ReadMultiBlock(uint32_t sector, uint8_t *buffer, uint32_t NbrOfSector);
int MSD_WriteSingleBlock(uint32_t sector, const uint8_t *buffer);
int MSD_WriteMultiBlock(uint32_t sector, const uint8_t *buffer, uint32_t NbrOfSector);

void MSD_SPI_Configuration(void);
void MSD_SPIHighSpeed(uint8_t b_high);

__inline int _spi_read_write(uint8_t data);
int _send_command(uint8_t cmd, uint32_t arg, uint8_t crc);
int _send_command_hold(uint8_t cmd, uint32_t arg, uint8_t crc);
int _read_buffer(uint8_t *buff, uint16_t len, uint8_t release);

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

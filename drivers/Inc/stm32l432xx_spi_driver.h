/*
 * stm32l432xx_spi_driver.h
 *
 *  Created on: May 23, 2026
 *      Author: geo26
 */

#ifndef INC_STM32L432XX_SPI_DRIVER_H_
#define INC_STM32L432XX_SPI_DRIVER_H_

#include "stm32l432xx.h"
//Configuration structure for SPI

typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t	SPI_SclkSpeed;
	uint8_t SPI_DFF;		//Data frame format
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t	SPI_SSM;		//Slave select management
}SPI_Config_t ;

//Handle structure for SPI

typedef struct{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPIConfig;
}SPI_Handle_t;

// @SPI_DeviceMode
#define SPI_DEVICE_MODE_MASTER			1
#define SPI_DEVICE_MODE_SLAVE			0

//@SPI_BUS_CONFIG
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	4

//@SPI_SCLK_SPEED
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

//@SPI_DFF

#define SPI_DFF_8BITS					0
#define SPI_DFF_16BITS					1

//@SPI_CPOL
#define SPI_CPOL_HIGH					1
#define SPI_CPOL_LOW					0

//@SPI_CPHA
#define	SPI_CPHA_HIGH					1
#define SPI_CPHA_LOW					0

//@SPI_SSM
#define SPI_SSM_EN						1
#define SPI_SM_DI						0

#define SPI_TXE_FLAG					(1 << 1)
#define SPI_RXNE_FLAG					(1 << 0)
#define SPI_BUSY_FLAG					(1 << 7)


//Init and DeInit
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//Peripheral clk
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnDi);

void SPI_SendData(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx , uint8_t *pRxBuffer, uint32_t Len);

void SPI_IRQInteruptConfig(uint8_t IRQNumber , uint8_t EnDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber ,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);


#endif /* INC_STM32L432XX_SPI_DRIVER_H_ */

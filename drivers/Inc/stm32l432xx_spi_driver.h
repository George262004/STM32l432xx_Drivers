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

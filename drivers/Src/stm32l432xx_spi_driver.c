/*
 * stm32l432xx_spi_driver.c
 *
 *  Created on: May 23, 2026
 *      Author: geo26
 */


#include "stm32l432xx_spi_driver.h"

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAGSET;
	}
	return FLAGRESET;
}

//Init and DeInit
void SPI_Init(SPI_Handle_t *pSPIHandle){

	uint32_t tempreg = 0;

	tempreg |= pSPIHandle -> SPIConfig.SPI_DeviceMode << 2;

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){

		//BIDIMODE should be 0
		tempreg &= ~(1 << 15 );
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		//BIDIMODE should be 1
		tempreg |= (1 << 15);

	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		//BIDIMODE is cleared
		tempreg &= ~(1 << 15 );
		//RXONLY is set
		tempreg |= (1 << 10);
	}

	tempreg |= pSPIHandle -> SPIConfig.SPI_SclkSpeed << 3;
	tempreg |= pSPIHandle -> SPIConfig.SPI_DFF << 11;
	tempreg |= pSPIHandle -> SPIConfig.SPI_CPOL << 1;
	tempreg |= pSPIHandle -> SPIConfig.SPI_CPHA << 0;

	pSPIHandle->pSPIx->CR1 = tempreg ;
}


void SPI_DeInit(SPI_RegDef_t *pSPIx){


}


//Peripheral clk
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnDi){

	if(EnDi == ENABLE){

		if (pSPIx == SPI1){
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}

	}else{
		if (pSPIx == SPI1){
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_DI();
		}

	}

}

void SPI_SendData(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer, uint32_t Len){
	while(Len < 0){
		// Wait untill TXE flag is set

		while(SPI_GetFlagStatus(pSPIx,  SPI_TXE_FLAG) == FLAGRESET);

		//Check DFF bit
		if( pSPIx->CR1 & (1<<11) ){
			// 16 bit formaat
			pSPIx->DR = *((uint16_t *) pTxBuffer );
			Len--;
			Len--;
			(uint16_t*) pTxBuffer ++ ;
		}
		else{

			//8 bit format
			pSPIx->DR = *pTxBuffer ;
			Len--;
			pTxBuffer ++ ;
		}
	}

}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx , uint8_t *pRxBuffer, uint32_t Len){


}

void SPI_IRQInteruptConfig(uint8_t IRQNumber , uint8_t EnDi){


}

void SPI_IRQPriorityConfig(uint8_t IRQNumber ,uint32_t IRQPriority){


}

void SPI_IRQHandling(SPI_Handle_t *pHandle){


}


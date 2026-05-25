/*
 * 006spi_tx_testing.c
 *
 *  Created on: May 25, 2026
 *      Author: geo26
 */

#include "stm32l432xx.h"

//Alt function 5
//SCK --> PA1,PA5,PB3
//MOSI --> PA7,PA12,PB5
//NSS --> PA4,PA15,PB0
//MISO --> PA6,PA11,PB4

void SPI1_GPIOINITS(void){
	GPIO_HANDLE_t SPIPins;
	SPIPins.pGPIOx = GPIOA ;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);


}

void SPI1_INITS(void){
	SPI_Handle_t SPI1Handle;

}

int main(void){

	SPI1_GPIOINITS();
	SPI1_INITS();

	return 0;
}

/*
 * 001LED_TOGGLE.c
 *
 *  Created on: Jan 16, 2026
 *      Author: geo26
 */

#include "stm32l432xx.h"
#include "string.h"

void delay(void){
	for(uint32_t i = 0; i < 50000; i++);
}

int main(void){

	GPIO_HANDLE_t GpioBtn;
	memset(&GpioBtn, 0, sizeof(GpioBtn));
	GpioBtn.pGPIOx = GPIOB ;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;


	GPIO_HANDLE_t GpioLed;
	memset(&GpioLed, 0, sizeof(GpioLed));
	GpioLed.pGPIOx = GPIOB ;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_out;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PeriClockControl(GPIOB, ENABLE);
	GPIO_Init(&GpioBtn);

	GPIO_Init(&GpioLed);

	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIOR15);
	GPIO_IRQInteruptConfig(IRQ_NO_EXTI9_5, ENABLE);

	while(1);
	return 0;

}

void EXTI9_5_IRQHandler(void){

	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_NO_3);

}

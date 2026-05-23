/*
 * stm32l432xx_gpio_driver.c
 *
 *  Created on: Dec 30, 2025
 *      Author: geo26
 */




#include "stm32l432xx_gpio_driver.h"

void GPIO_Init(GPIO_HANDLE_t *pGPIOHandle){

	DBGMCU->CR &= ~(1 << 5);// inorder to disable the debug so that the LED can blink

	//Configure mode
	uint32_t temp = 0;

	if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//Non interupt mode
		temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle -> pGPIOx -> MODER &= ~(0x3 << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber) );// clearing the corresponding bit before setting
		pGPIOHandle -> pGPIOx -> MODER |= temp;


	}else{
		//interupt mode

		if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){

			pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
			temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle -> pGPIOx -> MODER &= ~(0x3 << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber) );// clearing the corresponding bit before setting
			pGPIOHandle -> pGPIOx -> MODER |= temp;

			//configure the interupt falling edge trigger

			EXTI->FTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// setting the corresponding line to falling edge trigger.
			EXTI->RTSR1 &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// Disabling the corresponding line to Rising edge trigger.


		}else if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			//configure the interupt rising edge trigger

			EXTI->FTSR1 &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// Disabling the corresponding line to falling edge trigger.
			EXTI->RTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// Enabling the corresponding line to Rising edge trigger.

		}else{
			//configure interupt rising and falling trigger

			EXTI->FTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// Enabling the corresponding line to falling edge trigger.
			EXTI->RTSR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// Enabling the corresponding line to Rising edge trigger.

		}
		//configure GPIO port selection in SYSCFG
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] |= ( portcode << temp2 * 4);

		//configure EXTI interupt delivery using interupt mask register (IMR)

		EXTI->IMR1 |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);



	}

	temp=0;

	//configure speed
	temp = (pGPIOHandle ->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle -> pGPIOx -> OSPEEDR &= ~(0x3 << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle -> pGPIOx ->OSPEEDR |= temp;
	temp=0;

	//configure pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle -> pGPIOx -> PUPDR &= ~(0x3 <<(2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle -> pGPIOx ->PUPDR |= temp;
	temp=0;

	//OUTPUT Type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle -> pGPIOx -> OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle -> pGPIOx ->OTYPER |= temp;
	temp=0;

	//configure the alt functions

	if((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)){
		// Configure the alt function register
		uint8_t temp1,temp2;

		temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // It determines whether the value should be stored in afrl or afrh
		temp2= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // It determines at low or high register, in which bits the data should be stored
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));

	}

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if (pGPIOx ==GPIOA){
			GPIOA_REG_RST();
		}else if(pGPIOx == GPIOB){
			GPIOB_REG_RST();
		}else if(pGPIOx == GPIOC){
			GPIOC_REG_RST();
		}else if(pGPIOx == GPIOH){
			GPIOH_REG_RST();
		}

}

//Peripheral clk
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnDi){

	if(EnDi == ENABLE){

		if (pGPIOx ==GPIOA){
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}

	}else{
		if (pGPIOx ==GPIOA){
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_DI();
		}

	}

}

//Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;

}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value = (uint16_t) (pGPIOx->IDR );
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber , uint8_t Value){
	pGPIOx->ODR |= (Value << PinNumber);

	if(Value == GPIO_PIN_SET){

		pGPIOx->ODR |= (1 << PinNumber);

	}else{

		pGPIOx->ODR &= ~(1 << PinNumber);
	}


}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){

	pGPIOx->ODR = Value;

}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber ){

	pGPIOx->ODR ^= (1 << PinNumber);

}

// IRQ Handling
void GPIO_IRQInteruptConfig(uint8_t IRQNumber , uint8_t EnDi){

	if (EnDi == ENABLE){
		if(IRQNumber <= 31){
			//Program the ISER0
			*NVIC_ISER0 |= (1 << IRQNumber);

		}else if(IRQNumber >31 && IRQNumber < 64){
			//Program ISER1
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber < 96){
					//Program ISER2
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
				}
	}else{
		if(IRQNumber <= 31){
			//Program the ICER0
			*NVIC_ICER0 |= (1 << IRQNumber);

		}else if(IRQNumber >31 && IRQNumber < 64){
			//Program ICER1
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
		else if(IRQNumber >= 64 && IRQNumber < 96){
					//Program ICER2
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
				}
	}

}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber ,uint32_t IRQPriority){

	//first find out which register and which section should we access
	uint8_t iprx = IRQNumber / 4 ;
	uint8_t iprx_section = IRQNumber % 4 ;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR +  iprx) |= (IRQPriority << shift_amount);

}
void GPIO_IRQHandling(uint8_t PinNumber){

	if (EXTI ->PR1 & (1 << PinNumber)){

		// Clearing the interrupt flag
		EXTI ->PR1 |= (1 << PinNumber);
	}


}

/*
 * stm32l432xx_gpio_driver.h
 *
 *  Created on: Dec 30, 2025
 *      Author: geo26
 */

#ifndef INC_STM32L432XX_GPIO_DRIVER_H_
#define INC_STM32L432XX_GPIO_DRIVER_H_

#include "stm32l432xx.h"

typedef struct{
	uint8_t GPIO_PinNumber;			//Possible values from @GPIO PIN NOs
	uint8_t GPIO_PinMode;			//Possible values from @GPIO PIN MODES
	uint8_t GPIO_PinSpeed;			//Possible values from @GPIO PIN SPEEDS
	uint8_t GPIO_PinPuPdControl;	//Possible values from @GPIO PIN PUPD CNTRL
	uint8_t GPIO_PinOPType;			//Possible values from @GPIO PIN OUT TYPES
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

//HANDLE STRUCTURE FOR GPIO PIN

typedef struct{
	//POINTER TO HOLD THE BASE ADDRESS OF THE GPIO PERIPHERAL
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_HANDLE_t;

//@GPIO PIN NOs
#define GPIO_PIN_NO_0 		0
#define GPIO_PIN_NO_1 		1
#define GPIO_PIN_NO_2 		2
#define GPIO_PIN_NO_3 		3
#define GPIO_PIN_NO_4 		4
#define GPIO_PIN_NO_5 		5
#define GPIO_PIN_NO_6 		6
#define GPIO_PIN_NO_7 		7
#define GPIO_PIN_NO_8 		8
#define GPIO_PIN_NO_9 		9
#define GPIO_PIN_NO_10 		10
#define GPIO_PIN_NO_11 		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14 		14
#define GPIO_PIN_NO_15 		15

//@GPIO PIN MODES
// from GPIO Mode register
#define GPIO_MODE_IN	 	0
#define GPIO_MODE_out 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG 	3

#define GPIO_MODE_IT_FT		4  // input falling trigger (IT is not in the gpio mode reg. It is in the exti reg.)
#define GPIO_MODE_IT_RT		5  //input rising trigger
#define GPIO_MODE_IT_RFT	6  //input rising and falling trigger

//@GPIO PIN OUT TYPES
// from GPIO OUTPUT TYPE reg
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OO		1

//@GPIO PIN SPEEDS
//from GPIO PORT SPEED REG
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

//@GPIO PIN PUPD CNTRL
//From GPIO PULLUP PULLDOWN reg
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

//******************************************************************

//********************************************************************

//Init and DeInit
void GPIO_Init(GPIO_HANDLE_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//Peripheral clk
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnDi);

//Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber , uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber );

// IRQ Handling
void GPIO_IRQInteruptConfig(uint8_t IRQNumber , uint8_t EnDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber ,uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32L432XX_GPIO_DRIVER_H_ */

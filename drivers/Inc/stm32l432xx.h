/*
 * stm32l432xx.h
 *
 *  Created on: Dec 27, 2025
 *      Author: geo26
 */

#ifndef INC_STM32L432XX_H_
#define INC_STM32L432XX_H_

#include <stdint.h>

#define __vo volatile

//#########################################   PROCESSOR SPECIFIC REGISTERS   #########################################

//	NVIC Register of processor

//interupt set enable register

#define NVIC_ISER0 			((__vo uint32_t*) 0xE000E100)
#define NVIC_ISER1 			((__vo uint32_t*) 0xE000E104)
#define NVIC_ISER2 			((__vo uint32_t*) 0xE000E108)
#define NVIC_ISER3 			((__vo uint32_t*) 0xE000E10C)

// interupt clear enable register
#define NVIC_ICER0 			((__vo uint32_t*) 0XE000E180)
#define NVIC_ICER1 			((__vo uint32_t*) 0XE000E184)
#define NVIC_ICER2 			((__vo uint32_t*) 0XE000E188)
#define NVIC_ICER3 			((__vo uint32_t*) 0XE000E18C)

//Interrupt priority register
#define NVIC_PR_BASE_ADDR 	((__vo uint32_t*) 0xE000E400)

#define NVIC_IRQ_PRIOR1 		1
#define NVIC_IRQ_PRIOR2			2
#define NVIC_IRQ_PRIOR3			3
#define NVIC_IRQ_PRIOR4			4
#define NVIC_IRQ_PRIOR5			5
#define NVIC_IRQ_PRIOR6			6
#define NVIC_IRQ_PRIOR7			7
#define NVIC_IRQ_PRIOR8			8
#define NVIC_IRQ_PRIOR9			9
#define NVIC_IRQ_PRIOR10		10
#define NVIC_IRQ_PRIOR11		11
#define NVIC_IRQ_PRIOR12		12
#define NVIC_IRQ_PRIOR13		13
#define NVIC_IRQ_PRIOR14		14
#define NVIC_IRQ_PRIOR15		15

#define NO_PR_BITS_IMPLEMENTED 4


//####################################################################################################################

//memory base address

#define FLASH_BASE_ADDR		0x08000000U
#define SRAM1_BASE_ADDR		0x20000000U
#define SRAM2_BASE_ADDR		0x2000C000U
#define ROM					0x1FFF0000U
#define SRAM 				SRAM1_BASE_ADDR

//bus base addresses

#define PERIPH_BASE_ADDR	0x40000000U
#define APB1_BASE_ADDR		PERIPH_BASE_ADDR
#define APB2_BASE_ADDR		0x40010000U
#define AHB1_BASE_ADDR		0x40020000U
#define AHB2_BASE_ADDR		0x48000000U

//DEBUG Base address
#define DBG_BASE_ADDR 		0xE0042000U

//GPIO BASE ADDRESS

#define GPIOA_BASE_ADDR		(AHB2_BASE_ADDR + 0x0000)
#define GPIOB_BASE_ADDR		(AHB2_BASE_ADDR + 0x0400)
#define GPIOC_BASE_ADDR		(AHB2_BASE_ADDR + 0x0800)
#define GPIOH_BASE_ADDR		(AHB2_BASE_ADDR + 0x1C00)

//I2C BASE ADDFRESS

#define I2C1_BASE_ADDR		(APB1_BASE_ADDR + 0x5400) //HANGING IN APB1 BUS
#define I2C3_BASE_ADDR		(APB1_BASE_ADDR + 0x5C00) //HANGING IN APB1 BUS

//SPI BASE ADDFRESS

#define SPI1_BASE_ADDR		(APB2_BASE_ADDR + 0x3000) //HANGING IN APB2 BUS
#define SPI3_BASE_ADDR		(APB1_BASE_ADDR + 0x3C00) //HANGING IN APB1 BUS

//USART BASE ADDRESS

#define USART1_BASE_ADDR	(APB2_BASE_ADDR + 0x3800) //HANGING IN APB2 BUS
#define USART2_BASE_ADDR	(APB1_BASE_ADDR + 0x4400) //HANGING IN APB1 BUS
#define LPUART1_BASE_ADDR	(APB1_BASE_ADDR + 0x8000) //HANGING IN APB1 BUS

//EXTERNAL INERUPT
#define EXTI_BASE_ADDR		(APB2_BASE_ADDR + 0x0400) //HANGING IN APB2 BUS

//SYSCONF
#define SYSCFG_BASE_ADDR	(APB2_BASE_ADDR + 0x0000) //HANGING IN APB2 BUS

//RCC
#define RCC_BASE_ADDR		(AHB1_BASE_ADDR + 0x1000) // HANGING IN AGB1 BUS


#define GPIO_BASEADDR_TO_CODE(x)	((x == GPIOA)? 0 :\
							    	 (x == GPIOB)? 1 :\
							    	 (x == GPIOC)? 1 :\
							    	 (x == GPIOH)? 1 :0 )


// IRQ Number

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

//--------------------------------------- STRUCTURE DEFINITONS ---------------------------------------------------


//SPI structure definitions
typedef struct{
	__vo uint32_t CR1;		//control register 1
	__vo uint32_t CR2;		//control register 2
	__vo uint32_t SR;		//status register
	__vo uint32_t DR;		//data register
	__vo uint32_t CRCPR;	//CRC register
	__vo uint32_t RXCRCR;	//Rx CRC register
	__vo uint32_t TXCRCR;	//Tx CRC register

}SPI_RegDef_t;

//gpio structure definitions

typedef struct{
	__vo uint32_t MODER;		//GPIO port mode register
	__vo uint32_t OTYPER;	//GPIO port output type register
	__vo uint32_t OSPEEDR;	//GPIO port output speed register
	__vo uint32_t PUPDR;		//GPIO port pull-up/pull-down register
	__vo uint32_t IDR;		//GPIO port input data register
	__vo uint32_t ODR;		//GPIO port output data register
	__vo uint32_t BSRR;		//GPIO port bit set/reset register
	__vo uint32_t LCKR;		//GPIO port configuration lock register
	__vo uint32_t AFR[2];	//AFR[0] GPIO alternate function low register AFR[1] GPIO alternate function HIGH register
	__vo uint32_t BRR;		//GPIO port bit reset register

}GPIO_RegDef_t;

// RCC structure definition

typedef struct{
	__vo uint32_t CR;			//Clock control register
	__vo uint32_t ICSCR;		//Internal clock sources calibration register
	__vo uint32_t CFGR;			//Clock configuration register
	__vo uint32_t PLLCFGR;		//PLL configuration register
	__vo uint32_t PLLSAI1CFGR;	//PLLSAI1 configuration register
	__vo uint32_t RESERVED1;
	__vo uint32_t CIER;			//Clock interrupt enable register
	__vo uint32_t CIFR;			//Clock interrupt flag register
	__vo uint32_t CICR;			//Clock interrupt clear register
	__vo uint32_t RESERVED2;
	__vo uint32_t AHB1RSTR;		//AHB1 peripheral reset register
	__vo uint32_t AHB2RSTR;		//AHB2 peripheral reset register
	__vo uint32_t AHB3RSTR;		//AHB3 peripheral reset register
	__vo uint32_t RESERVED3;
	__vo uint32_t APB1RSTR1;	//APB1 peripheral reset register 1
	__vo uint32_t APB1RSTR2;	//APB1 peripheral reset register 2
	__vo uint32_t APB2RSTR;		//APB2 peripheral reset register
	__vo uint32_t RESERVED4;
	__vo uint32_t AHB1ENR;		//AHB1 peripheral clock enable register
	__vo uint32_t AHB2ENR;		//AHB2 peripheral clock enable register
	__vo uint32_t AHB3ENR;		//AHB3 peripheral clock enable register
	__vo uint32_t RESERVED5;
	__vo uint32_t APB1ENR1;		//APB1 peripheral clock enable register 1
	__vo uint32_t APB1ENR2;		//APB1 peripheral clock enable register 2
	__vo uint32_t APB2ENR;		//APB2 peripheral clock enable register
	__vo uint32_t RESERVED6;
	__vo uint32_t AHB1SMENR;	//AHB1 peripheral clocks enable in Sleep and Stop modes register
	__vo uint32_t AHB2SMENR;	//AHB2 peripheral clocks enable in Sleep and Stop modes register
	__vo uint32_t AHB3SMENR;	//AHB3 peripheral clocks enable in Sleep and Stop modes register
	__vo uint32_t RESERVED7;
	__vo uint32_t APB1SMENR1;	//APB1 peripheral clocks enable in Sleep and Stop modes register 1
	__vo uint32_t APB1SMENR2;	//APB1 peripheral clocks enable in Sleep and Stop modes register 2
	__vo uint32_t APB2SMENR;	//APB2 peripheral clocks enable in Sleep and Stop modes register
	__vo uint32_t RESERVED8;
	__vo uint32_t CCIPR;		//Peripherals independent clock configuration register
	__vo uint32_t RESERVED9;
	__vo uint32_t BDCR;			//Backup domain control register
	__vo uint32_t CSR;			//Control/status register
	__vo uint32_t CRRCR;		//Clock recovery RC register
	__vo uint32_t CCIPR2;		//Peripherals independent clock configuration register

}RCC_RegDef_t;

//debug structure definitions

typedef struct{
	__vo uint32_t IDCODE;
	__vo uint32_t CR;
	__vo uint32_t APB1FZR1;
	__vo uint32_t APB1FZR2;
	__vo uint32_t APB2FZR;
}DBGMCU_TypeDef;

//EXTI structure definitions

typedef struct{
	__vo uint32_t IMR1; 		// Interrupt mask register 1
	__vo uint32_t EMR1;			//Event mask register 1 (EXTI_EMR1)
	__vo uint32_t RTSR1;		//Rising trigger selection register 1 (EXTI_RTSR1)
	__vo uint32_t FTSR1;		//Falling trigger selection register 1 (EXTI_FTSR1)
	__vo uint32_t SWIER1;		//Software interrupt event register 1 (EXTI_SWIER1)
	__vo uint32_t PR1;			//Pending register 1 (EXTI_PR1)
	__vo uint32_t reserved;		//Interrupt mask register 2 (EXTI_IMR2)
	__vo uint32_t reserved1;
	__vo uint32_t IMR2;			///Interrupt mask register 2 (EXTI_IMR2)
	__vo uint32_t EMR2;			//Event mask register 2 (EXTI_EMR2)
	__vo uint32_t RTSR2;		//Rising trigger selection register 2 (EXTI_RTSR2)
	__vo uint32_t FTSR2;		//Falling trigger selection register 2 (EXTI_FTSR2)
	__vo uint32_t SWIER2;		//Software interrupt event register 2 (EXTI_SWIER2)
	__vo uint32_t PR2;			//Pending register 2 (EXTI_PR2)
}EXTI_TypeDef;

//SYSCFG register configuration
typedef struct{
	__vo uint32_t MEMRMP;		//SYSCFG memory remap register (SYSCFG_MEMRMP)
	__vo uint32_t CFGR1;		//SYSCFG configuration register 1 (SYSCFG_CFGR1)
	__vo uint32_t EXTICR[4];	//SYSCFG external interrupt configuration register (SYSCFG_EXTICR)
	__vo uint32_t SCSR;			//SYSCFG SRAM2 control and status register (SYSCFG_SCSR)
	__vo uint32_t CFGR2;		//SYSCFG configuration register 2 (SYSCFG_CFGR2)
	__vo uint32_t SWPR;			//SYSCFG SRAM2 write protection register (SYSCFG_SWPR)
	__vo uint32_t SKR;			//SYSCFG SRAM2 key register (SYSCFG_SKR)


}SYSCFG_TypeDef;

//SYSCFG definitions
#define SYSCFG ((SYSCFG_TypeDef *) SYSCFG_BASE_ADDR)

//EXTI definitions
#define EXTI ((EXTI_TypeDef *) EXTI_BASE_ADDR)

//Debug definitions
#define DBGMCU ((DBGMCU_TypeDef *) DBG_BASE_ADDR)

// Peripheral definitions

#define GPIOA ( (GPIO_RegDef_t* ) GPIOA_BASE_ADDR)
#define GPIOB ( (GPIO_RegDef_t* ) GPIOB_BASE_ADDR)
#define GPIOC ( (GPIO_RegDef_t* ) GPIOC_BASE_ADDR)
#define GPIOH ( (GPIO_RegDef_t* ) GPIOH_BASE_ADDR)

#define SPI1 ( (SPI_RegDef_t*) SPI1_BASE_ADDR)
#define SPI3 ( (SPI_RegDef_t*) SPI3_BASE_ADDR)

#define RCC ( (RCC_RegDef_t*) RCC_BASE_ADDR )

//--------------------------------------------------------------------------------------------------------------------------

//CLOCK ENABLE MACROS FOR GPIOx

#define GPIOA_PCLK_EN()  (RCC -> AHB2ENR |= ( 1 << 0 ))
#define GPIOB_PCLK_EN()  (RCC -> AHB2ENR |= ( 1 << 1 ))
#define GPIOC_PCLK_EN()  (RCC -> AHB2ENR |= ( 1 << 2 ))
#define GPIOH_PCLK_EN()  (RCC -> AHB2ENR |= ( 1 << 7 ))

//CLOCK ENABLE MACROS FOR I2C

#define I2C1_PCLK_EN()  (RCC -> APB1ENR1 |= ( 1 << 21 ))
#define I2C3_PCLK_EN()  (RCC -> APB1ENR1 |= ( 1 << 23 ))

//CLOCK ENABLE MACROS FOR SPI

#define SPI1_PCLK_EN()  (RCC -> APB2ENR |= ( 1 << 12 ))
#define SPI3_PCLK_EN()  (RCC -> APB1ENR1 |= ( 1 << 15 ))

//CLOCK ENABLE MACROS FOR UART

#define USART1_PCLK_EN()  (RCC -> APB2ENR |= ( 1 << 14 ))
#define USART2_PCLK_EN()  (RCC -> APB1ENR1 |= ( 1 << 17 ))
#define LPUART1_PCLK_EN()  (RCC -> APB1ENR2 |= ( 1 << 0 ))

//CLOCK ENABLE FOR SYSCONFIG
#define SYSCFG_PCLK_EN()  (RCC -> APB2ENR |= ( 1 << 0 ))

//----------------------------------------------------------------------------------------------------------------------------

//CLOCK DISABLE MACROS FOR GPIOx

#define GPIOA_PCLK_DI()  (RCC -> AHB2ENR &= ~( 1 << 0 ))
#define GPIOB_PCLK_DI()  (RCC -> AHB2ENR &= ~( 1 << 1 ))
#define GPIOC_PCLK_DI()  (RCC -> AHB2ENR &= ~( 1 << 2 ))
#define GPIOH_PCLK_DI()  (RCC -> AHB2ENR &= ~( 1 << 7 ))

//CLOCK DISABLE MACROS FOR I2C

#define I2C1_PCLK_DI()  (RCC -> APB1ENR1 &= ~( 1 << 21 ))
#define I2C3_PCLK_DI()  (RCC -> APB1ENR1 &= ~( 1 << 23 ))

//CLOCK DISABLE MACROS FOR SPI

#define SPI1_PCLK_DI()  (RCC -> APB2ENR &= ~( 1 << 12 ))
#define SPI3_PCLK_DI()  (RCC -> APB1ENR1 &= ~( 1 << 15 ))

//CLOCK DISABLE MACROS FOR UART

#define USART1_PCLK_DI()  (RCC -> APB2ENR &= ~( 1 << 14 ))
#define USART2_PCLK_DI()  (RCC -> APB1ENR1 &= ~( 1 << 17 ))
#define LPUART1_PCLK_DI()  (RCC -> APB1ENR2 &= ~( 1 << 0 ))

//CLOCK DISABLE FOR SYSCONFIG
#define SYSCFG_PCLK_DI()  (RCC -> APB2ENR &= ~( 1 << 0 ))

//Macros for GPIO Reset
#define GPIOA_REG_RST()		do{(RCC -> AHB2RSTR |= ( 1 << 0 )) ; (RCC -> AHB2RSTR &= ~( 1 << 0 ));} while(0)
#define GPIOB_REG_RST()		do{(RCC -> AHB2RSTR |= ( 1 << 1 )) ; (RCC -> AHB2RSTR &= ~( 1 << 1 ));} while(0)
#define GPIOC_REG_RST()		do{(RCC -> AHB2RSTR |= ( 1 << 2 )) ; (RCC -> AHB2RSTR &= ~( 1 << 2 ));} while(0)
#define GPIOH_REG_RST()		do{(RCC -> AHB2RSTR |= ( 1 << 7 )) ; (RCC -> AHB2RSTR &= ~( 1 << 7 ));} while(0)
//----------------------------------------------------------------------------------------------------------------------------------

//Some generic macros

#define ENABLE 			1
#define Disable 		0
#define SET 			ENABLE
#define RESET 			Disable
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET  RESET


#include "stm32l432xx_gpio_driver.h"
#include "stm32l432xx_spi_driver.h"


#endif /* INC_STM32L432XX_H_ */

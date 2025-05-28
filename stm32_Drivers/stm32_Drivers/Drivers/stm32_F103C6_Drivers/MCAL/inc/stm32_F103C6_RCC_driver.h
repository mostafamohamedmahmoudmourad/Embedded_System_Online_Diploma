/*
 * stm32_F103C6_gpio_driver.h
 *
 *  Created on: Sep 13, 2024
 *      Author: Mostafa Mourad
 */

#ifndef MCAL_INC_STM32_F103C6_RCC_DRIVER_H_
#define MCAL_INC_STM32_F103C6_RCC_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"


#define HSI_RC_CLK		(uint32_t)80000000
#define HSE_Clock		(uint32_t)16000000


uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);



#endif /* MCAL_INC_STM32_F103C6_RCC_DRIVER_H_ */

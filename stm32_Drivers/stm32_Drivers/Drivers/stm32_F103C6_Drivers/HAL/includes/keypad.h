/*
 * keypad.h
 *
 * Created: 11/09/2024 15:36:17
 *  Author: Mostafa Mourad
 */

#ifndef HAL_INCLUDES_KEYPAD_H_
#define HAL_INCLUDES_KEYPAD_H_

#include "../../MCAL/inc/stm32_F103C6_gpio_driver.h"
#include "../../MCAL/inc/stm32f103x6.h"
#include <stdio.h>
#include <stdlib.h>



#define  KEYPAD_PORT			GPIOB

GPIO_PinConfig_t PinCfg;


#define R0	GPIO_PIN_0
#define R1	GPIO_PIN_1
#define R2	GPIO_PIN_3
#define R3	GPIO_PIN_4
#define C0	GPIO_PIN_5
#define C1	GPIO_PIN_6
#define C2	GPIO_PIN_7
#define C3	GPIO_PIN_8


void KEYPAD_INIT();
char KEYPAD_GETCHAR();


#endif /* HAL_INCLUDES_KEYPAD_H_ */

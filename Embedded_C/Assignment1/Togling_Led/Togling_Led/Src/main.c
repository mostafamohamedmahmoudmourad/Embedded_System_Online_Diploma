/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mostafa Mourad
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


#include "stdint.h"

#define RCC_BASE        0x40021000
#define PORTA_BASE      0x40010800

typedef volatile uint32_t    vuint32_t;

#define RCC_APB2ENR     *((vuint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRH       *((vuint32_t *)(PORTA_BASE + 0x04))
#define GPIOA_ODR       *((vuint32_t *)(PORTA_BASE + 0x0C))

#define RCC_IOPAEN      (1<<2)

typedef union
{
    vuint32_t       all_fields;
    struct {
        vuint32_t   reserved:13;
        vuint32_t   P_13:1;
    }Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORTA_BASE + 0x0C);

int main(void)
{
    RCC_APB2ENR |= RCC_IOPAEN;
    GPIOA_CRH    &= 0xFF0FFFFF;
    GPIOA_CRH    |= 0x00200000;

    while(1)
    {
         R_ODR->Pin.P_13 = 1;
         for(int i = 0; i < 10000; i++);
         R_ODR->Pin.P_13 = 0;
         for(int i = 0; i < 10000; i++);
    }
}


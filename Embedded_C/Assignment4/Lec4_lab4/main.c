/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mostafa Mourad
 * @brief          : Togling_Led
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


#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))

int main ()
{
    volatile unsigned long delay_count;
    SYSCTL_RCGC2_R = 0x20; // Enable clock for Port F
    // Short delay to allow clock to stabilize
    for(delay_count=0; delay_count<200; delay_count++);
     GPIO_PORTF_DEN_R |= (1<<3); // Enable digital function for PF3
    GPIO_PORTF_DIR_R |= (1<<3); // Set PF3 as output
    while(1)
    {
        GPIO_PORTF_DATA_R |= 1<<3; // Set PF3 high
        for(delay_count=0; delay_count<20000; delay_count++);
        GPIO_PORTF_DATA_R &= ~(1<<3); // Set PF3 low
        for(delay_count=0; delay_count<20000; delay_count++);
    }
    return 0;
}
/*
 * stm32_F103C6_gpio_driver.h
 *
 *  Created on: Sep 13, 2024
 *      Author: Mostafa Mourad
 */

#ifndef MCAL_INC_STM32_F103C6_GPIO_DRIVER_H_
#define MCAL_INC_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct {
	uint16_t GPIO_PinNumber;		// Specifies the GPIO pins to be configured.
									// This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE;				// Specifies the operating mode for the selected pins
									// This parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed;		// Specifies the speed for the selected pins
									// This parameter can be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;


//-----------------------------
//Macros Configuration References
//-----------------------------


//============================================================================
//@ref GPIO_SPEED_define
//============================================================================
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

//============================================================================
//@ref GPIO_RETURN_LOCK
//============================================================================
#define GPIO_RETURN_LOCK_Enabled		1
#define GPIO_RETURN_LOCK_ERROR			0


//============================================================================
//@ref GPIO_PINS_define
//============================================================================

#define GPIO_PIN_0		((uint16_t)0x0001)	/*Pin 0  Selected */
#define GPIO_PIN_1		((uint16_t)0x0002)	/*Pin 1  Selected */
#define GPIO_PIN_2		((uint16_t)0x0004)	/*Pin 2  Selected */
#define GPIO_PIN_3		((uint16_t)0x0008)	/*Pin 3  Selected */
#define GPIO_PIN_4		((uint16_t)0x0010)	/*Pin 4  Selected */
#define GPIO_PIN_5		((uint16_t)0x0020)	/*Pin 5  Selected */
#define GPIO_PIN_6		((uint16_t)0x0040)	/*Pin 6  Selected */
#define GPIO_PIN_7		((uint16_t)0x0080)	/*Pin 7  Selected */
#define GPIO_PIN_8		((uint16_t)0x0100)	/*Pin 8  Selected */
#define GPIO_PIN_9		((uint16_t)0x0200)	/*Pin 9  Selected */
#define GPIO_PIN_10		((uint16_t)0x0400)	/*Pin 10 Selected */
#define GPIO_PIN_11		((uint16_t)0x0800)	/*Pin 11 Selected */
#define GPIO_PIN_12		((uint16_t)0x1000)	/*Pin 12 Selected */
#define GPIO_PIN_13		((uint16_t)0x2000)	/*Pin 13 Selected */
#define GPIO_PIN_14		((uint16_t)0x4000)	/*Pin 14 Selected */
#define GPIO_PIN_15		((uint16_t)0x8000)	/*Pin 15 Selected */

#define GPIO_PIN_All	((uint16_t)0xFFFF)	/*All Pins Selected */

//============================================================================
//@ref GPIO_MODE_define
//============================================================================

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function Input


#define GPIO_MODE_Analog				0x00000000u		//0: Analog mode
#define GPIO_MODE_Input_FLO				0x00000001u		//1: Floating input (reset state)
#define GPIO_MODE_Input_PU				0x00000002u		//2: Input with pull-up
#define GPIO_MODE_Input_PD				0x00000003u		//3: Input with pull-down
#define GPIO_MODE_Output_PP				0x00000004u		//4: General purpose output push-pull
#define GPIO_MODE_Output_OD				0x00000005u		//5: General purpose output Open-drain
#define GPIO_MODE_Output_AF_PP			0x00000006u		//6: Alternate function output Push-pull
#define GPIO_MODE_Output_AF_OD			0x00000007u		//7: Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT				0x00000008u		//8: Alternate function Input


//============================================================================
//@ref GPIO_SPEED_define
//============================================================================
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.

#define GPIO_Speed_Reset_State          0x00000000u  // you should set this define in case of Input_Mode
#define GPIO_SPEED_10M					0x00000001u		//1: Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M					0x00000002u		//2: Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M					0x00000003u		//3: Output mode, max speed 50 MHz.


//============================================================================

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void MCAL_GPIO_INIT(GPIO_TypeDef * GPIOx,GPIO_PinConfig_t *PinCofig);
void MCAL_GPIO_DEINIT(GPIO_TypeDef * GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx, uint16_t PinNumber);

#endif /* MCAL_INC_STM32_F103C6_GPIO_DRIVER_H_ */

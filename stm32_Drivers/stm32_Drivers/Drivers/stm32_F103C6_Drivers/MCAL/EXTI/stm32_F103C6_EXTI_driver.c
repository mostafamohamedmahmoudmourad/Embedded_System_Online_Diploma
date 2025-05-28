/*
 * stm32_F103C6_EXTI_driver.c
 *
 *  Created on: Sep 13, 2024
 *      Author: Mostafa Mourad
 */

#include "../inc/stm32_F103C6_EXTI_driver.h"



/*
 * ------------------------------------------------------------------------------
 * 								Generic Variables
 *-------------------------------------------------------------------------------
 */

void(* GP_IRQ_CallBack[15])(void);


/*
 * ------------------------------------------------------------------------------
 * 								Generic Macros
 *-------------------------------------------------------------------------------
 */

#define AFIO_GPIO_EXTI_Mapping(x)		((x==GPIOA)?0:\
										 (x==GPIOB)?1:\
										 (x==GPIOC)?2:\
										 (x==GPIOD)?3:0 )


/*
 * ------------------------------------------------------------------------------
 * 								Generic Function
 *-------------------------------------------------------------------------------
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
		{
		case 0:
			NVIC_IRQ6_EXTI0_Disable;
			break;
		case 1:
			NVIC_IRQ7_EXTI1_Disable;
			break;
		case 2:
			NVIC_IRQ8_EXTI2_Disable;
			break;
		case 3:
			NVIC_IRQ9_EXTI3_Disable;
			break;
		case 4:
			NVIC_IRQ10_EXTI4_Disable;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_Disable;
			break;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_Disable;
			break;
		}
}


//=========================================================================

void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1- Config GPIO to be  AF Input -> FLoating INPUT

	GPIO_PinConfig_t PinCfg;
	//Update the GPIO Pin to be Floating Input;
	PinCfg.GPIO_PinNumber 	= EXTI_Config->EXTI_PIN.ETI_InputLineNumber;
	PinCfg.GPIO_MODE 		= GPIO_MODE_Input_FLO;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_Port, &PinCfg);
	//---------------------------------------------------------------


	//2- Update AFIO to Route between EXTI Line with Port A,B,C,D

	uint8_t AFIO_EXTIICR_index 		= EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4;
	uint8_t AFIO_EXTIICR_position 	= (EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4) * 4;

	//clear the  Four bit
	AFIO->EXTICR[AFIO_EXTIICR_index] &= ~(0xf << AFIO_EXTIICR_position);
	// Setting
	AFIO->EXTICR[AFIO_EXTIICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTIICR_position);
	//------------------------------------
	//3- Falling or Rising Register
	//------------------------------------
	EXTI->RTSR &= ~(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);


	if(EXTI_Config->Trigger==EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger==EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else if(EXTI_Config->Trigger==EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |= (1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}

	//------------------------------------
	//4- Update IRQ Handling CALLBACK
	//------------------------------------
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//------------------------------------
	//5- Enable/Disable IRQ
	//------------------------------------

	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else
	{
		EXTI->IMR &= ~(1<< EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}


}







///**================================================================
// * @Fn			- MCAL_EXTI_GPIO_DEINIT
// * @brief			- Reset EXTI Register and NVIC corresponding IRQ Mask
// * @param [in] 	- GPIOX: where x can be (A..E depending on device used) to select the GPIO peripheral
// * @retval 		- none
// * Note			- none
// */

void MCAL_EXTI_GPIO_DEINIT(void)
{
	EXTI->IMR    =  0x00000000;
	EXTI->EMR  	 =  0x00000000;
	EXTI->RTSR 	 =  0x00000000;
	EXTI->FTSR 	 =  0x00000000;
	EXTI->SWIER  =  0x00000000;
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR    =   0xFFFFFFFF;

	//disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;
}




///**================================================================
// * @Fn			- MCAL_EXTI_GPIO_INIT
// * @brief			- This is used to inialize EXTI from Specific GPIO PIN and Specify the Mask/Trigger condition and IRQ CallBack
// * @param [in] 	- EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and and EXTI IRQ define
// * @retval 		- none
// * Note			- none
// */

void MCAL_EXTI_GPIO_INIT(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


///**================================================================
// * @Fn			- MCAL_EXTI_GPIO_Update
// * @brief			- This is used to inialize EXTI from Specific GPIO PIN and Specify the Mask/Trigger condition and IRQ CallBack
// * @param [in] 	- EXTI_Config set by @ref EXTI_define, EXTI_Trigger_define and and EXTI IRQ define
// * @retval 		- none
// * Note			- none
// */

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


//===================================================================
//						ISR Function
//===================================================================
void EXTI0_IRQHandler(void)
{
	//Cleared by Write a '1' into the bit Pending Register (EXTI_PR)
	EXTI->PR |= (1<<0);
	//Call IRQ_CALL
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	//Cleared by Write a '1' into the bit Pending Register (EXTI_PR)
	EXTI->PR |= (1<<1);
	//Call IRQ_CALL
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	//Cleared by Write a '1' into the bit Pending Register (EXTI_PR)
	EXTI->PR |= (1<<2);
	//Call IRQ_CALL
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//Cleared by Write a '1' into the bit Pending Register (EXTI_PR)
	EXTI->PR |= (1<<3);
	//Call IRQ_CALL
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	//Cleared by Write a '1' into the bit Pending Register (EXTI_PR)
	EXTI->PR |= (1<<4);
	//Call IRQ_CALL
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5 ) { EXTI->PR |= (1<<5); 		GP_IRQ_CallBack[5]();  }
	if(EXTI->PR & 1<<6 ) { EXTI->PR |= (1<<6); 		GP_IRQ_CallBack[6]();  }
	if(EXTI->PR & 1<<7 ) { EXTI->PR |= (1<<7); 		GP_IRQ_CallBack[7]();  }
	if(EXTI->PR & 1<<8 ) { EXTI->PR |= (1<<8); 		GP_IRQ_CallBack[8]();  }
	if(EXTI->PR & 1<<9 ) { EXTI->PR |= (1<<9); 		GP_IRQ_CallBack[9]();  }
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10 ) { EXTI->PR |= (1<<10); 		GP_IRQ_CallBack[10]();  }
	if(EXTI->PR & 1<<11 ) { EXTI->PR |= (1<<11); 		GP_IRQ_CallBack[11]();  }
	if(EXTI->PR & 1<<12 ) { EXTI->PR |= (1<<12); 		GP_IRQ_CallBack[12]();  }
	if(EXTI->PR & 1<<13 ) { EXTI->PR |= (1<<13); 		GP_IRQ_CallBack[13]();  }
	if(EXTI->PR & 1<<14 ) { EXTI->PR |= (1<<14); 		GP_IRQ_CallBack[14]();  }
	if(EXTI->PR & 1<<15 ) { EXTI->PR |= (1<<15); 		GP_IRQ_CallBack[15]();  }
}




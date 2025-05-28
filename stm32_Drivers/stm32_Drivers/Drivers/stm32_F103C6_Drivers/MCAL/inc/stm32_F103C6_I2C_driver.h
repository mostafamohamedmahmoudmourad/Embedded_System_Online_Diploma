/*
 * stm32_F103C6_I2C_driver.h
 *
 *  Created on: 14 Oct 2024
 *      Author: Mostafa Mourad
 */

#ifndef MCAL_INC_STM32_F103C6_I2C_DRIVER_H_
#define MCAL_INC_STM32_F103C6_I2C_DRIVER_H_


//Includes
#include <stdio.h>
#include <stdlib.h>
#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "stm32_F103C6_RCC_driver.h"






typedef struct
{
	uint16_t Enable_DUAL_Address; 		//1 = Enable , 0 = Disable
	uint16_t Primary_Slave_Address;
	uint16_t Secondary_Slave_Address;
	uint32_t I2C_Addressing_Slave_Mode;	//Specifies the Addressing Mode of I2C Slave
										//This Parameter must be set with value
										//from Macro Configuration Manual @ref I2C_Addressing_Slave_Mode_Define

}S_I2C_Slave_Device_Address;

typedef enum
{
	I2C_enable,
	I2C_disable
}E_Functional_State;


typedef enum
{
	I2C_EV_STOP,
	I2C_ER_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,		//Application Layer Should send data in this state (MCAL_I2C_SlaveSendData)
	I2C_EV_DATA_RCV			//Application Layer Should read data in this state (MCAL_I2C_SlaveReadData)

}E_Slave_State;

typedef enum
{
	withSTOP,
	withoutSTOP
}E_STOP_CONDITION;


typedef enum
{
	Repeated_Start,
	No_Repeated_Start
}E_Repeated_Start;


typedef enum
{
	RESET,
	SET
}E_I2C_Flag_Status;


#define I2C_EV_MASTER_BYTE_TRANSMITTER 						((uint32_t)0x00070080) //TRA, BUSY, MSL , TXE FLAGS


typedef enum
{
	I2C_FLAG_BUSY,
	EV5, 	//EV5: SB=1, cleared by reading SR1 register
	EV6, 	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV8,	//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_2,	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	EV7,	//EV7: RxNE=1 Cleared by Reading DR Register
	MASTER_BYTE_TRANSMITTER = ((uint32_t)0x00070080),




}E_Status;

typedef enum
{
	Transmitter,
	Reciever
}E_Direction;



//========================================================
//				Configuration Structure
//===



typedef struct
{
	uint32_t				I2C_ClockSpeed; 		// Specifies the clock frequency.\
													this parameter must be set to @I2C_SCLK_Define

	uint32_t 				Stretch_Mode ;  	  //Specifies Mode of I2C Clock Stretching (Enabled / Disabled)
												 //This Parameter must be set with value
												//from Macro Configuration Manual @ref I2C_Stretch_Mode_Define

	uint32_t 				I2C_Mode;			  //Specifies the I2C  Mode
												 //This Parameter must be set with value
												//from Macro Configuration Manual @ref I2C_Mode_Define

	uint32_t 				I2C_ACK_Control;	  //Specifies Mode of I2C Ack respond (Enabled / Disabled)
												 //This Parameter must be set with value
												//from Macro Configuration Manual @ref I2C_ACK_Control_Define

	uint32_t 				General_Call_Address_Detection;		  //Specifies Mode of General Call Address Detection (Enabled / Disabled)
																 //This Parameter must be set with value
																//from Macro Configuration Manual @ref General_Call_Define

	S_I2C_Slave_Device_Address I2C_Slave_Address_Mode;

	void (* Ptr_Slave_EV_IRQ_CallBack)(E_Slave_State state); //Set C function to be called once IRQ Happens




}I2C_Config_t;



//================================================
//Reference Macros
//================================================


//-------------------------------------------------------------
//@I2C_SCLK_Define
#define I2C_SCLK_SM_50K				(0x50000U)
#define I2C_SCLK_SM_100K			(100000U)
#define I2C_SCLK_FM_200K			(200000U)//Fast Mode Not Supported Yet
#define I2C_SCLK_FM_400K			(400000U))//Fast Mode Not Supported Yet

//-------------------------------------------------------------
//@ref I2C_Stretch_Mode_Define
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled

#define I2C_StretchMode_Enable 	0x00000000U
#define I2C_StretchMode_Disable	I2C_CR1_NOSTRETCH


//-------------------------------------------------------------
//@ref I2C_Mode_Define
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode

#define I2C_Mode_I2C								(0x0)
#define I2C_Mode_SMBus								I2C_CR1_SMBUS



//-------------------------------------------------------------
//@ref I2C_Addressing_Slave_Mode_Define
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)

#define I2C_Slave_7Bit_Address						(0x0)
#define I2C_Slave_10Bit_Address						I2C_OAR1_ADDMODE


//-------------------------------------------------------------
//@ref I2C_ACK_Control_Define
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or dat

#define I2C_ACK_Disable								(0x0)
#define I2C_ACK_Enable								I2C_CR1_ACK



//-------------------------------------------------------------
//@ref General_Call_Define
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.

#define I2C_General_Call_Enabled					I2C_CR1_ENGC
#define I2C_General_Call_Disabled					(0x0)






//-----------------------------------------------------------------
//*****************************************************************
//-----------------------------------------------------------------


//========================================================
//			APIs Supported by "MCAL I2C DRIVER"
//========================================================

void MCAL_I2C_Init(I2C_TypeDef* I2Cx , I2C_Config_t* I2C_Config);
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx );

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

void MCAL_I2C_MASTER_TX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start );
void MCAL_I2C_MASTER_RX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start );

void MCAL_I2C_SLAVE_TX (I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t MCAL_I2C_SLAVE_RX (I2C_TypeDef* I2Cx);






//========================================================
//					Generic APIs
//========================================================
void I2C_GenerateSTART(I2C_TypeDef* I2Cx,E_Functional_State State ,E_Repeated_Start Start );

E_I2C_Flag_Status I2C_Get_Status ( I2C_TypeDef* I2Cx , E_Status flag);

void I2C_SendAddress (I2C_TypeDef* I2Cx , uint16_t Address, E_Direction I2C_Direction);

void I2C_GenerateSTOP(I2C_TypeDef* I2Cx,E_Functional_State State);

void I2C_AckConfig (I2C_TypeDef* I2Cx, E_Functional_State State);













#endif /* MCAL_INC_STM32_F103C6_I2C_DRIVER_H_ */

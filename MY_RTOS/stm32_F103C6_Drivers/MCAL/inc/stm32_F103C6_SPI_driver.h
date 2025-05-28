/*
 * stm32_F103C6_SPI_driver.h
 *
 *  Created on: 10 Oct 2024
 *      Author: Mostafa Mourad
 */

#ifndef MCAL_INC_STM32_F103C6_SPI_DRIVER_H_
#define MCAL_INC_STM32_F103C6_SPI_DRIVER_H_

//*************************************
// 				Include Header
//*************************************
#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "Data_Types.h"
#include <stdio.h>

//========================================
//		Macros Configuration References
//========================================
//@ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE							(uint32_t)(0)	         //CR1 >> Bit 2 MSTR: Slave selection
#define SPI_Device_Mode_MASTER  						(uint32_t)(1<<2)         //CR1 >> Bit 2 MSTR: Master selection

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES		 					(uint32_t)(0)	         //CR1 >> Bit 10 RXONLY: Full Duplex
#define SPI_DIRECTION_2LINES_RXONLY	 					(uint32_t)(1<<10)        //CR1 >> Bit 10 RXONLY: Receive only
#define SPI_DIRECTION_1LINES_transmit_only				(uint32_t)(1<<15 | 1<<14)//CR1 >> Bit 15 BIDIMODE: Bidirectional data mode enable
															  	  	 //CR1 >> Bit 14 BIDIOE: Output disabled (receive-only mode)
#define SPI_DIRECTION_1LINES_receive_only 				(uint32_t)(1<<15)        //CR1 >> Bit 15 BIDIMODE: Bidirectional data mode enable
															  	  	 //CR1 >> Bit 14 BIDIOE: Output enabled (transmit-only mode)
//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first			(uint32_t)(0)   //( MSB First)
#define SPI_Frame_Format_LSB_transmitted_first			(uint32_t)(1<<7)//CR1 >> Bit 7 LSBFIRST: Frame format (LSB First)

//@ref SPI_DataSize
#define SPI_Frame_Format_8BIT							(uint32_t)(0)
#define SPI_Frame_Format_16BIT							(uint32_t)(1<<11)//CR1 >> Bit 11 DFF: Data frame format

//@ref SPI_CLKPolarity
#define	SPI_Clock_Polarity_LOW_when_Idle				(uint32_t)(0)    //CR1 >> Bit1 CPOL: CK to 0(Low_Level) when idle
#define	SPI_Clock_Polarity_HIGH_when_Idle				(uint32_t)(1<<1) //CR1 >> Bit1 CPOL: CK to 1(High_Level) when idle

//@ref SPI_CLKPhase
#define	SPI_Clock_Phase_1EDGE_first_data_capture_edge	(uint32_t)(0)
#define	SPI_Clock_Phase_2EDGE_first_data_capture_edge	(uint32_t)(1<<0)//CR1 >> Bit 0 CPHA: Clock phase

//@ref SPI_NSS SPI Slave Select Management
//-----------------NSS--------------------
//Hardware
#define SPI_NSS_Hard_Slave  							(uint32_t)(0)   //CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_Hard_Master_SS_Output_Enable			(uint32_t)(1<<2)//CR2 >>Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_Output_Disable		   ~((uint32_t)(1<<2))	//CR2 >>Bit 2 SSOE: SS output enable

//NSS is Driven by SW (Master or Slave)
#define SPI_NSS_SW_NSSInternalSoft_Reset				(uint32_t)(1<<9)//CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_SW_NSSInternalSoft_Set					(uint32_t)(1<<9 | 1<<8)// for Slave & Master

/* Bits 5:3 BR[2:0]: Baud rate control
000: fPCLK/2   ,,,  001: fPCLK/4  ,,, 010: fPCLK/8    ,,, 011: fPCLK/16
100: fPCLK/32  ,,,  101: fPCLK/64 ,,, 110: fPCLK/128  ,,, 111: fPCLK/256  */
//@ref SPI_BAUDRATEPRESCALER
#define SPI_BaudRatePrescaler_2							(uint32_t)(0) //CR1 >> Bits 5:3 BR[2:0]: Baud rate control
#define SPI_BaudRatePrescaler_4							(uint32_t)(0b001U << 3)
#define SPI_BaudRatePrescaler_8							(uint32_t)(0b010U << 3)
#define SPI_BaudRatePrescaler_16						(uint32_t)(0b011U << 3)
#define SPI_BaudRatePrescaler_32						(uint32_t)(0b100U << 3)
#define SPI_BaudRatePrescaler_64						(uint32_t)(0b101U << 3)
#define SPI_BaudRatePrescaler_128						(uint32_t)(0b110U << 3)
#define SPI_BaudRatePrescaler_256						(uint32_t)(0b111U << 3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE								(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE							(uint32_t)(1<<7)//CR2 >> Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE							(uint32_t)(1<<5)//CR2 >> Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE							(uint32_t)(1<<6)//CR2 >> Bit 5 ERRIE: Error interrupt enable


//==============================================
//			User type definitions (structures)
//==============================================
struct S_IRQ_SRC
{
	uint8_t TXE:1 ;
	uint8_t RXNE:1 ;
	uint8_t ERRI:1 ;
	uint8_t Reserved:5 ;
};

typedef struct
{
	uint16_t 	Device_Mode;			//specifies the SPI operation mode @ref SPI_Device_Mode

	uint16_t 	Communication_Mode;		//specifies the SPI bidirectional mode state @ref SPI_Communication_Mode

	uint16_t 	Frame_Format;          	//specifies LSB or MSB @ref SPI_Frame_Format

	uint16_t	DataSize;				//specifies Size of TX/RX Data 8/16 Bits @ref SPI_DataSize

	uint16_t	CLKPolarity;			//specifies Clock Polarity (Low_Level when Idle or High_Level when idle )
										//this Parameter set based on @ref SPI_CLKPolarity

	uint16_t 	CLKPhase;				//specifies Clock Phase (Sampling at 1st or 2nd edge)according to CLKPolarity
										//this Parameter set based on @ref SPI_CLKPhase

	uint16_t	NSS;					//specifies whether the NSS signal managed by
										//Hardware (NSS Pin) or (Software SSI bit enable)
										//this Parameter set based on @ref SPI_NSS

	uint16_t	SPI_BAUDRATEPRESCALER;	//Specifies the baud rate prescaler value which will be
										//used to configure the transmit and receive SCK Clock.
										//This Parameter can be a value of @ref SPI_BAUDRATEPRESCALER
										//@note The Communication Clock derived form the master clock.
										//The slave clock dose not need to be set.
										//Take care you have to Configure RCC to enter the correct clock to APB1 >> SPI2
										//or APB2 >> SPI1 .

	uint16_t	IRQ_Enable ;            //Specifies Interrupt Enable or Disable
										//This parameter must be set based on @ref SPI_IRQ_Enable

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src );// Set C Function() which will be called once the IRQ Happen .

}SPI_Config_t;

enum PollingMechanism
{
	PollingEnable ,
	PollingDisable
};

/* ===============================================
 * APIs Supported by "MCAL SPI DRIVER"
 * =============================================== */
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn );

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn );

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn );

#endif /* MCAL_INC_STM32_F103C6_SPI_DRIVER_H_ */

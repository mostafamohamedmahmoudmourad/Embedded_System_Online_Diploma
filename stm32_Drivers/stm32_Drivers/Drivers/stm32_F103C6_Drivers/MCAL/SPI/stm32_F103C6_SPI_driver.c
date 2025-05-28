/*
 * stm32_F103C6_SPI_driver.c
 *
 *  Created on: 10 Oct 2024
 *  Author: Mostafa Mourad
 */


#include "../inc/stm32_F103C6_SPI_driver.h"

/* =====================================================================================
 * 							Generic Variables
 * ===================================================================================== */
SPI_Config_t* Global_SPI_Config[2] = {NULL,NULL};
SPI_Config_t  Global_SPI_Config1;
SPI_Config_t  Global_SPI_Config2;
/* =====================================================================================
 * 							Generic Macros
 * ===================================================================================== */
#define SPI1_INDEX    			0
#define SPI2_INDEX    			1
#define SPI_SR_TXE				((uint8_t)(0x02)) // Transmit Buffer is empty
#define SPI_SR_RXNE				((uint8_t)(0x01)) // Receive Buffer is not empty

/**=======================================================================================
 * @Fn			 -MCAL_SPI_Init
 * @brief 		 -Initialize SPI according to the specified parameters in SPI_Config
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]   -pointer to SPI_Config Structure that Contains the configuration information for All SPI.
 * Note			 -Support for SPI Full Duplex Master/Slave & NSS HW/SW
 * 				 -In Case of Master you have to Configure pin and drive it.
 =========================================================================================*/

void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config)
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0 ;
	uint16_t tmpreg_CR2 = 0 ;

	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config;
		Global_SPI_Config[SPI1_INDEX] = &Global_SPI_Config1;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_Config;
		Global_SPI_Config[SPI2_INDEX] = &Global_SPI_Config2;
		RCC_SPI2_CLK_EN();
	}

	//SPI_CR1. Bit 6 SPE: SPI enable
	tmpreg_CR1 = (1<<6);

	//Master or Slave
	tmpreg_CR1 |= SPI_Config->Device_Mode;

	//SPI_Communication_Mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode;

	//SPI_Frame_Format
	tmpreg_CR1 |= SPI_Config->Frame_Format;

	//SPI_DataSize
	tmpreg_CR1 |= SPI_Config->DataSize;

	//SPI_Clock_Polarity
	tmpreg_CR1 |= SPI_Config->CLKPolarity;

	//SPI_Clock_Phase
	tmpreg_CR1 |= SPI_Config->CLKPhase;

	//=======================NSS=====================
		//SPI_NSS SPI Slave Select Management
		if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Enable)
		{
			tmpreg_CR2 |= SPI_Config->NSS ;
		}
		else if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
		{
			tmpreg_CR2 &= SPI_Config->NSS ;
		}
		else
		{
			tmpreg_CR1 |= SPI_Config->NSS ;
		}
		//===============================================
		//SPI_BaudRatePrescaler
		tmpreg_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALER ;
		// Interrupt
		if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE )
		{
			// SPI_IRQ_Enable_define
			tmpreg_CR2 |= SPI_Config->IRQ_Enable ;
			if (SPIx == SPI1)
			{
				NVIC_IRQ35_SPI1_Enable;
			}
			else if (SPIx == SPI2)
			{
				NVIC_IRQ36_SPI2_Enable;
			}
		}
		SPIx->SPI_CR1 = tmpreg_CR1 ;
		SPIx->SPI_CR2 = tmpreg_CR2 ;

}

/**===============================================================================================
 * @Fn			 -MCAL_SPI_DeInit
 * @brief 		 -Reset SPI Registers and NVIC corresponding to IRQ Mask
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * ==============================================================================================*/
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI1)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}

/**======================================================================================================
 * @Fn			- MCAL_SPI_SendData
 * @brief 		- Send data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in] 	- pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 ======================================================================================================*/
void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE)) ;
	SPIx->SPI_DR = *pTxBuffer ;
}
/**===============================================================================================
 * @Fn			- MCAL_SPI_ReceiveData
 * @brief 		- Receive data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in] 	- pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 =================================================================================================*/
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;
	*pTxBuffer = SPIx->SPI_DR ;
}
/**==================================================================================================
 * @Fn			- MCAL_SPI_TX_RX
 * @brief 		- To transmit and receive data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]  - pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 ==================================================================================================*/
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE)) ;
	SPIx->SPI_DR = *pTxBuffer ;
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;
	*pTxBuffer = SPIx->SPI_DR ;
}
/**========================================================================================================
 * @Fn					- MCAL_SPI_GPIO_Set_Pins
 * @brief 				- Configure the pins as recommended in the data sheer
 * @param [in] 			- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 =========================================================================================================*/
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	GPIO_PinConfig_t Pin_Cfg;
	if(SPIx == SPI1)
	{
		// PA4 : NSS
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_Output_Disable :   // As input to sense if there are other masters
				// Hardware master /slave Input floating
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
				break;
			case SPI_NSS_Hard_Master_SS_Output_Enable:
				// Hardware master/ NSS output enabled Alternate function push-pull
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_4;
				Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
				break;
			}
			// PA5 : SCK
			// Master Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_5;
			Pin_Cfg.GPIO_Output_Speed= GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
			// PA6 : MISO
			// Full duplex / master Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);

			// PA7 : MOSI
			// Full duplex / master Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_7;
			Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}
		else
		{
			// Slave
			// PA4 : NSS
			// Just use NSS in case of it is configured as hardware
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				// Slave Input floating
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
			}
			// PA5 : SCK
			// Slave Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);


			// PA6 : MISO
			// Full duplex / slave (point to point) Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_6;
			Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
			// PA7 : MOSI
			// Full duplex / slave Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_INIT(GPIOA, &Pin_Cfg);
		}
	}
	else if(SPIx == SPI2)
	{
		// PB12 : NSS
		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{

			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_Output_Disable :   // As input to sense if there are other masters
				// Hardware master /slave Input floating
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
				break;
			case SPI_NSS_Hard_Master_SS_Output_Enable:
				// Hardware master/ NSS output enabled Alternate function push-pull
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_12;
				Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
				break;
			}
			// PB13 : SCK
			// Master Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_13;
			Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
			// PB14 : MISO
			// Full duplex / master Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
			// PB15 : MOSI
			// Full duplex / master Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_15;
			Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
		}
		else
		{   // Slave
			// PB12 : NSS
			// Just use NSS in case of it is configured as hardware
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				// Slave Input floating
				Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
				Pin_Cfg.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
			}
			// PB13 : SCK
			// Slave Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
			// PB14 : MISO
			// Full duplex / slave (point to point) Alternate function push-pull
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Output_AF_PP;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_14;
			Pin_Cfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
			// PB15 : MOSI
			// Full duplex / slave Input floating
			Pin_Cfg.GPIO_MODE = GPIO_MODE_Input_FLO;
			Pin_Cfg.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_INIT(GPIOB, &Pin_Cfg);
		}
	}
}
/* =====================================================================================
 * 							ISR Functions
 * ===================================================================================== */
void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE  = ( ( SPI1->SPI_SR  & (1<<1)) >> 1 ) ;
	irq_src.RXNE = ( ( SPI1->SPI_SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI1->SPI_SR  & (1<<4)) >> 4 ) ;
	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE  = ( ( SPI1->SPI_SR  & (1<<1)) >> 1 ) ;
	irq_src.RXNE = ( ( SPI1->SPI_SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI1->SPI_SR  & (1<<4)) >> 4 ) ;
	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_src);
}


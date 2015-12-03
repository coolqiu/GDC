/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Hardware Configuration & Setup.
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "hw_config.h"
#include "stm32f3_discovery.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
RCC_ClocksTypeDef RCC_Clocks;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef        NVIC_InitStructure;

#define RCC_AHBPeriph_ALLGPIO                 (RCC_AHBPeriph_GPIOA \
                                              | RCC_AHBPeriph_GPIOB \
                                              | RCC_AHBPeriph_GPIOC \
                                              | RCC_AHBPeriph_GPIOD \
                                              | RCC_AHBPeriph_GPIOE \
                                              | RCC_AHBPeriph_GPIOF )

/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;

/**
  * @brief  Configures Main system clocks & power.
  * @param  None
  * @retval None
  */
void Set_System(void)
{
  
	
 /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Enable the SYSCFG module clock (used for the USB disconnect feature) */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Enable the USB disconnect GPIO clock */
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIO_DISCONNECT, ENABLE);

  /* Configure the Key button in EXTI mode */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
  
  /* Configure the EXTI line 18 connected internally to the USB IP */
	/*
  EXTI_ClearITPendingBit(EXTI_Line18);
  EXTI_InitStructure.EXTI_Line = EXTI_Line18; //USB resume from suspend mode
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); */
 
  EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
	systick_init(100); // every  10 ms 
 	GPIO_Config();
	USART_1_5_Config();
}


/**
  * @brief  Configures all IOs .
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  //Enable all GPIOs Clock
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, ENABLE); 
	/* Disable all GPIOs Clock*/
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, DISABLE); 
	
  /* Configure all GPIO port pins */
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// GPIO A
	//Внимание !!!  на РА14 и РА13 подключен по SWD отладчик !
	//РА14 и РА15 не инициализировать.
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All-GPIO_Pin_13-GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	//Alternate function to USART2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
	//SYS CLK to PA8 pin
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //GPIO B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//GPIO C
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//*SET PC4,5 for UART1
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_7);
	//*SET PC10,11 for UART4
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_5);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_5);
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//GPIO D
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOD, &GPIO_InitStructure);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//GPIO E
	//PE8-15   leds 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8+GPIO_Pin_9+GPIO_Pin_10+GPIO_Pin_11+GPIO_Pin_12+GPIO_Pin_13+GPIO_Pin_14+GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}

void USART_1_5_Config(void)
{
	
	USART_InitTypeDef USART_InitStructure ;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	USART_ClockStructInit( &USART_ClockInitStructure );
	// USART1 init +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
  /* USART1 configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
	
	USART_ClockInit( USART1, &USART_ClockInitStructure );
	
  USART_InitStructure.USART_BaudRate = 19200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
	
  USART_Init(USART1, &USART_InitStructure);   
	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // приоритет
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // приоритет субгруппы
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // включаем канал
  NVIC_Init( &NVIC_InitStructure );                           // инициализируем
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART1, USART_IT_TC, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_WU, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_CM, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_EOB, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_RTO, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_PE, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
	USART_ITConfig(USART1, USART_IT_LBD, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_CTS, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_ERR, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_ORE, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_NE, 	DISABLE);
	USART_ITConfig(USART1, USART_IT_FE, 	DISABLE);
  USART_Cmd(USART1, ENABLE); 
	//NVIC_EnableIRQ(USART1_IRQn);
	//USART_OverSampling8Cmd(ENABLE);  
  //USART_OneBitMethodCmd(ENABLE); 
  //USART_HalfDuplexCmd (ENABLE); 
	
// USART2 init ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
  /* USART2 
	default ude for MAVLink interface configured as follow:
  - BaudRate = 57600 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
	USART_ClockStructInit( &USART_ClockInitStructure );
	USART_ClockInit( USART2, &USART_ClockInitStructure );
	
  USART_InitStructure.USART_BaudRate = 57600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	
  USART_Init(USART2, &USART_InitStructure);   
	//USART_SetReceiverTimeOut(USART2, 24);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // приоритет
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // приоритет субгруппы
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // включаем канал
  
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART2, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART2, USART_IT_TC,   DISABLE);
	USART_ITConfig(USART2, USART_IT_WU,   DISABLE);
	USART_ITConfig(USART2, USART_IT_CM,   DISABLE);
	USART_ITConfig(USART2, USART_IT_EOB,  DISABLE);
	USART_ITConfig(USART2, USART_IT_RTO,  DISABLE);
	USART_ITConfig(USART2, USART_IT_PE,   DISABLE);
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);
	USART_ITConfig(USART2, USART_IT_LBD,  DISABLE);
	USART_ITConfig(USART2, USART_IT_CTS,  DISABLE);
	USART_ITConfig(USART2, USART_IT_ERR,  DISABLE);
	USART_ITConfig(USART2, USART_IT_ORE,  DISABLE);
	USART_ITConfig(USART2, USART_IT_NE,   DISABLE);
	USART_ITConfig(USART2, USART_IT_FE,   DISABLE);
  USART_Cmd(USART2, ENABLE);

NVIC_Init( &NVIC_InitStructure );   	// инициализируем

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
// USART3 init ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  /* USART3 configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
	USART_ClockStructInit( &USART_ClockInitStructure );
	USART_ClockInit( USART3, &USART_ClockInitStructure );
	
  USART_InitStructure.USART_BaudRate = 250000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	
  USART_Init(USART3, &USART_InitStructure);   
	//USART_SetReceiverTimeOut(USART3, 24);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // приоритет
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // приоритет субгруппы
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // включаем канал
  
  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART3, USART_IT_TXE,  DISABLE);
  USART_ITConfig(USART3, USART_IT_TC,   DISABLE);
	USART_ITConfig(USART3, USART_IT_WU,   DISABLE);
	USART_ITConfig(USART3, USART_IT_CM,   DISABLE);
	USART_ITConfig(USART3, USART_IT_EOB,  DISABLE);
	USART_ITConfig(USART3, USART_IT_RTO,  DISABLE);
	USART_ITConfig(USART3, USART_IT_PE,   DISABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);
	USART_ITConfig(USART3, USART_IT_LBD,  DISABLE);
	USART_ITConfig(USART3, USART_IT_CTS,  DISABLE);
	USART_ITConfig(USART3, USART_IT_ERR,  DISABLE);
	USART_ITConfig(USART3, USART_IT_ORE,  DISABLE);
	USART_ITConfig(USART3, USART_IT_NE,   DISABLE);
	USART_ITConfig(USART3, USART_IT_FE,   DISABLE);
  USART_Cmd(USART3, ENABLE);

NVIC_Init( &NVIC_InitStructure );   	// инициализируем

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
// UART4 init ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

  /* UART4 configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabledg
  */
	USART_ClockStructInit( &USART_ClockInitStructure );
	USART_ClockInit( UART4, &USART_ClockInitStructure );
	
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
  USART_InitStructure.USART_StopBits = USART_StopBits_1; 
  USART_InitStructure.USART_Parity = USART_Parity_No; 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	
  USART_Init(UART4, &USART_InitStructure);   
	USART_SetReceiverTimeOut(UART4, 32);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;           // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   // приоритет
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // приоритет субгруппы
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             // включаем канал
  
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_ITConfig(UART4, USART_IT_TXE,  DISABLE);
  USART_ITConfig(UART4, USART_IT_TC,   DISABLE);
	USART_ITConfig(UART4, USART_IT_WU,   DISABLE);
	USART_ITConfig(UART4, USART_IT_CM,   DISABLE);
	USART_ITConfig(UART4, USART_IT_EOB,  DISABLE);
	USART_ITConfig(UART4, USART_IT_RTO,  DISABLE);
	USART_ITConfig(UART4, USART_IT_PE,   DISABLE);
	USART_ITConfig(UART4, USART_IT_IDLE, DISABLE);
	USART_ITConfig(UART4, USART_IT_LBD,  DISABLE);
	USART_ITConfig(UART4, USART_IT_CTS,  DISABLE);
	USART_ITConfig(UART4, USART_IT_ERR,  DISABLE);
	USART_ITConfig(UART4, USART_IT_ORE,  DISABLE);
	USART_ITConfig(UART4, USART_IT_NE,   DISABLE);
	USART_ITConfig(UART4, USART_IT_FE,   DISABLE);
  USART_Cmd(UART4, ENABLE);

NVIC_Init( &NVIC_InitStructure );   	// инициализируем

 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
}
/* SysTick end of count event each 10ms if divider = 100 */
void systick_init (uint16_t divider){
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / divider);
}
void Leds_init (void){
 /* Initialize LEDs and User Button available on STM32F3-Discovery board */
  STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);	
	STM_EVAL_LEDInit(LED8);
	
  //STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 
  /* Reset UserButton_Pressed variable */
  //UserButtonPressed = 0x00; 
		
	/* LEDs Off */
  STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
	STM_EVAL_LEDOff(LED8);
}	

/**
  * @brief  Power-off system clocks and power while entering suspend mode.
  * @param  None
  * @retval None
  */
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
 // bDeviceState = SUSPENDED;
  /* Clear EXTI Line18 pending bit */
  EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
} 

/**
  * @brief  Restores system clocks and power while exiting suspend mode.
  * @param  None
  * @retval None
  */
void Leave_LowPowerMode(void)
{
//  DEVICE_INFO *pInfo = &Device_Info;

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();


  /* Wait till HSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
  {}
   
  /* Enable PLL1 */
  RCC_PLLCmd(ENABLE);

  /* Wait till PLL1 is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}

  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

  /* Wait till PLL is used as system clock source */ 
  while (RCC_GetSYSCLKSource() != 0x08)
  {}  

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 

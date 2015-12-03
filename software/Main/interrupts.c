/**
  ******************************************************************************
  * @file    stm32f30x_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x_it.h"
#include "main.h"
#include "suncti_m500.h"
#include "alexmos32.h"

//#include "usb_istr.h"

/** @addtogroup STM32F3-Discovery_Demo
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t i =0;
extern __IO uint32_t UserButtonPressed;
extern __IO uint8_t DataReady;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


void SysTick_Handler(void)
{
  TimingDelay_Decrement();
//  USBConnectTimeOut--;
  DataReady ++;
	heartbeat_sending_timer++;
	target_coordinate_sending_timer++;
	alex_mos_getting_angles_timer++;
	alex_mos_sending_control_timer++;
	usart_4_not_busy_delay_timer++;
  system_time += 10;
  time_boot += 10;
	if(flash_saving_timer!=0xff)
	{
		flash_saving_timer++;
		if(flash_saving_timer == flash_save_interval)
			write_params_to_flash();
	}
}

/******************************************************************************/
/*                 STM32F30x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f30x.s).                                            */
/******************************************************************************/
/**
  * @brief  This function handles EXTI0_IRQ Handler.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{ 
  if ((EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) == SET)&&(STM_EVAL_PBGetState(BUTTON_USER) != RESET))
  {
    /* Delay */
    for(i=0; i<0x7FFFF; i++);
    
    /* Wait for SEL button to be pressed  */
    while(STM_EVAL_PBGetState(BUTTON_USER) != RESET); 
    /* Delay */
    for(i=0; i<0x7FFFF; i++);
    UserButtonPressed++;
    
    if (UserButtonPressed > 0x2)
    {
      UserButtonPressed = 0x0;
    }
    
    /* Clear the EXTI line pending bit */
    EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
  }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------USART1---------USART1--------USART1---------USART1--------USART1---------USART1--------USART1-
void USART1_IRQHandler()
{
	uint8_t temp_rx_data,temp_tx_data,escape_flag=0;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//USART1 NOT EMPTY RECIVER REGISTER INTERRUPT
	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		temp_rx_data= USART_ReceiveData(USART1);
		switch (temp_rx_data)
		{
			case 0xf0:
			{
			suncti_m500_rxindex=0;
			suncti_m500_new_message_recived =0;
			break;
			}
			case 0xf5:
			{
			escape_flag=0xff;
			break;
			}
			case 0xff:
			{
			suncti_m500_rxindex=0;
			suncti_m500_new_message_recived =0xff;	
			}
			default :
			{
				if(escape_flag)
					{
						temp_rx_data|=0xf0;
						escape_flag  =0x00;
					}
				suncti_m500_rx_buffer[suncti_m500_rxindex] = temp_rx_data;
				suncti_m500_rxindex++;
				if(suncti_m500_rxindex > 13)suncti_m500_rxindex=13; 
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//USART1 EMPTY TRANSMITTER REGISTER INTERRUPT
	
	if (USART_GetITStatus(USART1, USART_IT_TXE))
	{
		if(suncti_m500_txindex<suncti_m500_txdata_length)
		{	
			temp_tx_data = suncti_m500_tx_buffer[suncti_m500_txindex];
			
			if(!((suncti_m500_txindex==0)||(suncti_m500_txindex==suncti_m500_txdata_length-1)))// Если это не начало или не конец пакета
				{	
					if ((suncti_m500_tx_buffer[suncti_m500_txindex]==0xF0)||// Обработка исключающих валидность протокола даных
							(suncti_m500_tx_buffer[suncti_m500_txindex]==0xFF)||
							(suncti_m500_tx_buffer[suncti_m500_txindex]==0xF5))
						{
							suncti_m500_tx_buffer[suncti_m500_txindex]=	suncti_m500_tx_buffer[suncti_m500_txindex]&~0xf0;
							temp_tx_data = 0xf5;
							suncti_m500_txindex--;
						}
				}

			suncti_m500_txindex++;
			suncti_m500_message_sended = 0x00;
			USART_SendData(USART1 , temp_tx_data);
		}
		else 
		{
			suncti_m500_txindex = 0x00;
			suncti_m500_message_sended = 0xff;
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//USART1 TRANSMIT COMPLETE INTERRUPT
	if (USART_GetITStatus(USART1, USART_IT_TC))
	{
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);	
		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//USART1
	if (USART_GetITStatus(USART1, USART_IT_WU))
		{
		USART_ITConfig(USART1, USART_IT_WU, DISABLE);	
		USART_ClearITPendingBit(USART1, USART_IT_WU);			
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART2, USART_IT_CM))
		{
		USART_ITConfig(USART1, USART_IT_CM, DISABLE);	
		USART_ClearITPendingBit(USART1, USART_IT_CM);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART1, USART_IT_EOB))
		{
		USART_ITConfig(USART1, USART_IT_EOB, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_EOB);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USART1 Reciver time out interrupt
	if (USART_GetITStatus(USART1, USART_IT_RTO))
		{
		USART_ITConfig(USART1, USART_IT_RTO, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_RTO);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART1, USART_IT_PE))
		{
		USART_ITConfig(USART1, USART_IT_PE, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_PE);				
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_IDLE ))
	{
		USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_IDLE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_LBD))
	{
		USART_ITConfig(USART1, USART_IT_LBD, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_LBD);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_CTS))
	{
		USART_ITConfig(USART1, USART_IT_CTS, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_CTS);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_ERR))
	{
		USART_ITConfig(USART1, USART_IT_ERR, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_ERR);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_ORE))
	{
		USART_ITConfig(USART1, USART_IT_ORE, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_ORE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_NE))
	{	
		USART_ITConfig(USART1, USART_IT_NE, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_NE);			
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART1, USART_IT_FE))
	{
		USART_ITConfig(USART1, USART_IT_FE, DISABLE);
		USART_ClearITPendingBit(USART1, USART_IT_FE);			
	};	
	
USART_ClearITPendingBit(USART1, USART_IT_ORE);		
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//USART2---------USART2---------USART2--------USART2---------USART2--------USART2---------USART2--------
void USART2_IRQHandler()
{
	volatile uint8_t temp_rx_data;

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART2, USART_IT_WU))
		{
		USART_ITConfig(USART2, USART_IT_WU, DISABLE);	
		USART_ClearITPendingBit(USART2, USART_IT_WU);			
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART2, USART_IT_CM))
		{
		USART_ITConfig(USART2, USART_IT_CM, DISABLE);	
		USART_ClearITPendingBit(USART2, USART_IT_CM);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART2, USART_IT_EOB))
		{
		USART_ITConfig(USART2, USART_IT_EOB, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_EOB);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USART2 Reciver time out interrupt
	if (USART_GetITStatus(USART2, USART_IT_RTO))
		{
		USART_ITConfig(USART2, USART_IT_RTO, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_RTO);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART2, USART_IT_PE))
		{
		USART_ITConfig(USART2, USART_IT_PE, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_PE);				
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USART2 EMPTY TRANSMITTER REGISTER INTERRUPT
if (USART_GetITStatus(USART2, USART_IT_TXE))
	{
		if(USART2_words_to_send > USART2_current_TX_word)
		{
			USART_SendData(USART2 ,USART2_TX_bufer[USART2_current_TX_word]);
			USART2_current_TX_word++;
		}
		else 
		{
			USART2_words_to_send=0;
			USART2_current_TX_word=0;
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
	}	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USART2 TRANSMIT COMPLETE INTERRUPT
if (USART_GetITStatus(USART2, USART_IT_TC))
	{
		
		USART_ITConfig(USART2, USART_IT_TC, DISABLE);	
		USART_ClearITPendingBit(USART2, USART_IT_TC);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USART2 NOT EMPTY RECIVER REGISTER INTERRUPT
if (USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		temp_rx_data = USART_ReceiveData(USART2);
		if(mavlink_parse_char(MAVLINK_COMM_0, temp_rx_data, &msg, &status)) 
			{
				new_mavlink_message_recived_via_usrt2_flag=0xff;
			}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_IDLE ))
	{
		USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_LBD))
	{
		USART_ITConfig(USART2, USART_IT_LBD, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_LBD);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_CTS))
	{
		USART_ITConfig(USART2, USART_IT_CTS, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_CTS);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_ERR))
	{
		USART_ITConfig(USART2, USART_IT_ERR, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_ERR);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_ORE))
	{
		USART_ITConfig(USART2, USART_IT_ORE, DISABLE);
		USART_ClearITPendingBit(USART2, USART_IT_ORE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_NE))
	{	
USART_ITConfig(USART2, USART_IT_NE, DISABLE);
USART_ClearITPendingBit(USART2, USART_IT_NE);			
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(USART2, USART_IT_FE))
	{
USART_ITConfig(USART2, USART_IT_FE, DISABLE);
USART_ClearITPendingBit(USART2, USART_IT_FE);			
	};	
	
	USART_ClearITPendingBit(USART2, USART_IT_ORE);		

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
//USART3---------USART3---------USART3---------USART3---------USART3---------USART3---------USART3---------
void USART3_IRQHandler()
{

	volatile uint8_t temp_rx_data;
	if (USART_GetITStatus(USART3, USART_IT_WU))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_CM))
		{

		};
	if (USART_GetITStatus(USART3, USART_IT_EOB))
		{
	
		};
	if (USART_GetITStatus(USART3, USART_IT_RTO))
		{
		
		};
	if (USART_GetITStatus(USART3, USART_IT_PE))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_TXE))
		{
	
		};	
	if (USART_GetITStatus(USART3, USART_IT_TC))
		{
		
		};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
if (USART_GetITStatus(USART3, USART_IT_RXNE))
	{
	temp_rx_data = USART_ReceiveData(USART3);
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	USART_ClearFlag        (USART3, USART_IT_RXNE);
	};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(USART3, USART_IT_IDLE ))
		{
	
		};
	if (USART_GetITStatus(USART3, USART_IT_LBD))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_CTS))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_ERR))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_ORE))
		{
			
		};
	if (USART_GetITStatus(USART3, USART_IT_NE))
		{	
			
		};
	if (USART_GetITStatus(USART3, USART_IT_FE))
		{
			
		};	
}

//UART4---------UART4---------UART4--------UART4---------UART4--------UART4---------UART4--------
void UART4_IRQHandler()
{
	volatile uint8_t temp_rx_data;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART4, USART_IT_WU))
		{
		USART_ITConfig(UART4, USART_IT_WU, DISABLE);	
		USART_ClearITPendingBit(UART4, USART_IT_WU);			
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART4, USART_IT_CM))
		{
		USART_ITConfig(UART4, USART_IT_CM, DISABLE);	
		USART_ClearITPendingBit(UART4, USART_IT_CM);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART4, USART_IT_EOB))
		{
		USART_ITConfig(UART4, USART_IT_EOB, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_EOB);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART4 Reciver time out interrupt
	if (USART_GetITStatus(UART4, USART_IT_RTO))
		{
			alex_rx_msg.alex_mos_parsing_state  = -1;
			alex_rx_msg.alex_mos_parsing_step   = 0;
			alex_rx_msg.alex_mos_parsing_steps  = ALEX_MOS_MAX_PACKET_LEN;			
			USART_ClearITPendingBit(UART4, USART_IT_RTO);
			USART_ITConfig(UART4, USART_IT_RTO, DISABLE);
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART4, USART_IT_PE))
		{
		USART_ITConfig(UART4, USART_IT_PE, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_PE);				
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART4 EMPTY TRANSMITTER REGISTER INTERRUPT
		volatile static uint16_t current_tx_index_uart4;
		//volatile uint16_t words_to_send;
if (USART_GetITStatus(UART4, USART_IT_TXE))
	{ 
		if(current_tx_index_uart4 < pointer_to_char_uart4[0])
		{ 
			UART4_not_bysy=0x00;
			current_tx_index_uart4 ++;
			USART_SendData(UART4 , pointer_to_char_uart4[current_tx_index_uart4]);
			//UART4->TDR = pointer_to_char_uart4[current_tx_index_uart4];//(Data & (uint16_t)0x01FF);
			usart_4_not_busy_delay_timer =0;
		}
		else 
		{
			current_tx_index_uart4=0;		
			USART_ITConfig(UART4, USART_IT_TXE, DISABLE);	
			
		}
		
		USART_ClearITPendingBit(UART4, USART_IT_TXE);
	}	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART4 TRANSMIT COMPLETE INTERRUPT
if (USART_GetITStatus(UART4, USART_IT_TC))
	{
		USART_ITConfig(UART4, USART_IT_TC, DISABLE);	
		USART_ClearITPendingBit(UART4, USART_IT_TC);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART4 NOT EMPTY RECIVER REGISTER INTERRUPT
if (USART_GetITStatus(UART4, USART_IT_RXNE))
	{ 
		temp_rx_data = USART_ReceiveData(UART4);
		if(alex_mos_parse_char(temp_rx_data, &alex_rx_msg)) 
			{
				new_alex_mos_message_recived=0xff;
			}
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		USART_ITConfig(UART4, USART_IT_RTO, ENABLE);
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_IDLE ))
	{
		USART_ITConfig(UART4, USART_IT_IDLE, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_IDLE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_LBD))
	{
		USART_ITConfig(UART4, USART_IT_LBD, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_LBD);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_CTS))
	{
		USART_ITConfig(UART4, USART_IT_CTS, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_CTS);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_ERR))
	{
		USART_ITConfig(UART4, USART_IT_ERR, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_ERR);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_ORE))
	{
		USART_ITConfig(UART4, USART_IT_ORE, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_ORE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_NE))
	{	
		USART_ITConfig(UART4, USART_IT_NE, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_NE);			
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART4, USART_IT_FE))
	{
		USART_ITConfig(UART4, USART_IT_FE, DISABLE);
		USART_ClearITPendingBit(UART4, USART_IT_FE);			
	};	
	
	USART_ClearITPendingBit(UART4, USART_IT_ORE);		

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
//UART5---------UART5---------UART5--------UART5---------UART5--------UART5---------UART5--------
void UART5_IRQHandler()
{
	volatile uint8_t temp_rx_data;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART5, USART_IT_WU))
		{
		USART_ITConfig(UART5, USART_IT_WU, DISABLE);	
		USART_ClearITPendingBit(UART5, USART_IT_WU);			
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART5, USART_IT_CM))
		{
		USART_ITConfig(UART5, USART_IT_CM, DISABLE);	
		USART_ClearITPendingBit(UART5, USART_IT_CM);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART5, USART_IT_EOB))
		{
		USART_ITConfig(UART5, USART_IT_EOB, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_EOB);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART5 Reciver time out interrupt
	if (USART_GetITStatus(UART5, USART_IT_RTO))
		{
		USART_ITConfig(UART5, USART_IT_RTO, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_RTO);	
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (USART_GetITStatus(UART5, USART_IT_PE))
		{
		USART_ITConfig(UART5, USART_IT_PE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_PE);				
		};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART5 EMPTY TRANSMITTER REGISTER INTERRUPT
if (USART_GetITStatus(UART5, USART_IT_TXE))
	{
		USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_TXE);
	}	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART5 TRANSMIT COMPLETE INTERRUPT
if (USART_GetITStatus(UART5, USART_IT_TC))
	{
		USART_ITConfig(UART5, USART_IT_TC, DISABLE);	
		USART_ClearITPendingBit(UART5, USART_IT_TC);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//UART5 NOT EMPTY RECIVER REGISTER INTERRUPT
if (USART_GetITStatus(UART5, USART_IT_RXNE))
	{
		temp_rx_data = USART_ReceiveData(UART5);
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_IDLE ))
	{
		USART_ITConfig(UART5, USART_IT_IDLE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_IDLE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_LBD))
	{
		USART_ITConfig(UART5, USART_IT_LBD, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_LBD);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_CTS))
	{
		USART_ITConfig(UART5, USART_IT_CTS, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_CTS);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_ERR))
	{
		USART_ITConfig(UART5, USART_IT_ERR, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_ERR);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_ORE))
	{
		USART_ITConfig(UART5, USART_IT_ORE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_ORE);	
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_NE))
	{	
		USART_ITConfig(UART5, USART_IT_NE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_NE);			
	};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if (USART_GetITStatus(UART5, USART_IT_FE))
	{
		USART_ITConfig(UART5, USART_IT_FE, DISABLE);
		USART_ClearITPendingBit(UART5, USART_IT_FE);			
	};	
	USART_ClearITPendingBit(UART5, USART_IT_ORE);		

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/****************************END OF FILE********************************************************************/





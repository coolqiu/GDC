#include "suncti_m500.h"
#include "main.h"
uint32_t suncti_m500_status;
uint8_t suncti_m500_txdata_length;
uint8_t suncti_m500_message_sended = 0xff;
uint8_t suncti_m500_new_message_recived = 0;
uint8_t suncti_m500_rxindex = 0;
uint8_t suncti_m500_txindex = 0;
uint8_t suncti_m500_rx_buffer[14];
uint8_t suncti_m500_tx_buffer[14];

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void suncti_m500_send_command(uint8_t command , uint16_t data1 , uint16_t data2)
{
	if(suncti_m500_message_sended) 
	{
	suncti_m500_tx_buffer[0] = suncti_m500_starting_mark;
  suncti_m500_tx_buffer[2] = suncti_m500_device_adres;
	
	switch (command)
	{
		case suncti_m500_Command_Status_enquiry :
		case suncti_m500_Command_Video_contrast_increase_setting :	
		case suncti_m500_Command_Video_contrast_decrease_setting :
		case suncti_m500_Command_Video_brightness_increase_setting :	
		case suncti_m500_Command_Video_brightness_decrease_setting :	
		case suncti_m500_Command_System_reset :	
		case suncti_m500_Command_Save_cursor_position :	
		{
			suncti_m500_tx_buffer[1] = 0x02;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = suncti_get_checksum ();
			suncti_m500_tx_buffer[5] = suncti_m500_trailing_flag;
			break;
		}
		case suncti_m500_Command_Polarity_setting : 
		{
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			
			// Error checking of data
			if (!((data1 == 0x00)||(data1 == 0x0F)))
			{
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
				goto exit_this_function;
			}
			break;
		}
		case suncti_m500_Command_Zoom_in : 
		{
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			
			// Error checking of data
			if (!((data1 == 0x00)||(data1 == 0x02)||(data1 == 0x04)))
			{
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
				goto exit_this_function;
			}
			
			break;
		}
		case suncti_m500_Command_Auto_mode_setting : 
		{
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			
			// Error checking of data
			if (!((data1 == 0x01)||(data1 == 0x02)))
			{
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
				goto exit_this_function;
			}
			break;
		}
		case suncti_m500_Command_Video_contrast_setting : 
		case suncti_m500_Command_Video_brightness_setting :
		{
			// Error checking of data
			if (data1 > 0x64)
			{
				data1=0x64;
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
			}
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			break;
		}
		
		case suncti_m500_Command_Image_mirror :	
		{
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			
			// Error checking of data
			if (data1 > 0x03)
			{
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
				goto exit_this_function;
			}
			break;
		}		
		case suncti_m500_Command_Cursor_display_hide :	
		{
			suncti_m500_tx_buffer[1] = 0x03;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			suncti_m500_tx_buffer[4] = data1;
			suncti_m500_tx_buffer[5] = suncti_get_checksum();
			suncti_m500_tx_buffer[6] = suncti_m500_trailing_flag;
			
			// Error checking of data
			if (!((data1 == 0x00)||(data1 == 0x01)))
			{
				suncti_m500_rx_buffer[1] = suncti_m500_error_bed_data_not_sended;
				goto exit_this_function;
			}
			break;
		}
		case suncti_m500_Command_Cursor_move_X :
		case suncti_m500_Command_Cursor_move_Y :	
		{
			suncti_m500_tx_buffer[1] = 0x04;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			if(data1 > 0xff)suncti_m500_tx_buffer[4] = 0x01;
			else 						suncti_m500_tx_buffer[4] = 0x00;
			suncti_m500_tx_buffer[5] = (char)data1;
			suncti_m500_tx_buffer[suncti_m500_txdata_length-2]   = suncti_get_checksum();
			suncti_m500_tx_buffer[suncti_m500_txdata_length-1]   = suncti_m500_trailing_flag;
			break;
		}
		case suncti_m500_Command_Cursor_move_X_Y :	
		{
			suncti_m500_tx_buffer[1] = 0x06;
			suncti_m500_txdata_length = suncti_m500_tx_buffer[1] + 0x04;
			suncti_m500_tx_buffer[3] = command;
			if(data1 > 0xff)suncti_m500_tx_buffer[4] = 0x01;
			else 						suncti_m500_tx_buffer[4] = 0x00;
			suncti_m500_tx_buffer[5] = (char)data1;
			if(data2 > 0xff)suncti_m500_tx_buffer[6] = 0x01;
			else 						suncti_m500_tx_buffer[6] = 0x00;
			suncti_m500_tx_buffer[7] = (char)data2;
			suncti_m500_tx_buffer[suncti_m500_txdata_length-1]   = suncti_get_checksum();
			suncti_m500_tx_buffer[suncti_m500_txdata_length] = suncti_m500_trailing_flag;
			break;
		}
    default :	
		{ //Если такой команды не существует - выход без инициации передачи
			suncti_m500_rx_buffer[1] = suncti_m500_error_bed_command_not_sended;
			goto exit_this_function;
		}
	}
	
	
	
	
		//USART_ClearFlag(USART1, USART_FLAG_TXE );
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	
exit_this_function : ;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint8_t suncti_get_checksum (void)
{
	uint8_t i;
	uint16_t  suncti_m500_cummulative_cheksum =0;
	for (i=2;i<suncti_m500_txdata_length-2;i++)
	{
		suncti_m500_cummulative_cheksum += suncti_m500_tx_buffer[i];
	}
	return ((uint8_t)suncti_m500_cummulative_cheksum);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t suncti_m500_get_error(void)
{
	return (suncti_m500_rx_buffer[1]);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t suncti_m500_get_status(void)
{
	return (suncti_m500_rx_buffer[2]);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t suncti_m500_get_contrast(void)
{
	return (suncti_m500_rx_buffer[3]);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t suncti_m500_get_brightness(void)
{
	return (suncti_m500_rx_buffer[4]);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int8_t suncti_chek_status(void)
{ 
	uint32_t starting_time = time_boot,t2;
	
	while(suncti_m500_message_sended ==0x00 && time_boot < (starting_time + 1000));
	suncti_m500_new_message_recived =0;
	starting_time = time_boot;
	while (suncti_m500_new_message_recived == 0x00 && time_boot < (starting_time + 5000)){
	 suncti_m500_send_command(suncti_m500_Command_Status_enquiry, 0 , 0);
		t2 = time_boot;
		while(time_boot < t2+500);
	}
	if(suncti_m500_new_message_recived) {
		suncti_m500_new_message_recived=0;
		starting_time = time_boot;
		while(suncti_m500_message_sended ==0x00 && time_boot < (starting_time + 2000));
		return suncti_m500_get_status();
	}
	else {
		suncti_m500_new_message_recived=0;
		suncti_m500_message_sended = 0xff;
		suncti_m500_rxindex = 0;
		suncti_m500_txindex = 0;
		return (-1);
	}
}

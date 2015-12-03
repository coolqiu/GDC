#ifndef __SUNCTI_M500_H
#define __SUNCTI_M500_H
#include "stm32f30x.h"
/*
uint32_t suncti_m500_status;
uint8_t suncti_m500_txdata_length;
uint8_t suncti_m500_message_sended ;
uint8_t suncti_m500_new_message_recived ;
uint8_t suncti_m500_rxindex;
uint8_t suncti_m500_txindex;
uint8_t suncti_m500_rx_buffer[8];
uint8_t suncti_m500_tx_buffer[14];
*/
// Настройки USARTа для камерного интерфейса
#define suncti_m500_baud_rate 		19200
#define suncti_m500_stop_bit 			USART_StopBits_1
#define suncti_m500_parity 				USART_Parity_No
#define suncti_m500_data_length 	USART_WordLength_8b
// Маркеры , адреса , флаги
#define suncti_m500_starting_mark 																		0xf0
#define suncti_m500_trailing_flag 																		0xff
#define suncti_m500_device_adres  																		0x26
// Команды для камеры
#define suncti_m500_Command_Status_enquiry														0x00
#define suncti_m500_Command_Polarity_setting 													0x01
#define suncti_m500_Command_Zoom_in																		0x02
#define suncti_m500_Command_Auto_mode_setting													0x03
#define suncti_m500_Command_Video_contrast_setting										0x04
#define suncti_m500_Command_Video_contrast_increase_setting						0x05
#define suncti_m500_Command_Video_contrast_decrease_setting						0x06
#define suncti_m500_Command_Image_mirror															0x07
#define suncti_m500_Command_Video_brightness_setting									0x09
#define suncti_m500_Command_Video_brightness_increase_setting					0x0A
#define suncti_m500_Command_Video_brightness_decrease_setting					0x0B
#define suncti_m500_Command_Cursor_display_hide												0x0C
#define suncti_m500_Command_Cursor_move_X															0x0D
#define suncti_m500_Command_Cursor_move_Y															0x0E
#define suncti_m500_Command_Cursor_move_X_Y														0x0F
#define suncti_m500_Command_Save_cursor_position											0x10
#define suncti_m500_Command_System_reset															0x80
// Ответные команды камеры камеры
#define suncti_m500_error_no_error  																	0x00
#define suncti_m500_error_check_code																	0x01
#define suncti_m500_error_bad_command																	0x02
#define suncti_m500_error_file_error																	0x03
#define suncti_m500_error_communication_interval											0x04
#define suncti_m500_error_packet_format_error													0x05
#define suncti_m500_error_bed_command_not_sended											0x06
#define suncti_m500_error_bed_data_not_sended													0x07

extern uint32_t suncti_m500_status;
extern uint8_t suncti_m500_txdata_length;
extern uint8_t suncti_m500_message_sended ;
extern uint8_t suncti_m500_new_message_recived ;
extern uint8_t suncti_m500_rxindex ;
extern uint8_t suncti_m500_txindex ;
extern uint8_t suncti_m500_rx_buffer[14];
extern uint8_t suncti_m500_tx_buffer[14];
uint8_t suncti_get_checksum (void);
void suncti_m500_send_command(uint8_t , uint16_t , uint16_t);
uint8_t suncti_m500_get_error(void);
int8_t suncti_chek_status(void);
#endif

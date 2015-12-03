#include "stm32f30x.h"
#include <stdint.h>
#include "mavlink.h"
#ifndef __MAV_STATE_H__
#define __MAV_STATE_H__
extern mavlink_gps_status_t gps_status;
extern mavlink_system_t mavlink_system;
extern mavlink_attitude_t CurrentAttitude;
extern mavlink_global_position_int_t current_GPS_data;
extern mavlink_mount_control_t mount_control;
/* MAVLINK VARIABLES SECTION	*/
extern mavlink_message_t msg;
extern mavlink_status_t status;
extern  uint8_t USART2_RX_bufer[];
extern __IO uint8_t USART2_words_to_recive;
extern __IO uint8_t USART2_current_RX_word;

extern  uint8_t USART2_TX_bufer[];
extern __IO uint8_t USART2_current_TX_word;
extern __IO uint8_t USART2_words_to_send;

extern __IO uint16_t  mav_tx_len;
extern __IO uint16_t heartbeat_sending_timer; //Heartbeat timer init
extern __IO uint16_t target_coordinate_sending_timer;
extern __IO uint8_t new_mavlink_message_recived_via_usrt2_flag;
/* MAVLINK VARIABLES SECTION END 																							*/


//extern GPS_data current_GPS_data;
void sort_mavlink_message(void);
void send_heart_beat_if_its_need(void);	
void send_target_gimbal_coordinates_if_its_need(void);
void	MAVLink_init(void);
void load_sending_intervals_from_parameters(void);
void send_gps_global_position_int_if_its_need (void);
#endif

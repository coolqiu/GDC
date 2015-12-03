#ifndef __alex_mos32_h__
#define __alex_mos32_h__
#include <stdint.h>
#include "math.h"
#define alex_mos_getting_angles_interval 20 // every 200mSec
#define alex_mos_sending_control_interval 20 //Êîæíèõ 200 ì1ë1ñåêóíä
#define usart_4_not_busy_delay_interval 2  //Êîæíèõ 20 ì1ë1ñåêóíä

#define ONE_UNIT_OF_RECIVED_ANGLE_DEG 0.02197265625f
#define ONE_UNIT_OF_RECIVED_ANGLE_RAD 0.001533980787886f
#define ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit 0.0003834951969714f //   2*Pi/2^14
#define angle_90_degrees 				4096
#define ALEX_MOS_start_CHARSTER 0x3E 
#define ALEX_MOS_MAX_PACKET_LEN 260
#define CHSUM                   0x00                     

#define CMD_CALIB_ACC 				65
#define CMD_CALIB_BAT 				66
#define CMD_CONFIRM 					67
#define CMD_CONTROL 					67
#define CMD_REALTIME_DATA 		68
#define CMD_EXECUTE_MENU 			69
#define CMD_USE_DEFAULTS			70
#define CMD_CALIB_EXT_GAIN 		71
#define CMD_HELPER_DATA 			72
#define CMD_GET_ANGLES 				73
#define CMD_MOTORS_ON 				77
#define CMD_CALIB_OFFSET 			79
#define CMD_CALIB_POLES				80
#define CMD_READ_PARAMS 			82
#define CMD_TRIGGER_PIN 			84
#define CMD_BOARD_INFO 				86
#define CMD_WRITE_PARAMS 			87
#define CMD_CALIB_GYRO 				103
#define CMD_MOTORS_OFF 				109
#define CMD_RESET 						114

// Board v3.x only
#define CMD_BOARD_INFO_3 					20
#define CMD_READ_PARAMS_3 				21
#define CMD_WRITE_PARAMS_3 				22
#define CMD_REALTIME_DATA_3 			23
#define CMD_REALTIME_DATA_4 			25
#define CMD_SELECT_IMU_3 					24
#define CMD_READ_PROFILE_NAMES 		28
#define CMD_WRITE_PROFILE_NAMES		29
#define CMD_QUEUE_PARAMS_INFO_3 	30
#define CMD_SET_ADJ_VARS 					31
#define CMD_SAVE_PARAMS_3 				32
#define CMD_READ_PARAMS_EXT 			33
#define CMD_WRITE_PARAMS_EXT 			34
#define CMD_AUTO_PID 							35
#define CMD_SERVO_OUT 						36
#define CMD_I2C_WRITE_REG_BUF 		39
#define CMD_I2C_READ_REG_BUF		 	40
#define CMD_WRITE_EXTERNAL_DATA 	41
#define CMD_READ_EXTERNAL_DATA		42
#define CMD_READ_ADJ_VARS_CFG 		43
#define CMD_WRITE_ADJ_VARS_CFG 		44
#define CMD_API_VIRT_CH_CONTROL 	45
#define CMD_ADJ_VARS_STATE 				46
#define CMD_EEPROM_WRITE 					47
#define CMD_EEPROM_READ 					48
#define CMD_BOOT_MODE_3 					51
#define CMD_READ_FILE 						53
#define CMD_WRITE_FILE 						54
#define CMD_FS_CLEAR_ALL 					55
#define CMD_AHRS_HELPER 					56
#define CMD_RUN_SCRIPT 						57
#define CMD_SCRIPT_DEBUG 					58
#define CMD_CALIB_MAG 						59
#define CMD_DEBUG_VARS_INFO_3 		253
#define CMD_DEBUG_VARS_3 					254
#define CMD_ERROR 								255

extern const uint8_t const_cmd_board_info[];
extern const uint8_t const_cmd_board_info3[];
extern const uint8_t const_cmd_read_params_3[];
extern const uint8_t const_cmd_read_params_ext[];
extern const uint8_t const_cmd_real_time_data_3[];
extern const uint8_t const_cmd_real_time_data_4[];
extern const uint8_t const_cmd_get_angles[];
extern const uint8_t const_cmd_read_profile_names[];
extern const uint8_t const_cmd_read_i2c_reg_buf[];
extern const uint8_t const_cmd_read_external_data[];
extern const uint8_t const_cmd_real_time_data[]			;
extern const uint8_t const_cmd_real_time_data_3[]		;
extern const uint8_t const_cmd_real_time_data_4[]		;
extern const uint8_t const_cmd_read_profile_names[]	;
extern const uint8_t const_cmd_read_i2c_reg_buf[]		;
extern const uint8_t const_cmd_read_external_data[]	;
extern const uint8_t const_cmd_calib_ext_gain[]			;
extern const uint8_t const_cmd_calib_poles[]				;
extern const uint8_t const_cmd_calib_offset[]				;
extern const uint8_t const_cmd_calib_mag[]					;
extern const uint8_t const_cmd_motors_on[]					;
extern const uint8_t const_cmd_motors_off[]					;
extern const uint8_t const_cmd_save_params[]				;
extern const uint8_t const_cmd_debug_vars_info_3[]	;
extern const uint8_t const_cmd_debug_vars_3[]				;
extern const uint8_t const_cmd_read_adj_vars_cfg[] 	;
extern const uint8_t const_cmd_read_vars_cfg[]			;
extern const uint8_t const_cmd_board_info_ext[]			;
extern const uint8_t const_cmd_calib_acc[]					;
extern const uint8_t const_cmd_calib_gyro[]					;
extern const uint8_t const_cmd_use_defaults[]				;
extern const uint8_t const_cmd_read_params[]				;
extern const uint8_t const_cmd_read_params_3[]			;
extern const uint8_t const_cmd_read_params_ext[]    ;
extern const uint8_t const_cmd_write_params[]				;
extern const uint8_t const_cmd_write_params_3[]			;
extern const uint8_t const_cmd_write_params_ext[]   ;
extern const uint8_t const_cmd_reset[]							;
extern const uint8_t const_cmd_boot_mode_3[]				;
extern const uint8_t const_cmd_calib_bat[]          ;
extern const uint8_t const_cmd_control[]         	  ;
extern const uint8_t const_cmd_trigger_pin[]        ;
extern const uint8_t const_cmd_execute_menu[]   		;
extern const uint8_t const_cmd_helper_data[]      	;
extern const uint8_t const_cmd_get_angles[]					;
extern const uint8_t const_cmd_select_imu[]					;
extern const uint8_t const_cmd_write_profile_names[];
extern const uint8_t const_cmd_set_adj_vars[] 			;
extern const uint8_t const_cmd_auto_pid[] 					;
extern const uint8_t const_cmd_servo_out[]					;
extern const uint8_t const_cmd_i2c_write_reg_buf[]	;
extern const uint8_t const_cmd_i2c_read_reg_buf[]		;
extern const uint8_t const_cmd_write_external_data[];
extern const uint8_t const_cmd_api_virt_ch_control[];
extern const uint8_t const_cmd_write_vars_cfg[]			;
extern const uint8_t const_cmd_eeprom_write[]				;
extern const uint8_t const_cmd_eeprom_read[]				;
extern const uint8_t const_cmd_ahrs_helper[]				;

#pragma pack(push,1)

typedef struct gimbal_parameters
{
	struct __frame
	{
		struct __angle
		{ 
			float roll;
			float yaw;
			float pitch;
		}angle;
		struct __cam_angle
		{
			float roll;
			float yaw;
			float pitch;
		}cam_angle;
	}frame;
	struct __mag_data
	{
			int16_t roll;
			int16_t yaw;
			int16_t pitch;		
	}mag_data;
	struct __balance_error
	{
			int16_t roll;
			int16_t yaw;
			int16_t pitch;			
	}balance_error;
	struct __imu
	{ 
		struct __frame_imu
		{
			int16_t temperature;
		}frame_imu;
		struct __main_imu
		{
			int16_t temperature;
		}main_imu;
	}imu;			
}__gimbal;

typedef union __control_union
	{
		uint8_t string[13];
		struct __control_struct
		{	int8_t control_mode;
			int16_t speed_roll;
			int16_t angle_roll;
			int16_t speed_pitch;
			int16_t angle_pitch;
			int16_t speed_yaw;
			int16_t angle_yaw;			
		}param;	
	}alex_mos_control;
typedef struct __alex_mos_msg_and_state{
union {
struct __alex_mos_message 
{ 
	uint8_t start;
	uint8_t command_id;
	uint8_t data_size;
	uint8_t header_cheksum;
	union 
		{
			uint8_t data[255];
			struct __real_time_data_3
			{
				int16_t roll_acc;
				int16_t roll_gyro;
				int16_t pitch_acc;
				int16_t pitch_gyro;
				int16_t yaw_acc;
				int16_t yaw_gyro;	
				//int16_t reserved_sensor_0;
				//int16_t reserved_sensor_1;
				int16_t debug1;
				int16_t debug2;
				int16_t debug3;
				int16_t debug4;
				int16_t rc_roll;
				int16_t rc_pitch;
				int16_t rc_yaw;
				int16_t rc_cmd;
				int16_t ext_fc_roll;
				int16_t ext_fc_pitch;
				int16_t angle_rool;
				int16_t angle_pitch;
				int16_t angle_yaw;
				int16_t frame_imu_angle_rool;
				int16_t frame_imu_angle_pitch;
				int16_t frame_imu_angle_yaw;				
				int16_t rc_angle_rool;
				int16_t rc_angle_pitch;
				int16_t rc_angle_yaw;				
				uint16_t cycle_time;
				uint16_t i2c_error_count;
				uint8_t  error_code;
				uint16_t bat_level;
				uint8_t other_flags;
				uint8_t cur_imu;
				uint8_t cur_profile;
				uint8_t motor_power_roll;
				uint8_t motor_power_pitch;
				uint8_t motor_power_yaw;
			}real_time_data_3;
			struct __real_time_data_4
			{ 
				int16_t roll_acc;
				int16_t roll_gyro;
				int16_t pitch_acc;
				int16_t pitch_gyro;
				int16_t yaw_acc;
				int16_t yaw_gyro;	
				//int16_t reserved_sensor_0;
				//int16_t reserved_sensor_1;
				int16_t debug1;
				int16_t debug2;
				int16_t debug3;
				int16_t debug4;
				int16_t rc_roll;
				int16_t rc_pitch;
				int16_t rc_yaw;
				int16_t rc_cmd;
				int16_t ext_fc_roll;
				int16_t ext_fc_pitch;
				int16_t angle_roll;
				int16_t angle_pitch;
				int16_t angle_yaw;
				int16_t frame_imu_angle_roll;
				int16_t frame_imu_angle_pitch;
				int16_t frame_imu_angle_yaw;				
				int16_t rc_angle_rool;
				int16_t rc_angle_pitch;
				int16_t rc_angle_yaw;				
				uint16_t cycle_time;
				uint16_t i2c_error_count;
				uint8_t  error_code;
				uint16_t bat_level;
				uint8_t other_flags;
				uint8_t cur_imu;
				uint8_t cur_profile;
				uint8_t motor_power_roll;
				uint8_t motor_power_pitch;
				uint8_t motor_power_yaw;
//===========================================
				int16_t  frame_angle_roll;
				int16_t  frame_angle_pitch;
				int16_t  frame_angle_yaw;
				uint8_t  RESERVED;
				int16_t  balance_error_roll;
				int16_t  balance_error_pitch;
				int16_t  balance_error_yaw;
				uint16_t current;
				int16_t  mag_data_roll;
				int16_t  mag_data_pitch;
				int16_t  mag_data_yaw;
				int8_t   imu_temperature;
				int8_t   frame_imu_temperature;
				int16_t  frame_cam_angle_roll;
				int16_t  frame_cam_angle_pitch;
				int16_t  frame_cam_angle_yaw;
				uint8_t  RESERVED_0[32];	
			}real_time_data_4;
		}msg_union;
	uint8_t body_cheksum;
	
}alex_mos_message;
uint8_t alexmos_rx_buffer[ALEX_MOS_MAX_PACKET_LEN];
}union_alex_mos_buf;
uint16_t alex_mos_parsing_step;
uint16_t alex_mos_parsing_steps;
int8_t  alex_mos_parsing_state;
}alex_mos_msg_and_state;

#pragma pack(pop)

extern __gimbal gimbal;
extern alex_mos_msg_and_state alex_rx_msg;
extern alex_mos_control alex_mos_ctrl_msg;
extern uint8_t new_alex_mos_message_recived;

extern alex_mos_msg_and_state alex_rx_msg;
extern uint8_t new_alex_mos_message_recived;
extern const uint8_t * pointer_to_const_char_uart4;
extern uint8_t *pointer_to_char_uart4 ;
extern uint8_t UART4_not_bysy;
extern volatile uint8_t alex_mos_getting_angles_timer;
extern volatile uint8_t alex_mos_sending_control_timer; // Òàéìåð â1äïðàâêè êîìàíä àëåêñìîñó
extern volatile uint8_t usart_4_not_busy_delay_timer;
extern volatile uint8_t ping_timer;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++FUNCTION PROTOTYPES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void alex_mos_insert_crc(uint8_t *msg);
int8_t alex_mos_parse_char(char recived_char , alex_mos_msg_and_state *msg);
void copy_message_header(const uint8_t *src_sring, uint8_t *dst_sring);
void alex_mos_pack_cmd_control(uint8_t *output_buffer,uint8_t *params);
void sort_alex_mos_message(void);
void send_realtime_data_request_to_alexmos_if_its_need(void);
void send_control_msg_to_alexmos_if_its_need(void);
void check_usart4_bysy(void);
void alexmos_buffers_init (void);

#endif



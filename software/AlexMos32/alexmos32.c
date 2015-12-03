#include "alexmos32.h"
#include "stm32f30x_it.h"
#include "stdint.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++GLOBAL VARIABLES FOR ALEX MOS+++++++++++++++++++++++++++++++++++++++++++++
uint8_t new_alex_mos_message_recived=0x00;
alex_mos_msg_and_state alex_rx_msg;
alex_mos_control alex_mos_ctrl_msg;
uint8_t *pointer_to_char_uart4 ;
__gimbal gimbal;

__IO uint8_t alex_mos_getting_angles_timer = 0; // “аймер запиту кут1в п1дв1су
__IO uint8_t alex_mos_sending_control_timer =0; // “аймер в1дправки команд алексмосу
__IO uint8_t usart_4_not_busy_delay_timer =0;   //“аймер затримки на 10-20 м1л1секунд в1дправки наступного пакету

//UART4 bysy flag 
uint8_t UART4_not_bysy=0xff;
uint8_t USART4_TX_bufer[ALEX_MOS_MAX_PACKET_LEN];

// оманды , которые можно определить в виде строковых констант , то есть команды без дополнительных параметров , или с 
//параметрами которые можно перечислить или продублировать , короче которые строго определены и нет необходимости пересчитывать 
//контрольные суммы , отправл€ютс€ через указатель
// Ќулевой лемент буффера содержит количество байт дл€ передачи всего сообщени€ +1 ,
//сам  при том не передаетс€ 
const uint8_t const_cmd_board_info[]					={6,0x3e,CMD_BOARD_INFO,1,CMD_BOARD_INFO+1,0,0};									//Ц request board and firmware information
const uint8_t const_cmd_board_info3[]					={6,0x3e,CMD_BOARD_INFO_3,1,CMD_BOARD_INFO_3+1,0,0};							//- request additional board information
const uint8_t const_cmd_real_time_data[]			={6,0x3e,CMD_REALTIME_DATA,1,CMD_REALTIME_DATA+1,0,0};
const uint8_t const_cmd_real_time_data_3[]		={6,0x3e,CMD_REALTIME_DATA_3,1,CMD_REALTIME_DATA_3+1,0,0};
const uint8_t const_cmd_real_time_data_4[]		={6,0x3e,CMD_REALTIME_DATA_4,1,CMD_REALTIME_DATA_4+1,0,0};
const uint8_t const_cmd_read_profile_names[]	={6,0x3e,CMD_READ_PROFILE_NAMES,1,CMD_READ_PROFILE_NAMES+1,0,0};
const uint8_t const_cmd_read_i2c_reg_buf[]		={6,0x3e,CMD_I2C_READ_REG_BUF,1,CMD_I2C_READ_REG_BUF+1,0,0};
const uint8_t const_cmd_read_external_data[]	={6,0x3e,CMD_READ_EXTERNAL_DATA,1,CMD_READ_EXTERNAL_DATA+1,0,0};
const uint8_t const_cmd_calib_ext_gain[]			={6,0x3e,CMD_CALIB_EXT_GAIN,1,CMD_CALIB_EXT_GAIN+1,0,0};
const uint8_t const_cmd_calib_poles[]					={6,0x3E,CMD_CALIB_POLES,1,CMD_CALIB_POLES+1,0,0};
const uint8_t const_cmd_calib_offset[]				={6,0x3E,CMD_CALIB_OFFSET,1,CMD_CALIB_OFFSET+1,0,0};
const uint8_t const_cmd_calib_mag[]						={6,0x3E,CMD_CALIB_MAG,1,CMD_CALIB_MAG+1,0,0};
const uint8_t const_cmd_motors_on[]						={6,0x3E,CMD_MOTORS_ON,1,CMD_MOTORS_ON+1,0,0};
const uint8_t const_cmd_motors_off[]					={6,0x3E,CMD_MOTORS_OFF,1,CMD_MOTORS_OFF+1,0,0};
const uint8_t const_cmd_save_params[]					={6,0x3E,CMD_SAVE_PARAMS_3,1,CMD_SAVE_PARAMS_3+1,0,0};
const uint8_t const_cmd_debug_vars_info_3[]		={6,0x3E,CMD_DEBUG_VARS_INFO_3,1,CMD_DEBUG_VARS_INFO_3+1,0,0};
const uint8_t const_cmd_debug_vars_3[]				={6,0x3E,CMD_DEBUG_VARS_3 ,1,CMD_DEBUG_VARS_3+1,0,0};
const uint8_t const_cmd_read_adj_vars_cfg[] 	={6,0x3e,CMD_READ_ADJ_VARS_CFG,1,CMD_READ_ADJ_VARS_CFG+1,0,0 };

//«десь описаны команды,  в виде строчных констант , с аргументами , перед отправкой будут копироватс€ 
// в строковую переменнную , добавл€тьс€ аргументы и вставл€тьс€ контрольные суммы , далее передача
// посредством указател€ 
const uint8_t const_cmd_board_info_ext[]			={7,0x3e,CMD_BOARD_INFO,2,CHSUM,0x00,0x00,0x00};
const uint8_t const_cmd_calib_acc[]						={0X11,0X3E,CMD_CALIB_ACC ,0x0c,CHSUM,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,CHSUM};
const uint8_t const_cmd_calib_gyro[]					={0X11,0X3E,CMD_CALIB_GYRO,0x0c,CHSUM,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,CHSUM};
const uint8_t const_cmd_use_defaults[]				={0x06,0x3e,CMD_USE_DEFAULTS,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_read_params[]					={0x06,0x3e,CMD_READ_PARAMS    ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_read_params_3[]				={0x06,0x3e,CMD_READ_PARAMS_3  ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_read_params_ext[]     ={0x06,0x3e,CMD_READ_PARAMS_EXT,0x01,CHSUM,0x00,CHSUM};
//дописать структуру даных дл€  врайт парам!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const uint8_t const_cmd_write_params[]				={0x06,0x3e,CMD_WRITE_PARAMS    ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_write_params_3[]			={0x06,0x3e,CMD_WRITE_PARAMS_3  ,0x01,CHSUM,0x00,CHSUM};
const uint8_t const_cmd_write_params_ext[]    ={0x06,0x3e,CMD_WRITE_PARAMS_EXT,0x01,CHSUM,0x00,CHSUM};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const uint8_t const_cmd_reset[]								={  8 ,0x3e,CMD_RESET,3};
const uint8_t const_cmd_boot_mode_3[]					={  8 ,0x3e,CMD_BOOT_MODE_3,3};
const uint8_t const_cmd_calib_bat[]           ={  7 ,0x3e,CMD_WRITE_PARAMS_EXT,0x02};
const uint8_t const_cmd_control[]         	  ={ 18 ,0x3e,CMD_CONTROL,13};
const uint8_t const_cmd_trigger_pin[]         ={  7 ,0x3e,CMD_TRIGGER_PIN,2};
const uint8_t const_cmd_execute_menu[]   			={  6 ,0x3e,CMD_EXECUTE_MENU,1};
const uint8_t const_cmd_helper_data[]      	  ={ 15 ,0x3e,CMD_HELPER_DATA,10};
const uint8_t const_cmd_get_angles[]					={  6 ,0x3e,CMD_GET_ANGLES,1};
const uint8_t const_cmd_select_imu[]					={  6 ,0x3e,CMD_SELECT_IMU_3,1};
const uint8_t const_cmd_write_profile_names[] ={245 ,0x3e,CMD_HELPER_DATA,240};
const uint8_t const_cmd_set_adj_vars[] 				={ 16 ,0x3e,CMD_SET_ADJ_VARS,11};
const uint8_t const_cmd_auto_pid[] 						={ 24 ,0x3e,CMD_AUTO_PID,19};
const uint8_t const_cmd_servo_out[]						={ 21 ,0x3e,CMD_SERVO_OUT,16};
const uint8_t const_cmd_i2c_write_reg_buf[]		={ 0  ,0x3e,CMD_I2C_WRITE_REG_BUF,4 }; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_i2c_read_reg_buf[]		={ 0  ,0x3e,CMD_I2C_READ_REG_BUF ,4 }; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов   
const uint8_t const_cmd_write_external_data[]	={ 132,0x3e,CMD_WRITE_EXTERNAL_DATA,128};
const uint8_t const_cmd_api_virt_ch_control[]	={ 71 ,0x3e,CMD_API_VIRT_CH_CONTROL,64 };
const uint8_t const_cmd_write_vars_cfg[]			={ 93 ,0x3e,CMD_WRITE_ADJ_VARS_CFG,88};
const uint8_t const_cmd_eeprom_write[]				={  4 ,0x3e,CMD_EEPROM_WRITE,0};//¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_eeprom_read[]					={  4 ,0x3e,CMD_EEPROM_READ,0}; //¬нимание  длина пакета мен€етс€ в зависимости от аргументов
const uint8_t const_cmd_ahrs_helper[]					={ 30 ,0x3e,CMD_AHRS_HELPER,25};




//‘унции копировани€ строчных констант в строчную переменнную , вставки параметров  и  контрольных сум.
void alex_mos_pack_cmd_read_params						(uint8_t * a[]);	//- request parameters from the board
void alex_mos_pack_cmd_read_params_3					(uint8_t * a[]);	//Ц request parameters from the board
void alex_mos_pack_cmd_read_params_ext				(uint8_t * a[]);	//Ц request extended parameters from the board
void alex_mos_pack_cmd_write_params						(uint8_t * a[]);	//- write parameters to board and saves to EEPROM
void alex_mos_pack_cmd_write_params_3					(uint8_t * a[]);	//- write parameters to board and saves to EEPROM
void alex_mos_pack_cmd_write_params_ext				(uint8_t * a[]);	//Ц write extended parameters
void alex_mos_pack_cmd_realtime_data		 			(uint8_t * a[]);	//- request real-time data, response is CMD_REALTIME_DATA_3
void alex_mos_pack_cmd_realtime_data_3 				(uint8_t * a[]);	//- request real-time data, response is CMD_REALTIME_DATA_3
void alex_mos_pack_cmd_realtime_data_4 				(uint8_t * a[]);	//Ц request extended real-time data, response is CMD_REALTIME_DATA_4
void alex_mos_pack_cmd_rset										(uint8_t * a[]);	//Ц reset device
void alex_mos_pack_cmd_boot_mode_3						(uint8_t * a[]);	//Ц enter bootloader mode to upload firmware
void alex_mos_pack_cmd_script_debug						(uint8_t * a[]);
void alex_mos_pack_cmd_ahrs_helper						(uint8_t * a[]);	//Ц use provided attitude instead of estimated attitude from main IMU sensor
void alex_mos_pack_cmd_calb_acc								(uint8_t * a[]);	//Ц calibrate accelerometer
void alex_mos_pack_cmd_calb_gyro							(uint8_t * a[]);	//Ц calibrate gyroscope
void alex_mos_pack_cmd_calib_ext_gain					(uint8_t * a[]);	//Ц calibrate EXT_FC gains
void alex_mos_pack_cmd_calib_use_defaults			(uint8_t * a[]);	//Ц reset to factory defaults
void alex_mos_pack_cmd_calib_poles						(uint8_t * a[]);	//Ц calibrate poles and direction
void alex_mos_pack_cmd_calib_offset						(uint8_t * a[]);	//Ц calibrate follow offset
void alex_mos_pack_cmd_calib_bat							(uint8_t * a[]);	//- calibrate battery (voltage sensor)
void alex_mos_pack_cmd_calib_mag							(uint8_t * a[]);	//Ц run magnetometer calibration
//Ц control alex_mos_pack movement
void alex_mos_pack_cmd_control								(uint8_t *output_buffer,uint8_t *params)
{
uint8_t copy_index_i;
copy_message_header(&const_cmd_control[0], &output_buffer[0]);
for(copy_index_i=0;copy_index_i<13;copy_index_i++)
{
	output_buffer[ copy_index_i+5 ]=params[ copy_index_i ];
}
alex_mos_insert_crc(&output_buffer[0]);
}	
void alex_mos_pack_cmd_trigger_pin						(uint8_t * a[]);	//- trigger output pin
void alex_mos_pack_cmd_motors_on							(uint8_t * a[]);	//- switch motors ON
void alex_mos_pack_cmd_motors_off							(uint8_t * a[]);	//- switch motors OFF
void alex_mos_pack_cmd_execute_menu						(uint8_t * a[]);	//- execute menu command
void alex_mos_pack_cmd_helper_data						(uint8_t * a[]);	//Ц pass helper data
void alex_mos_pack_cmd_get_angles 						(uint8_t * a[]);	//- Request information about angles and RC control state
void alex_mos_pack_cmd_select_imu_3						(uint8_t * a[]);	//Ц Select which IMU to configure
void alex_mos_pack_cmd_read_profile_names_3		(uint8_t * a[]);	//Ц Request profile names stored in EEPROM
void alex_mos_pack_cmd_write_profile_names_3	(uint8_t * a[]);	//Ц Writes profile names to EEPROM
void alex_mos_pack_cmd_get_params_3 					(uint8_t * a[]);	//Ц Request information about configurable parameters: type, range, current value
void alex_mos_pack_cmd_set_adj_vars 					(uint8_t * a[]);	//Ц Change the value of selected parameter(s)
void alex_mos_pack_cmd_save_params_3					(uint8_t * a[]);	//Ц Saves current params from volatile memory to EEPROM, to the active profile slot.
void alex_mos_pack_cmd_auto_pid								(uint8_t * a[]);	//Ц Starts automatic PID calibration
void alex_mos_pack_cmd_servo_out							(uint8_t * a[]);	//Ц Output PWM signal on the specified pins
void alex_mos_pack_cmd_i2c_write_reg_buf			(uint8_t * a[]);	//Ц writes data to any device connected to I2C line
void alex_mos_pack_cmd_i2c_read_reg_buf				(uint8_t * a[]);	//Ц requests reading from any device connected to I2C line
void alex_mos_pack_cmd_debug_vars_info_3			(uint8_t * a[]);	//Ц request information about debug variables
void alex_mos_pack_cmd_debug_vars_3						(uint8_t * a[]);	//Ц request values of debug variables
void alex_mos_pack_cmd_write_extern_data_3		(uint8_t * a[]);	//Ц stores any user data to the dedicated area in the EEPROM
void alex_mos_pack_cmd_read_extern_data_3			(uint8_t * a[]);	//Ц request user data, stored in the EEPROM
void alex_mos_pack_cmd_api_virt_ch_control		(uint8_t * a[]);	//Ц update a state of 32 virtual channels that named УAPI_VIRT_CHXXФ in the GUI
void alex_mos_pack_cmd_read_adj_vars_cfg			(uint8_t * a[]);	//Ц request configuration of mapping of control inputs to adjustable
void alex_mos_pack_cmd_write_adj_vars_cfg			(uint8_t * a[]);	//Ц writes configuration of mapping of control inputs to adjustable variables
void alex_mos_pack_cmd_eeprom_write						(uint8_t * a[]);	//Ц writes a block of data to EEPROM to specified address
void alex_mos_pack_cmd_eeprom_read						(uint8_t * a[]);	//Ц request a reading of block of data from EEPROM at the specified address and size.
void alex_mos_pack_cmd_read_file							(uint8_t * a[]);	//Ц read file from internal filesystem
void alex_mos_pack_cmd_write_file							(uint8_t * a[]);	//Ц write file to internal filesystem
void alex_mos_pack_cmd_fs_clear_all						(uint8_t * a[]);	//Ц delete all files from internal filesystem
void alex_mos_pack_cmd_run_script							(uint8_t * a[]);	//Ц start or stop user-written script

//alex mos reciver structure init 
void alexmos_buffers_init (void) {
	alex_rx_msg.alex_mos_parsing_state = 0;
	alex_rx_msg.alex_mos_parsing_step  = 0;
	alex_rx_msg.alex_mos_parsing_steps  = ALEX_MOS_MAX_PACKET_LEN;
}
//‘ункци€ вставл€ет контрольные суммы , в протоколе их две , в нужные места указаного буфера
void alex_mos_insert_crc(uint8_t *msg)
{
uint16_t crc_accu=0;
uint16_t i;
crc_accu = msg[2]+msg[3];
msg[4] = (uint8_t)crc_accu;
crc_accu=0;
for(i=5; i<msg[3]+5 ;i++) crc_accu += msg[i];
msg[msg[0]]= (uint8_t)crc_accu;
}	
//ѕарсинг сообщений 
int8_t alex_mos_parse_char(char recived_char , alex_mos_msg_and_state *msg)
{ 
	if ((recived_char == ALEX_MOS_start_CHARSTER)&&(alex_rx_msg.alex_mos_parsing_step == 0)&&(alex_rx_msg.alex_mos_parsing_steps  == ALEX_MOS_MAX_PACKET_LEN))
	{
		alex_rx_msg.alex_mos_parsing_state = 0;
	}
	if (alex_rx_msg.alex_mos_parsing_state == 0)
	{
		alex_rx_msg.union_alex_mos_buf.alexmos_rx_buffer[alex_rx_msg.alex_mos_parsing_step]=recived_char;
		alex_rx_msg.alex_mos_parsing_step++;
	}
	if(alex_rx_msg.alex_mos_parsing_step == 0x03) 
	{
		alex_rx_msg.alex_mos_parsing_steps=alex_rx_msg.union_alex_mos_buf.alexmos_rx_buffer[2]+3;
	}

	if (alex_rx_msg.alex_mos_parsing_step>= alex_rx_msg.alex_mos_parsing_steps)
	{
		alex_rx_msg.alex_mos_parsing_state  = 1;
		alex_rx_msg.alex_mos_parsing_step   = 0;
		alex_rx_msg.alex_mos_parsing_steps  = ALEX_MOS_MAX_PACKET_LEN;
	}		
	if (alex_rx_msg.alex_mos_parsing_step > ALEX_MOS_MAX_PACKET_LEN)
		{
			alex_rx_msg.alex_mos_parsing_state  = -1;
			alex_rx_msg.alex_mos_parsing_step   = 0;
			alex_rx_msg.alex_mos_parsing_steps  = ALEX_MOS_MAX_PACKET_LEN;
		}
	
	return(alex_rx_msg.alex_mos_parsing_state);
}
// ‘унц1€ коп1ю3 заголовок пов1домленн€ з *src_sring в *dst_sring , всього коп1ю3тьс€ чотири байти
void copy_message_header(const uint8_t *src_sring, uint8_t *dst_sring)
{
uint8_t copy_index_i;
	for(copy_index_i=0;copy_index_i<4;copy_index_i++)
	{
		dst_sring[copy_index_i]= src_sring[copy_index_i];
	}
}	
void sort_alex_mos_message(void)
{
	if(new_alex_mos_message_recived)
	{
		new_alex_mos_message_recived = 0;
		switch (alex_rx_msg.union_alex_mos_buf.alex_mos_message.command_id)
		{
			case CMD_BOARD_INFO : 				
			{
				break;	
			}
			case CMD_BOARD_INFO_3 :
			{
				break;
			}
			case CMD_READ_PARAMS :
			{
				break;
			}
			case CMD_READ_PARAMS_EXT :
			{
				break;
			}
			case CMD_REALTIME_DATA_3 :
			{
				//gimbal.yaw_angle   = alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_3.frame_angle_yaw;
	      //gimbal.pitch_angle = alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_3.frame_angle_pitch;
				break;
			}
			case CMD_REALTIME_DATA_4 :
			{
				gimbal.frame.cam_angle.roll  = alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.frame_cam_angle_roll  * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;
				gimbal.frame.cam_angle.pitch = alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.frame_cam_angle_pitch * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;
				gimbal.frame.cam_angle.yaw   = alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.frame_cam_angle_yaw   * ONE_UNIT_OF_RECIVED_ANGLE_RAD_14bit;
				
				gimbal.frame.angle.yaw   =  alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.angle_yaw;
				gimbal.frame.angle.pitch =  alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.angle_pitch;
				gimbal.frame.angle.roll  =  alex_rx_msg.union_alex_mos_buf.alex_mos_message.msg_union.real_time_data_4.angle_roll;
			break;
			}
			case CMD_CONFIRM :
			{
				break;
			}
			case CMD_ERROR :
			{
				break;
			}
			case CMD_GET_ANGLES :
			{
				break;
			}
			case CMD_READ_PROFILE_NAMES :
			{
				break;
			}
			case CMD_I2C_READ_REG_BUF :
			{
				break;
			}
			case CMD_AUTO_PID :
			{
				break;
			}
			case CMD_DEBUG_VARS_INFO_3 :
			{
				break;
			}
			case CMD_DEBUG_VARS_3 :
			{
				break;
			}
			case CMD_READ_EXTERNAL_DATA :
			{
				break;
			}
			case CMD_READ_ADJ_VARS_CFG :
			{
				break;
			}
			case CMD_RESET :
			{
				break;
			}
			case CMD_EEPROM_READ :
			{
				break;
			}
			case CMD_READ_FILE :
			{
				break;
			}
			case CMD_SCRIPT_DEBUG :
			{
				break;
			}
			case CMD_AHRS_HELPER :
			{
				break;
			}
		  default :
			{
				
			}
		}
	}
}
void	send_realtime_data_request_to_alexmos_if_its_need(void){
		if (alex_mos_getting_angles_timer > alex_mos_getting_angles_interval)
		{
			if (UART4_not_bysy )
			{ 
				pointer_to_char_uart4 =(uint8_t *) &const_cmd_real_time_data_4;
				UART4_not_bysy = 0x00;
				USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
				alex_mos_getting_angles_timer=0;
			}
		}
	}
void send_control_msg_to_alexmos_if_its_need(void){
		if (alex_mos_sending_control_timer > alex_mos_sending_control_interval)
		{
			if (UART4_not_bysy )
			{ 
				alex_mos_pack_cmd_control(&USART4_TX_bufer[0],&alex_mos_ctrl_msg.string[0]);
				pointer_to_char_uart4 = &USART4_TX_bufer[0];
				UART4_not_bysy = 0x00;
				USART_ITConfig(UART4, USART_IT_TXE, ENABLE);	
				alex_mos_sending_control_timer =0;	
			}
		}
	}
void check_usart4_bysy(void){
		//ќюробка зайн€тост1 uart4
	  if ( UART4_not_bysy ==0)
		{
			if (usart_4_not_busy_delay_timer >= usart_4_not_busy_delay_interval	)  UART4_not_bysy = 0xff;
		}
	}




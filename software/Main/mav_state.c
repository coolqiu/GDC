#include <stdint.h>
#include "mav_state.h"
#include "mavlink.h"
#include "main.h"
#include "parameters.h"
#include "stm32f30x_it.h"
#include "stm32f3_discovery.h"
#include "alexmos32.h"
#include "lense_coordinate_finding.h"
#include <string.h>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* MAVLINK VARIABLES SECTION			*/
#define This_mav_sys_id 3
#define This_mav_comp_id MAV_COMP_ID_PAYLOAD_CONTROLLER
#define GCS_SYS_ID 255
#define heartbeat_sending_interval  100 //100=1 sec. - in 10 milise per unit
#define coordinate_sending_interval 20  // every 200mSec. send target coordinates 

#define default_sending_interval_of_global_position 100
static volatile uint16_t sending_interval_of_global_position =0;

static volatile uint16_t sending_interval_of_heartbeat_sending =0;

static volatile uint16_t sending_interval_target_coordinates =0;

uint8_t USART2_RX_bufer[MAVLINK_MAX_PACKET_LEN];
volatile uint8_t USART2_words_to_recive=0;
volatile uint8_t USART2_current_RX_word=0;
uint8_t USART2_TX_bufer[MAVLINK_MAX_PACKET_LEN];
volatile uint8_t USART2_current_TX_word=0;
volatile uint8_t USART2_words_to_send=0;
volatile uint8_t new_mavlink_message_recived_via_usrt2_flag=0;
mavlink_message_t msg;
mavlink_system_t mavlink_system = {This_mav_sys_id,This_mav_comp_id};
mavlink_message_t RX_msg; //recived mav link message
mavlink_message_t TX_msg; //MAVLink message to transmit
mavlink_status_t status;

//static int packet_drops = 0;
static int mode = MAV_MODE_FLAG_SAFETY_ARMED; /* Defined in mavlink_types.h, which is included by mavlink.h */
 
// Define the system type, in this case an airplane
uint8_t system_type = MAV_TYPE_GIMBAL;
uint8_t autopilot_type = 'P';
//uint8_t system_mode = MAV_MODE_FLAG_SAFETY_ARMED;
uint32_t custom_mode = 0;         ///< Custom mode, can be defined by user/adopter
uint8_t system_state = MAV_STATE_ACTIVE; 
 
volatile uint16_t  mav_tx_len;
volatile uint16_t heartbeat_sending_timer=0; //Heartbeat timer init 
volatile uint16_t target_coordinate_sending_timer =0;
mavlink_attitude_t CurrentAttitude;
mavlink_global_position_int_t current_GPS_data;
mavlink_gps_status_t gps_status;
mavlink_gps_raw_int_t gps_raw_int;
mavlink_mount_control_t mount_control;
static volatile 	uint16_t command_long_confirmation =0;

void	MAVLink_init(void){
mavlink_system.sysid = This_mav_sys_id;
mavlink_system.compid= This_mav_comp_id;
load_sending_intervals_from_parameters();
}
void load_sending_intervals_from_parameters(void)
{ uint16_t ind;  
	//Frequences(realy intervals beetwhen ) of sending  mavlink messages , separatly for every 
  //message  
  //GLOBAL_POSITION_INT ( #33 )	
	ind = parameters_contain("SEND_GLB_POS_INT");
	if (ind == 0xffff) 
		sending_interval_of_global_position = default_sending_interval_of_global_position;
	else
		{
		convert_to.float32 = parameter_RW[ind].value;
		if(convert_to.float32> 655.35f)convert_to.float32 = 65535.0;
		if(convert_to.float32< 0.1f   )convert_to.float32 = 0.1;
		sending_interval_of_global_position = (uint16_t)(convert_to.float32*100);
		};
	//HEARTBEAT ( #0 )
	ind = parameters_contain("SEND_HEARTBEAT_I");
	//if (ind == 0xffff) 
		//sending_interval_of	
}

void send_heart_beat_if_its_need(void)	 { 
		if (heartbeat_sending_timer > heartbeat_sending_interval) 
			{ 
				if(USART2_words_to_send ==0 && USART2_current_TX_word ==0)
				{ 
				// Pack the message
				mavlink_msg_heartbeat_pack( 
					This_mav_sys_id,
					This_mav_comp_id, 
					&TX_msg, 
					system_type, 
					autopilot_type, 
					mode, 
					custom_mode, 
					system_state);
					
				USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);
					
				USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
				heartbeat_sending_timer=0;
				STM_EVAL_LEDToggle(LED3); // Toggle LD3 
				}
			} 
		}

void send_gps_global_position_int_if_its_need (void){
	static volatile uint64_t sending_time_of_global_position_int =0;
	if (time_boot > sending_time_of_global_position_int)	
	{
		if(USART2_words_to_send ==0 && USART2_current_TX_word ==0)
		{
		mavlink_msg_global_position_int_pack(
			//uint8_t system_id, //uint8_t component_id,//mavlink_message_t* msg, 
			//uint32_t time_boot_ms, 
			//int32_t lat, //int32_t lon,//int32_t alt,//int32_t relative_alt,
			//int16_t vx, //int16_t vy,//int16_t vz,//uint16_t hdg
			This_mav_sys_id, This_mav_comp_id, &TX_msg, 
			time_boot,			
			current_GPS_data.lat,current_GPS_data.lon,current_GPS_data.alt,current_GPS_data.relative_alt,				
			current_GPS_data.vx,current_GPS_data.vy,current_GPS_data.vz,current_GPS_data.hdg);
		
		if( time_boot > 0xffffffff - sending_interval_of_global_position * 2 )
			sending_time_of_global_position_int = 0;
		else
		
		USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);			
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		sending_time_of_global_position_int = time_boot + sending_interval_of_global_position;
		
		//				STM_EVAL_LEDToggle(LED3); // Toggle LD3 
		}
	}
}

void send_target_gimbal_coordinates_if_its_need(void){	
	if (target_coordinate_sending_timer > coordinate_sending_interval) 	
		{ 	
			if(USART2_words_to_send==0 && USART2_current_TX_word==0)
				{
  				//mavlink_msg_command_long_pack(
					//uint8_t system_id, 
					//uint8_t component_id, 
					//mavlink_message_t* msg,
					//uint8_t target_system, 
					//uint8_t target_component, 
					//uint16_t command, 
					//uint8_t confirmation, 
					//float param1, 
					//float param2, 
					//float param3,
					//float param4,
					//float param5, 
					//float param6,
					//float param7)
									
			  	mavlink_msg_command_long_pack(
					This_mav_sys_id,
					This_mav_comp_id, 
					&TX_msg,
					0, 
					0, 
					MAV_CMD_GIMBAL_GEO_ATTITUDE_DATA , //2222
					command_long_confirmation,
					current_lense_coordinates.target_latitude ,
					current_lense_coordinates.target_longtitude, 
					current_lense_coordinates.target_altitude_ASL,
					current_lense_coordinates.gimbal_altitude_REL, 
					current_lense_coordinates.camera_angle_YAW   * RADIANS_TO_DEGREES , 
					current_lense_coordinates.camera_angle_PITCH * RADIANS_TO_DEGREES ,
					current_lense_coordinates.camera_angle_ROLL  * RADIANS_TO_DEGREES);
					
				  command_long_confirmation ++;
				  USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);// Copy the message to the send buffer
				  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
				  target_coordinate_sending_timer=0;
				  STM_EVAL_LEDToggle(LED4); // Toggle LD4 
				}
		}
}
	
void sort_mavlink_message(void)
{
uint16_t j=0 , a=0;
if(new_mavlink_message_recived_via_usrt2_flag)
{
	new_mavlink_message_recived_via_usrt2_flag=0;
	switch(msg.msgid)
			{
			case MAVLINK_MSG_ID_HEARTBEAT:
			{
				//temp=0;
			}
			break;
			case  MAVLINK_MSG_ID_SYS_STATUS:
			{
				//temp=1;
			}
			break;
			case MAVLINK_MSG_ID_SYSTEM_TIME:
			{
				//temp=2;
			}
			break; 
			case MAVLINK_MSG_ID_PING:
			{
				//temp=4;
			}
			break;	
			case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL:
			{
				//temp=5;
			}
			break;		
			case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK:
			{
				//temp=6;
			}
			break;	
			case MAVLINK_MSG_ID_AUTH_KEY:
			{
				//temp=7;
			}
			break;	
			case 8:
			{
				//temp=8;
			}
			break;	
			case 9:
			{
				//temp=9;
			}
			break;	
			case 10:
			{
				//temp=10;
			}
			break;
			case MAVLINK_MSG_ID_SET_MODE:
			{
				//temp=11;
			}
			break;		
			case 12:
			{
				//temp=12;
			}
			break;	
			case 13:
			{
				//temp=13;
			}
			break;		
			case 14:
			{
				//temp=14;
			}
			break;
			case 15:
			{
				//temp=15;
			}
			break;		
			case 16:
			{
				//temp=16;
			}
			break;
			case 17:
			{
				//temp=17;
			}
			break;
			case 18:
			{
				//temp=18;
			}
			break;
			case 19:
			{
				//temp=19;
			}
			break;
			case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
			{//temp=20;
			mavlink_param_request_read_t param_request_read;
			//mavlink_msg_param_request_read_encode(This_mav_sys_id, This_mav_comp_id, &msg, &param_request_read);
			memcpy(&param_request_read,&msg.payload64, MAVLINK_MSG_ID_PARAM_REQUEST_READ_LEN);
			if(param_request_read.target_system == This_mav_sys_id && param_request_read.target_component== This_mav_comp_id)
			{
				
				if(param_request_read.param_index == -1)
				{
					for(a=0;a<total_param_count;a++)
					{
						if(strncmp(parameter_RW[a].param_id,param_request_read.param_id,16) == 0)
						{	while (USART2_words_to_send !=0 && USART2_current_TX_word !=0){heartbeat_sending_timer=0;target_coordinate_sending_timer=0;};			
							mavlink_msg_param_value_pack(This_mav_sys_id, This_mav_comp_id, &TX_msg,
						       &parameter_RW[a].param_id[0] ,parameter_RW[a].value, 
										parameter_RW[a].param_type,total_param_count, a);
							a=0xffff;
						}
					}
				}
				else
				{ if(param_request_read.param_index > total_param_count) break;
					while (USART2_words_to_send !=0 && USART2_current_TX_word !=0){heartbeat_sending_timer=0;target_coordinate_sending_timer=0;};
					mavlink_msg_param_value_pack(This_mav_sys_id, This_mav_comp_id, &TX_msg,
						        &parameter_RW[param_request_read.param_index].param_id[0],
										parameter_RW[param_request_read.param_index].value, 
										parameter_RW[param_request_read.param_index].param_type, 
										total_param_count, param_request_read.param_index);
				}
								USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);
								USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
								heartbeat_sending_timer=0;
								STM_EVAL_LEDToggle(LED3); // Toggle LD3
								while(target_coordinate_sending_timer<10){};
								target_coordinate_sending_timer=0;	
				}				
			}
			break;
			case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
			{	
				if((mavlink_msg_param_request_list_get_target_system(&msg)    == This_mav_sys_id  || msg.sysid == 0)
					&&
					 (mavlink_msg_param_request_list_get_target_component(&msg) == This_mav_comp_id || msg.compid== 0))
				{
					while (j < total_param_count)
					{ 
						while (USART2_words_to_send !=0 && USART2_current_TX_word !=0){heartbeat_sending_timer=0;target_coordinate_sending_timer=0;};
						mavlink_msg_param_value_pack(This_mav_sys_id, This_mav_comp_id, &TX_msg,
					    &parameter_RW[j].param_id[0],
							parameter_RW[j].value, 
							parameter_RW[j].param_type, 
							total_param_count, j);
									
						USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);
						USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
						heartbeat_sending_timer=0;
						STM_EVAL_LEDToggle(LED3); // Toggle LD3
						while(target_coordinate_sending_timer<10){};
						target_coordinate_sending_timer=0;	
						j++;
					}
				}
			}
			break;
			case MAVLINK_MSG_ID_PARAM_VALUE:
			{//temp=22;	
			}
			break;
			case MAVLINK_MSG_ID_PARAM_SET:
			{//temp=23;
				mavlink_param_set_t param_set;
				//mavlink_msg_param_set_decode(&msg, );
				memcpy(&param_set,&msg.payload64, MAVLINK_MSG_ID_PARAM_SET_LEN);
				if(param_set.target_system == This_mav_sys_id && param_set.target_component == This_mav_comp_id)
				{
					for(j=0;j< total_param_count;j++)
					{
						if(strncmp(param_set.param_id , parameter_RW[j].param_id,16)==0){
							parameter_RW[j].value = param_set.param_value;
						  while (USART2_words_to_send !=0 && USART2_current_TX_word !=0){heartbeat_sending_timer=0;target_coordinate_sending_timer=0;};
							mavlink_msg_param_value_pack(This_mav_sys_id, This_mav_comp_id, &TX_msg,
						    &parameter_RW[j].param_id[0],
								 parameter_RW[j].value, 
								 parameter_RW[j].param_type, 
								 total_param_count, j);
						USART2_words_to_send = mavlink_msg_to_send_buffer(USART2_TX_bufer, &TX_msg);
						USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
						STM_EVAL_LEDToggle(LED3); // Toggle LD3
						while(target_coordinate_sending_timer<10){};
						flash_saving_timer = 0;
						break;
						}
					}
				}
			}
			
			break;
			case MAVLINK_MSG_ID_GPS_RAW_INT:
			{//temp=24;
				memcpy(&gps_raw_int,&msg.payload64, MAVLINK_MSG_ID_GPS_RAW_INT_LEN);
			}
			break;
			case MAVLINK_MSG_ID_GPS_STATUS:
			{//temp=25;
				//mavlink_msg_gps_status_encode(This_mav_sys_id, This_mav_comp_id, &msg, );
				memcpy(&gps_status,&msg.payload64, MAVLINK_MSG_ID_GPS_STATUS_LEN);
       }
			break;
			case MAVLINK_MSG_ID_SCALED_IMU:
			{
				//temp=26;
			}
			break;
			case MAVLINK_MSG_ID_RAW_IMU :
			{
				//temp=27;
			}
			break;
			case MAVLINK_MSG_ID_RAW_PRESSURE:
			{
				//temp=28;
			}
			break;
			case  MAVLINK_MSG_ID_SCALED_PRESSURE:
			{
				//temp=29;
			}
			break;
			case  MAVLINK_MSG_ID_ATTITUDE:
			{//temp=30;
				//mavlink_msg_attitude_encode(mavlink_system.sysid, mavlink_system.compid, &RX_msg, );
				memcpy( &CurrentAttitude,&msg.payload64, MAVLINK_MSG_ID_ATTITUDE_LEN);	
				STM_EVAL_LEDToggle(LED5);
			}
			break;
			case  MAVLINK_MSG_ID_ATTITUDE_QUATERNION:
			{
				//temp=31;
			}
			break;
			case  MAVLINK_MSG_ID_LOCAL_POSITION_NED:
			{
				//temp=32;
			}
			break;
			case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
			{//temp=33; 
				memcpy( &current_GPS_data,&msg.payload64, MAVLINK_MSG_ID_GLOBAL_POSITION_INT_LEN);
				STM_EVAL_LEDToggle(LED6);
				
				if (gps_raw_int.satellites_visible == 0){
					current_GPS_data.alt = 500000;
				  current_GPS_data.lat = 50.403976f * 1e7f;
				  current_GPS_data.lon = 30.561912f * 1e7f;
				}
			}
			break;
			case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:
			{//temp=34;
				
			}
			break;
			case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
			{//temp=35;
				
			}
			break;
			case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW :
			{//temp=36;
				
			}
			break;
			case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST:
			{//temp=37;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST:
			{//temp=38;
				
			}
			break;
			case MAVLINK_MSG_ID_MISSION_ITEM:
			{//temp=39;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_REQUEST:
			{//temp=40;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_SET_CURRENT:
			{//temp=41
				;
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_CURRENT:
			{//temp=42;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
			{//temp=43;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_COUNT:
			{//temp=44;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_CLEAR_ALL:
			{//temp=45;
				
			}
			break;
			case  MAVLINK_MSG_ID_MISSION_ITEM_REACHED:
			{//temp=46;
				
			}
			break;
			case MAVLINK_MSG_ID_MISSION_ACK:
			{//temp=47;
				
			}
			break;
			case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN:
			{//temp=48;
				
			}
			break;
			case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN:
			{//temp=49;
				
			}
			break;
			case MAVLINK_MSG_ID_PARAM_MAP_RC:
			{
				//temp=50;
			}
			break;
			case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA:
			{
				//temp=54;
			}
			break;
			case MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA:
			{
				//temp=55;
			}
			break;
			case MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV :
			{
				//temp=61;
			}
			break;
			case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT :
			{
				//temp=62;
			}
			break;
			case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV:
			{//temp=63;
				//mavlink_msg_request_data_stream_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_request_data_stream_t* request_data_stream)
			}
			break;
			case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV:
			{
				//temp=64;
			}
			break;
			case MAVLINK_MSG_ID_RC_CHANNELS:
			{
				//temp=65;
			}
			break;
			case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
			{
				//temp=66;
			}
			break;
			case MAVLINK_MSG_ID_DATA_STREAM:
			{//temp=67;
				
			}
			break;
			case MAVLINK_MSG_ID_MANUAL_CONTROL:
			{
				//temp=69;
			}
			break;
			case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE:
			{//temp=70;
				/*
				if (msg.sysid==GCS_SYS_ID){
					int tmp;
					char zoom;
				  if (This_mav_sys_id == mavlink_msg_rc_channels_override_get_target_system(&msg)){
						alex_mos_ctrl_msg.param.speed_yaw   = mavlink_msg_rc_channels_override_get_chan6_raw(&msg)-1501;
						alex_mos_ctrl_msg.param.speed_pitch = mavlink_msg_rc_channels_override_get_chan7_raw(&msg)-1498;
						tmp = mavlink_msg_rc_channels_override_get_chan8_raw(&msg);
						alex_mos_ctrl_msg.param.control_mode = 1;
						 if (alex_mos_ctrl_msg.param.speed_yaw==-1500 && alex_mos_ctrl_msg.param.speed_pitch==-1500)
						 {
							 alex_mos_ctrl_msg.param.speed_yaw   = 0;
							 alex_mos_ctrl_msg.param.speed_pitch = 0;
							 alex_mos_ctrl_msg.param.control_mode = 0; 
						 }
						 if (tmp < 1200) zoom = 4;
						 if (tmp > 1800) zoom = 0;
						 if (tmp >1200 && tmp < 1800)zoom = 2;
						 suncti_m500_send_command(suncti_m500_Command_Zoom_in, zoom,0);
					}
				}
				*/
			}
			break;
			case MAVLINK_MSG_ID_MISSION_ITEM_INT:
			{
				//temp=73;
			}
			break;
			case MAVLINK_MSG_ID_VFR_HUD :
			{
				//temp=74;
			}
			break;			
			case MAVLINK_MSG_ID_COMMAND_INT:
			{
				//temp=75;
			}
			break;		 	 				 
			case MAVLINK_MSG_ID_COMMAND_LONG:
			{
				//temp=76;
			}
			break;
			case MAVLINK_MSG_ID_COMMAND_ACK:
			{
				//temp=77;
			}
			break;
			case   MAVLINK_MSG_ID_MANUAL_SETPOINT:
			{
				//temp=81;
			}
			break;
			case   MAVLINK_MSG_ID_SET_ATTITUDE_TARGET:
			{
				//temp=82;
			}
			break;
			case   MAVLINK_MSG_ID_ATTITUDE_TARGET:
			{
				//temp=83;
			}
			break;
			case   MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED:
			{
				//temp=84;
			}
			break;
			case   MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED:
			{
				//temp=85;
			}
			break;
			case   MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT:
			{
				//temp=86;
			}
			break;
			case   MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT:
			{
				//temp=87;
			}
			break;
			case  MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET:
			{
				//temp=89;
			}
			break;
			case MAVLINK_MSG_ID_HIL_STATE:
			{
				//temp=90;
			}
			break;
			case MAVLINK_MSG_ID_HIL_CONTROLS:
			{
				//temp=91;
			}
			break;
			case MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW :
			{
				//temp=92;
			}
			break;
			case MAVLINK_MSG_ID_OPTICAL_FLOW:
			{
				//temp=100;
			}
			break;
			case MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE:
			{
				//temp=101;
			}
			break;
			case MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE:
			{
				//temp=102;
			}
			break;
			case MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE:
			{
				//temp=103;
			}
			break;
			case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE:
			{
				//temp=104;
			}
			break;
			case MAVLINK_MSG_ID_HIGHRES_IMU:
			{
				//temp=105;
			}
			break;
			case MAVLINK_MSG_ID_OPTICAL_FLOW_RAD:
			{
				//temp=106;
			}
			break;			
			case MAVLINK_MSG_ID_HIL_SENSOR:
			{
				//temp=107;
			}
			break;
			case MAVLINK_MSG_ID_SIM_STATE:
			{
				//temp=108;
			}
			break;
			case MAVLINK_MSG_ID_RADIO_STATUS:
			{
				//temp=109;
			}
			break;
			case  MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL:
			{
				//temp=110;
			}
			break;
			case MAVLINK_MSG_ID_TIMESYNC :
			{
				//temp=111;
			}
			break;
			case  112:
			{
				//temp=112;
			}
			break;
			case  MAVLINK_MSG_ID_HIL_GPS:
			{
				//temp=113;
			}
			break;
			case  MAVLINK_MSG_ID_HIL_OPTICAL_FLOW:
			{
				//temp=114;
			}
			break;	
			case  MAVLINK_MSG_ID_HIL_STATE_QUATERNION:
			{
				//temp=115;
			}
			break;
			case  MAVLINK_MSG_ID_SCALED_IMU2:
			{
				//temp=116;
			}
			break;
			case  MAVLINK_MSG_ID_LOG_REQUEST_LIST:
			{
				//temp=117;
			}
			break;
			case MAVLINK_MSG_ID_LOG_ENTRY:
			{
				//temp=118;
			}
			break;
			case MAVLINK_MSG_ID_LOG_REQUEST_DATA:
			{
				//temp=119;
			}
			break;
			case  MAVLINK_MSG_ID_LOG_DATA :
			{
				//temp=120;
			}
			break;
			case  MAVLINK_MSG_ID_LOG_ERASE :
			{
				//temp=121;
			}
			break;
			case  MAVLINK_MSG_ID_LOG_REQUEST_END:
			{
				//temp=122;
			}
			break;
			case  MAVLINK_MSG_ID_GPS_INJECT_DATA :
			{
				//temp=123;
			}
			break;
			case  MAVLINK_MSG_ID_GPS2_RAW :
			{
				//temp=124;
			}
			break;
			case  MAVLINK_MSG_ID_POWER_STATUS :
			{
				//temp=125;
			}
			break;
			case  MAVLINK_MSG_ID_SERIAL_CONTROL :
			{
				//temp=126;
			}
			break;
			case  MAVLINK_MSG_ID_GPS_RTK :
			{
				//temp=127;
			}
			break;
			case  MAVLINK_MSG_ID_GPS2_RTK :
			{
				//temp=128;
			}
			break;
			case MAVLINK_MSG_ID_SCALED_IMU3 :
			{
				//temp=129;
			}
			break;			
			case  MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE:
			{
				//temp=130;
			}
			break;	
			case  MAVLINK_MSG_ID_ENCAPSULATED_DATA:
			{
				//temp=131;
			}
			break;	
			case  MAVLINK_MSG_ID_DISTANCE_SENSOR:
			{
				//temp=132;
			}
			break;
			case MAVLINK_MSG_ID_TERRAIN_REQUEST :
			{
				//temp=133;
			}
			break;
			case MAVLINK_MSG_ID_TERRAIN_DATA :
			{
				//temp=134;
			}
			break;
			case MAVLINK_MSG_ID_TERRAIN_CHECK :
			{
				//temp=135;
			}
			break;
			case MAVLINK_MSG_ID_TERRAIN_REPORT :
			{
				//temp=136;
			}
			break;
			case MAVLINK_MSG_ID_SCALED_PRESSURE2:
			{
				//temp=137;
			}
			break;
			case  MAVLINK_MSG_ID_ATT_POS_MOCAP:
			{
				//temp=138;
			}
			break;
			case  MAVLINK_MSG_ID_SET_ACTUATOR_CONTROL_TARGET:
			{
				//temp=139;
			}
			break;
			case  MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET:
			{
				//temp=140;
			}
			break;			
			case  MAVLINK_MSG_ID_BATTERY_STATUS:
			{
				//temp=147;
			}
			break;	
			case  MAVLINK_MSG_ID_AUTOPILOT_VERSION:
			{
				//temp=148;
			}
			break;
			case  149:
			{
				//temp=149;
			}
			break;
			case 150:// MAVLINK_MSG_ID_SENSOR_OFFSETS:
			{
				//temp=150;
			}
			break;			
			case 151://MAVLINK_MSG_ID_SET_CAM_SHUTTER://MAVLINK_MSG_ID_SET_MAG_OFFSETS 151 ARDUPILOT MEGA
			{
				//temp=151;
			}
			break;	
			case 152://MAVLINK_MSG_ID_IMAGE_TRIGGERED: //MAVLINK_MSG_ID_MEMINFO  in ardupilot mega
			{
				//temp=152;
			}
			break;		
			case 153://MAVLINK_MSG_ID_IMAGE_TRIGGER_CONTROL:
			{
				//temp=153;
			}
			break;						
			case 154://MAVLINK_MSG_ID_IMAGE_AVAILABLE://MAVLINK_MSG_ID_DIGICAM_CONFIGURE 154 ARDUPILOT MEGA
			{
				//temp=154;
			}
			break;
			case 155://MAVLINK_MSG_ID_DIGICAM_CONTROL : //ARDUPILOT MEGA
			{
				//temp=155;
			}
			break;
			case 156://MAVLINK_MSG_ID_MOUNT_CONFIGURE:
			{
				//temp=156;
			}
			break;
			case 157://MAVLINK_MSG_ID_MOUNT_CONTROL:
			{//temp=157;
				if(  mavlink_msg_mount_control_get_target_system(&msg)   == This_mav_sys_id 
					&& mavlink_msg_mount_control_get_target_component(&msg)== This_mav_comp_id)
				{
					memcpy(&mount_control ,&msg.payload64, MAVLINK_MSG_ID_MOUNT_CONTROL_LEN);
				}
			}
			break;
			case 158://MAVLINK_MSG_ID_MOUNT_STATUS:
			{
				//temp=158;
			}
			break;
			case 160://MAVLINK_MSG_ID_SET_POSITION_CONTROL_OFFSET://MAVLINK_MSG_ID_FENCE_POINT 160 ARDUPILOT MEGA
			{
				//temp=160;
			}
			break;
			case 161://MAVLINK_MSG_ID_FENCE_FETCH_POINT ://ARDUPILOT MEGA
			{
				//temp=161;
			}
			break;					
			case 162://MAVLINK_MSG_ID_FENCE_STATUS:
			{
				//temp=162;
			}
			break;	
			case  163://MAVLINK_MSG_ID_AHRS:
			{
				//temp=163;
			}
			break;
			case  164://MAVLINK_MSG_ID_SIMSTATE:
			{
				//temp=164;
			}
			break;				
			case 165://MAVLINK_MSG_ID_HWSTATUS: //ARDUPILOT MEGA 165
			{
				//temp=165;
			}
			break;			
			case 166://MAVLINK_MSG_ID_RADIO:
			{
				//temp=166;
			}
			break;
			case 167://MAVLINK_MSG_ID_LIMITS_STATUS : //ARDUPILOT MEGA 167
			{
				//temp=167;
			}
			break;
			case 168://MAVLINK_MSG_ID_WIND : //ARDUPILOT MEGA 168
			{
				//temp=168;
			}
			break;
			case 169://MAVLINK_MSG_ID_DATA16: //MAVLINK_MSG_ID_DATA16  ARDUPILOT MEGA
			{
				//temp=169;
			}
			break;
			case 170://MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT://MAVLINK_MSG_ID_DATA32  ARDUPILOT MEGA
			{
				//temp=170;
			}
			break;
			case 171://MAVLINK_MSG_MARKER://MAVLINK_MSG_ID_DATA64 171 ARDUPILOT MEGA
			{
				//temp=171;
			}
			break;
			case 172://MAVLINK_MSG_ID_RAW_AUX://MAVLINK_MSG_ID_DATA16  ARDUPILOT MEGA
			{
				//temp=172;
			}
			break;
			case 173://MAVLINK_MSG_ID_RANGEFINDER ://  ARDUPILOT MEGA
			{
				//temp=173;
			}
			break;
			case 174://MAVLINK_MSG_ID_AIRSPEED_AUTOCAL://MAVLINK_MSG_ID_DATA16  ARDUPILOT MEGA
			{
				//temp=174;
			}
			break;
			case 175://MAVLINK_MSG_ID_RALLY_POINT: // ARDUPILOT MEGA
			{
				//temp=175;
			}
			break;
			case  176://MAVLINK_MSG_ID_RALLY_FETCH_POINT : // ARDUPILOT MEGA
			{
				//temp=176;
			}
			break;
			case 177://MAVLINK_MSG_ID_COMPASSMOT_STATUS: // ARDUPILOT MEGA
			{
				//temp=177;
			}
			break;
			case 178://MAVLINK_MSG_ID_AHRS2: // ARDUPILOT MEGA
			{
				//temp=178;
			}
			break;
			case 179://MAVLINK_MSG_ID_CAMERA_STATUS : 
			{
				//temp=179;
			}
			break;				
			case 180://MAVLINK_MSG_ID_WATCHDOG_HEARTBEAT: //MAVLINK_MSG_ID_CAMERA_FEEDBACK 180  ARDUPILOT MEGA
			{
				//temp=180;
			}
			break;
			case 181://MAVLINK_MSG_ID_WATCHDOG_PROCESS_INFO:
			{
				//temp=181;
			}
			break;
			case 182://MAVLINK_MSG_ID_WATCHDOG_PROCESS_STATUS:// MAVLINK_MSG_ID_AHRS3 182  ARDUPILOT MEGA
			{
				//temp=182;
			}
			break;		
			case 183://MAVLINK_MSG_ID_WATCHDOG_COMMAND:
			{
				//temp=183;
			}
			break;
			case 186://MAVLINK_MSG_ID_LED_CONTROL: //ARDUPILOT MEGA 186
			{
				//temp=186;
			}
			break;
			case  MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA:
			{
				//temp=188;
			}
			break;
			case 190://MAVLINK_MSG_ID_PATTERN_DETECTED:
			{
				//temp=190;
			}
			break;
			case  191://MAVLINK_MSG_ID_POINT_OF_INTEREST: //MAVLINK_MSG_ID_MAG_CAL_PROGRESS 191 IN  ARDUPILOT MEGA
			{
				//temp=191;
			}
			break;
			case 192:// MAVLINK_MSG_ID_POINT_OF_INTEREST_CONNECTION: // MAVLINK_MSG_ID_MAG_CAL_REPORT 192 IN  ARDUPILOT MEGA
			{
				//temp=192;
			}
			break;
			case  193:// MAVLINK_MSG_ID_EKF_STATUS_REPORT:// ARDUPILOT MEGA
			{
				//temp=193;
			}
			break;
			case  194://MAVLINK_MSG_ID_PID_TUNING:
			{
				//temp=194;
			}
			break;
			case 195://MAVLINK_MSG_ID_BRIEF_FEATURE:
			{
				//temp=195;
			}
			break;
			case 200://MAVLINK_MSG_ID_ATTITUDE_CONTROL: //MAVLINK_MSG_ID_GIMBAL_REPORT 200 ARDUPILOT MEGA
			{
				//temp=200;
			}
			break;
			case 201://MAVLINK_MSG_ID_GIMBAL_CONTROL:
			{
				//temp=201;
			}
			break;
			case 202://MAVLINK_MSG_ID_GIMBAL_RESET:
			{
				//temp=202;
			}
			break;
			case 203://MAVLINK_MSG_ID_GIMBAL_AXIS_CALIBRATION_PROGRESS:
			{
				//temp=203;
			}
			break;
			case 204://MAVLINK_MSG_ID_GIMBAL_SET_HOME_OFFSETS:
			{
				//temp=204;
			}
			break;
			case 205://MAVLINK_MSG_ID_DETECTION_STATS: //MAVLINK_MSG_ID_GIMBAL_HOME_OFFSET_CALIBRATION_RESULT 205 ARDUPILOT MEGA
			{
				//temp=205;
			}
			break;
			case 206://MAVLINK_MSG_ID_ONBOARD_HEALTH: //MAVLINK_MSG_ID_GIMBAL_SET_FACTORY_PARAMETERS 206  ARDUPILOT MEGA
			{
				//temp=206;
			}
			break;
			case 207://MAVLINK_MSG_ID_GIMBAL_FACTORY_PARAMETERS_LOADED:
			{
				//temp=207;
			}
			break;
			case 208://MAVLINK_MSG_ID_GIMBAL_ERASE_FIRMWARE_AND_CONFIG:
			{
				//temp=208;
			}
			break;
			case 209://MAVLINK_MSG_ID_GIMBAL_PERFORM_FACTORY_TESTS:
			{
				//temp=209;
			}
			break;
			case 210://MAVLINK_MSG_ID_GIMBAL_REPORT_FACTORY_TESTS_PROGRESS:
			{
				//temp=210;
			}
			break;
			case 215://MAVLINK_MSG_ID_GOPRO_POWER_ON:
			{
				//temp=215;
			}
			break;
			case 216://MAVLINK_MSG_ID_GOPRO_POWER_OFF:
			{
				//temp=216;
			}
			break;
			case 217://MAVLINK_MSG_ID_GOPRO_POWER_COMMAND:
			{
				//temp=217;
			}
			break;
			case 218://MAVLINK_MSG_ID_GOPRO_RESPONSE: 
			{
				//temp=218;
			}
			break;
			case  241 : 
			{
				//temp=241;
			}
			break;
			case  MAVLINK_MSG_ID_V2_EXTENSION : 
			{
				//temp=248;
			}
			break;
			case  MAVLINK_MSG_ID_MEMORY_VECT: 
			{
				//temp=249;
			}
			break;
			case MAVLINK_MSG_ID_DEBUG_VECT: 
			{
				//temp=250;
			}
			break;
			case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT: 
			{
				//temp=251;
			}
			break;
			case MAVLINK_MSG_ID_NAMED_VALUE_INT: 
			{
				//temp=252;
			}
			break;
			case MAVLINK_MSG_ID_STATUSTEXT: 
			{
				//temp=253;
			}
			break;
			case MAVLINK_MSG_ID_DEBUG: 
			{
				//temp=254;
			}
			break;
			default:
				 {
				//temp=0x00;
				//Do nothing
				 }
			   break;
			}
		};
	}

		


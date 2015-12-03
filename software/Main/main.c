#include "main.h"
#define ABS(x)         (x < 0) ? (-x) : x

__IO uint32_t TimingDelay = 0;
__IO uint32_t UserButtonPressed = 0;
__IO float HeadingValue = 0.0f;  
float MagBuffer[3] = {0.0f}, AccBuffer[3] = {0.0f}, Buffer[3] = {0.0f};
uint8_t Xval, Yval = 0x00;
__IO uint8_t DataReady = 0;
__IO uint8_t PrevXferComplete = 1;
//__IO uint32_t USBConnectTimeOut = 100;

float fNormAcc,fSinRoll,fCosRoll,fSinPitch,fCosPitch = 0.0f, RollAng = 0.0f, PitchAng = 0.0f;
float fTiltedX,fTiltedY = 0.0f;

__IO uint64_t system_time=0;
__IO uint32_t time_boot =0;

int main(void)
{  
	alexmos_buffers_init ();
  Set_System();
  Leds_init ();	
	init_param_arry();
	MAVLink_init();
	//IR camera controls sending cursor switch on
	suncti_chek_status();
	suncti_m500_send_command(suncti_m500_Command_Cursor_display_hide,1,1);
		
  /* Infinite loop */
  while (1)
  {
		//Тут отправка  Heartbeat по мавлинк 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		send_heart_beat_if_its_need();
		
		//Тут отправка  координат подвеса // запрос координат по мавлинк 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		send_target_gimbal_coordinates_if_its_need();	
		
		//Sending of gps data of this UAV 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		send_gps_global_position_int_if_its_need ();
		
		// ЗАПРОС УГЛОВ С АЛЕКСМОС 
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		send_realtime_data_request_to_alexmos_if_its_need();
		
		// В1дправка команд керування в алексмос
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		send_control_msg_to_alexmos_if_its_need();
		
		// Used for small delay (10ms) beetween messages. If this delay smaler - can 
		//be problems with alexmos32 input buffer owerflow		
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		check_usart4_bysy();
		//Check new MAVLink messages and work with him
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		sort_mavlink_message();	
		
		//Chek new alexmos message 	 and work with him
		sort_alex_mos_message();
		
		//Finding GPS coordinates of gimbal point 
		find_target_coordinates(&current_lense_coordinates, &CurrentAttitude, &gimbal, &current_GPS_data);
		
		//Set lense to needed position referenced as GPS data (WGS86)		
		find_needed_gimbal_adj_angle_and_send
			(&current_lense_coordinates,&CurrentAttitude,&gimbal,&current_GPS_data,&mount_control,&alex_mos_ctrl_msg);
		//IR camera controls sending
		//suncti_m500_send_command(suncti_m500_Command_Cursor_display_hide,1,1);
	} // end of infinitie loop
}// end of main

//########################################################################################
//########################################################################################
//########################################################################################
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif


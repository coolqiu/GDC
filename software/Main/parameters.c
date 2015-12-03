//Page size 2048 bytes in this
//controller . If you change controller
// check  sections  for work with flash
#include <stdint.h>
#include <string.h>
#include "parameters.h"
#include "stm32f30x_flash.h"

convert_params_to_t convert_to;
uint16_t total_param_count;
uint8_t flash_saving_timer=0xff;
float yaw_offset = 0.0f;
float pitch_offset = 0.0f;

//Prarameters in format ID size 16 bytes 
//if strings shorter than 16 chars then must terminated NULL 
parameters_t parameter_RW[455];
#define FLASH_WRITE_START_ADR 0x8010000
const parameters_t parameter_RO[455]  __attribute__((section(".ARM.__at_0x8010000" ))) ={
{0.0f             , "CAM0_FCB_EV7500 ",1},//0  Camera 0	
{(uint32_t)(1920) , "CAM0_H_RESOLUTIO",3},//1
{(uint32_t)(1080) , "CAM0_V_RESOLUTIO",3},//2
{2.3f             , "CAM0_H_ANGLE_MIN",9},//3
{63.7f            , "CAM0_H_ANGLE_MAX",9},//4
{(uint32_t)(1)    , "CAM1_SUNCTI_M500",1},//5  Camera 1
{(uint32_t)(640)  , "CAM1_H_RESOLUTIO",3},//6
{(uint32_t)(480)  , "CAM1_V_RESOLUTIO",3},//7
{15.0f            , "CAM1_H_ANGLE_MIN",9},//8
{45.0f            , "CAM1_H_ANGLE_MAX",9},//9
{(uint32_t)(0)    , "CAMERA_DEFAULT  ",1},//10
{165.2f           , "GIMB_OFFSET_YAV ",9},//11  GIMBAL AXSYSES OFFSETS
{90.0f            , "GIMB_OFFSET_PITC",9},//12  DEPENDED FROM ENCODERS 
{0.0000f          , "GIMB_OFFSET_ROLL",9},//13  ABSOLUTE POSITION
{0.99f            , "FIRMVARE_VERSION",9},//14  
{1.0f             , "SEND_GLB_POS_INT",9},//15  SENDING INTERVALS , UNIT  SECONDS
{1.0f             , "SEND_HEARTBEAT_I",9},//16  
{0.2f             , "SEND_TARGET_POS ",9},//17  
{0.0f             , "GIMB_TO_UAV_YAV ",9},//18  GIMBAL TO UAV POSITION  
{0.0f             , "GIMB_TO_UAV_PITC",9},//19  REFERENCED  TO UAV 
{0.0f             , "GIMB_TO_UAV_ROLL",9},//20  COORDINATE SYSTEM
{0.0f             , "Gimbal_Kinematic",1},//21  Gimbal Kinematic Type 0 Yaw/Pitch/Roll 1 Yaw/Roll/Pitch

{0.00000, "   END PARAMS   ",0}// Terminator,ID must  beginning from Space end ended NULL  !!!!!!!!!
};
// value 8 bytes , type 1 bytes - total  9 bytes
//Type as MAV_PARAM_TYPE 
// 1	MAV_PARAM_TYPE_UINT8	8-bit unsigned integer
// 2	MAV_PARAM_TYPE_INT8	  8-bit signed integer
// 3	MAV_PARAM_TYPE_UINT16	16-bit unsigned integer
// 4	MAV_PARAM_TYPE_INT16	16-bit signed integer
// 5	MAV_PARAM_TYPE_UINT32	32-bit unsigned integer
// 6	MAV_PARAM_TYPE_INT32	32-bit signed integer
// 7	MAV_PARAM_TYPE_UINT64	64-bit unsigned integer
// 8	MAV_PARAM_TYPE_INT64	64-bit signed integer
// 9	MAV_PARAM_TYPE_REAL32	32-bit floating-point
// 10 MAV_PARAM_TYPE_REAL64	64-bit floating-point

uint16_t parameters_contain(char string[16])   //return 0xffff if parameters not contain string 
																							 //,else return position of this string 
																							 //in parameter_RW[POSITION] 
{ uint16_t count;
	for(count=0;count <= total_param_count ; count++)
	{	
		if(strncmp(string , parameter_RW[count].param_id,16) == 0)
		return (count);
	}
	return (0xffff);
}

//funciton copy to ram sawed params and calculate count of params
void init_param_arry(void)
{ uint8_t i=0;
	for (total_param_count=0;parameter_RO[total_param_count].param_id [0] != 0x20 ; total_param_count++)
	{
		parameter_RW[total_param_count].param_type = parameter_RO[total_param_count].param_type;
		parameter_RW[total_param_count].value =      parameter_RO[total_param_count].value;
		for (i=0;i <= 16;i++)
	  parameter_RW[total_param_count].param_id [i] = parameter_RO[total_param_count].param_id [i];
	};
}

void write_params_to_flash(void)
{ uint32_t *pointrer32;
	uint16_t *pointrer16;
	int16_t pages_for_erease_count = 0;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;/*FLASH complete erasure marks*/
	uint32_t Address = 0, WRITE_END_ADDR =0;
	const parameters_t end = {0.00000, "   END PARAMS   ",0};
	pages_for_erease_count = sizeof(parameters_t)*(total_param_count+1)/FLASH_MEMORY_PAGE_SIZE;
	
	/*Unlock FLASH*/
  FLASH_Unlock();
	/* Remove all hang flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
  while ((pages_for_erease_count >= 0) && (FLASHStatus == FLASH_COMPLETE))
    {
			FLASHStatus = FLASH_ErasePage(FLASH_WRITE_START_ADR + (FLASH_MEMORY_PAGE_SIZE * pages_for_erease_count));
			pages_for_erease_count--;
    }
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
	Address = FLASH_WRITE_START_ADR;
	WRITE_END_ADDR = FLASH_WRITE_START_ADR + sizeof(parameters_t)*(total_param_count);
	pointrer32 = (uint32_t *)&parameter_RW[0].value;
	while((Address <=WRITE_END_ADDR)&&(FLASHStatus == FLASH_COMPLETE))
		{	
			FLASHStatus = FLASH_ProgramWord(Address, *pointrer32);
			Address+=4;
			pointrer32++;
		}	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Terminating 
	Address-=4;
  WRITE_END_ADDR = Address + sizeof(parameters_t);		
	pointrer16 = (uint16_t *)&end.value;
  while((Address <=WRITE_END_ADDR)&&(FLASHStatus == FLASH_COMPLETE))
		{	
			FLASHStatus = FLASH_ProgramHalfWord(Address, *pointrer16);
			Address+=2;
			pointrer16++;
		}	
  FLASH_Lock();	
	reload_parameters();
}
void reload_parameters(void)
{
uint16_t	temp; 
temp = parameters_contain("GIMB_OFFSET_YAV ");
if(temp !=0xffff) yaw_offset = parameter_RW[temp].value;
temp = parameters_contain("GIMB_OFFSET_PITC");
if(temp !=0xffff) pitch_offset = parameter_RW[temp].value;
}




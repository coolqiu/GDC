/*
 * lense_coordinate_finding_h
 *
 *  Created on: 20_05_2015
 *      Author: Мох
 */

#ifndef LENSE_COORDINATE_FINDING_H_
#define LENSE_COORDINATE_FINDING_H_
#include "math.h"
#include <stdint.h>
#include "mavlink.h"
#include "alexmos32.h"
#include "parameters.h"

#define Pi                 (float)3.14159265358f
#define DEGREES_TO_RADIANS (float)(Pi/180.0f)
#define RADIANS_TO_DEGREES (float)(180.0f/Pi)
#define cl_earth_radius    (float)6371000.00f     //радиус земли (средний) итого в метрах
#define one_degrees_of_equator  (float)111000.00  // meters
#define one_degrees_of_meridian (float)111300.00  // meters
#define one_radian_of_equator  (float)6359831.525952  // meters
#define one_radian_of_meridian (float)6377020.259806  // meters

typedef struct __point_and_angles_t
{
	float x;
	float y;
	float z;
	float alfa;
	float beta;
	float gamma;
} point_and_angles_t;
typedef struct __lense_coordinates_t 
{
	float target_latitude;    //WGS86 DEGREES
	float target_longtitude;  //WGS86 DEGREES
	float target_altitude_ASL;//IN METERS
	float gimbal_latitude;    //WGS86 DEGREES
	float gimbal_longtitude;  //WGS86 DEGREES
	float gimbal_altitude_ASL;//IN METERS
	float gimbal_altitude_REL;//IN METERS
	float camera_angle_YAW;   //in degrees , referenced to magnetic north 0 -> north 
	float camera_angle_PITCH; //in degrees , referenced to horizont , 0 -> camera axis in a horizontal position
	float camera_angle_ROLL;  //in degrees , referenced to horizont , 0 -> camera plate in a horizontal position
	uint32_t time_boot_ms;
} lense_coordinates_t;

extern lense_coordinates_t current_lense_coordinates;

float find_to_target_distance(float l_altitude_AGL,float f_angle);
float find_target_altitude_ASL(float f_altitude_of_UAV_ASL, float f_tilt_angle,float to_target_distance);
void find_target_coordinates(lense_coordinates_t* , mavlink_attitude_t* ,__gimbal*, mavlink_global_position_int_t* );
void find_needed_gimbal_adj_angle_and_send(lense_coordinates_t* lense, mavlink_attitude_t* Attitude  ,	__gimbal* gimbal,
		mavlink_global_position_int_t* GPS,mavlink_mount_control_t* position ,alex_mos_control* ctrl_msg ); 
void rotate_coordinate_system_with_point (point_and_angles_t*);
#endif /* LENSE_COORDINATE_FINDING_H_ */


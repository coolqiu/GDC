#include "lense_coordinate_finding.h"

lense_coordinates_t current_lense_coordinates;
point_and_angles_t point;
// ������� ��������� ���������� , ���� �������� ������ , ���������� ��������� � ��������� current_lense_coordinates
void find_target_coordinates(lense_coordinates_t* lense_coordinates,  mavlink_attitude_t* Attitude  ,__gimbal* gimbal, mavlink_global_position_int_t* GPS_data)//(float f_current_uav_latitude,float f_current_uav_longtitude,
							 //float f_current_uav_alitude_ASL , float f_current_uav_alitude_AGL , float f_azimuth_angle , float f_tilt_angle)
{

if (Attitude->time_boot_ms != lense_coordinates->time_boot_ms){
lense_coordinates->time_boot_ms = Attitude->time_boot_ms;
float f_distance_to_target;
float f_katet_length_beetwen_UAV_and_target;
float proection;
float delta_angle;
// �������� �������� � ����� , ��������� � ������� �������� 
point.alfa  = gimbal->frame.cam_angle.yaw   - parameter_RW[11].value * DEGREES_TO_RADIANS;	
point.beta  =	gimbal->frame.cam_angle.pitch - parameter_RW[12].value * DEGREES_TO_RADIANS; 
point.gamma = gimbal->frame.cam_angle.roll  - parameter_RW[13].value * DEGREES_TO_RADIANS;  
// ������� ��������� ����� ��������� �� 1 ���� �� ������ ����������� ���� �������� ������� 
//� ������� ��������� ���� .
switch ((int)parameter_RW[21].value) { 
	case 0 :{// if gimbal kinematic is Yaw/Pitch/Roll
		point.x = cosf( point.alfa ) * cosf( point.beta  );// if gimbal do not hawe Roll 
		point.y = sinf( point.alfa ) * cosf( point.beta  );// then Roll angle must be zero
		point.z = sinf( point.beta ) ;
		break;
		}
	case 1 :{// if gimbal kinematic is Yaw/Roll/Pitch
		point.z = sinf( point.beta ) * cosf( point.gamma );	
		point.x = cosf( point.alfa ) * cosf( point.beta  ) + point.z * sinf( point.gamma ); 
		point.y = sinf( point.alfa ) * cosf( point.beta  ) - point.x * sinf( point.gamma );
		
		break;
	}
	default:{
		point.x = cosf( point.alfa ) * cosf( point.beta  );// if gimbal do not hawe Roll 
		point.y = sinf( point.alfa ) * cosf( point.beta  );// then Roll angle must be zero
		point.z = sinf( point.beta ) ;
	}
}

// ��������������� ���������� ����� ����� � ���������� ���������������� ������� ��������� 
// ���������� �� ���� ���� � , ����� ������� , ��������� �� ���������������� ������� ��������� 
// ���������� �����(������� , �  ������  ����������  ��������� ����������� � ����� ����� �����

//�������� �������� ����� ��������� ������� �� ���������  � ����
point.alfa  = Attitude->yaw   - parameter_RW[18].value*DEGREES_TO_RADIANS ;
point.beta  = Attitude->pitch - parameter_RW[19].value*DEGREES_TO_RADIANS ;
point.gamma = Attitude->roll  - parameter_RW[20].value*DEGREES_TO_RADIANS ;

rotate_coordinate_system_with_point(&point);

// ����� �������  �� ����4��� ������������ ��������� ������ � ������� � ����� ����������� 
// ���� �������� ������� � ������ �  ����� x1,y1,z1 , ����������� � ����� , ���� ������� ������

// ���� �������� ���� ������� �� ��������� �  ���������������� ������, � ������� ����������� 
// � ����� �� ����� ����������� ���� �������� �������
lense_coordinates->camera_angle_YAW   =  acosf(point.x);
lense_coordinates->camera_angle_PITCH =  asinf(point.z);
lense_coordinates->camera_angle_ROLL  =  acosf(point.y);
	
if (lense_coordinates->camera_angle_PITCH < 0.01f &&    //���������� "��������������"
	  lense_coordinates->camera_angle_PITCH > -0.01f )    // � , ��� ����� , ���������� 
lense_coordinates->camera_angle_PITCH = 0.01f;          //��������� ��  �������������
		
f_distance_to_target = tan(lense_coordinates->camera_angle_PITCH+Pi/2);
if (f_distance_to_target < 0)f_distance_to_target *=-1;

lense_coordinates->gimbal_altitude_ASL = GPS_data->alt;
lense_coordinates->gimbal_altitude_REL = GPS_data->relative_alt;

f_distance_to_target *= (GPS_data->alt/1000 - lense_coordinates->target_altitude_ASL);  
f_katet_length_beetwen_UAV_and_target = f_distance_to_target * cosf( lense_coordinates->camera_angle_PITCH);
proection = f_katet_length_beetwen_UAV_and_target * cosf( lense_coordinates->camera_angle_YAW );
delta_angle = proection/one_degrees_of_meridian;
lense_coordinates->target_latitude = (float)(GPS_data->lat)/1e7f+delta_angle; 
//����� ������ ����
proection = f_katet_length_beetwen_UAV_and_target * sinf(lense_coordinates->camera_angle_YAW ); // ���� ������� ������� ���� , ������� � �������� �� ��� ������������  ��������
delta_angle=proection/(cosf((float)GPS_data->lat /1e7f * DEGREES_TO_RADIANS )*one_degrees_of_equator);
lense_coordinates->target_longtitude = GPS_data->lon /1e7f + delta_angle;
//����� ������� ����
	}
}

void find_needed_gimbal_adj_angle_and_send(
		mavlink_attitude_t* Attitude  ,							//Current UAV attitude
		__gimbal* gimbal, 													//Current gimbal angles from IMU , camera and encoder			
		mavlink_global_position_int_t* GPS, 		//Current GPS data where  we is now
		mavlink_mount_control_t* position , 				//To where we need see command from ground
		alex_mos_control* ctrl_msg  )               //Output control signals 
{
float a;
if (position->input_a !=0x7FFFFFFF ) // ������� ��� ���� ������� ����������� ��� ��������� ����� �����
	{
		//��������� ���������� ��������� (�������) ����� � ������� ��������� ��������������
		point.z = GPS->alt/1000 - position->input_c/100;
		point.x = (position->input_a - GPS->lat)/1e7f * one_degrees_of_meridian ;
		point.y = (position->input_b - GPS->lon)/1e7f * one_degrees_of_equator 
					* cosf((float)GPS->lat /1e7f * DEGREES_TO_RADIANS ) ;
		//������� ���������� ���� ����� � ������� ��������� ����� ��������� 
		//������� � ���� ����� ���������������� ���������� ������ ��������������� 
		//��� �� ���� ���� �����  ����  ��������� �������
		//�������� �������� ����� ��������� ������� �� ���������  � ����
		point.alfa  = Attitude->yaw   - parameter_RW[18].value*DEGREES_TO_RADIANS ;
		point.beta  = Attitude->pitch - parameter_RW[19].value*DEGREES_TO_RADIANS ;
		point.gamma = Attitude->roll  - parameter_RW[20].value*DEGREES_TO_RADIANS ;
		//������ ������� 
		rotate_coordinate_system_with_point(&point);
		//����� ������� ������� �������� ����� ������� ��������� �� ���� ������ ����� �������
		point.alfa  = gimbal->frame.cam_angle.yaw   - parameter_RW[11].value * DEGREES_TO_RADIANS;	
		point.beta  =	gimbal->frame.cam_angle.pitch - parameter_RW[12].value * DEGREES_TO_RADIANS; 
		point.gamma = gimbal->frame.cam_angle.roll  - parameter_RW[13].value * DEGREES_TO_RADIANS;  
		rotate_coordinate_system_with_point(&point);
		//��������� ���� ������� �� ��������� � ��������� ������� ��������� ��� �� ��������
		//������ �������� ��� ��������� ���������� ��� ������� � ������� �����.
		a = sqrt(point.x * point.x + point.y * point.y + point.z * point.z ); //������ ������� 
		point.alfa = acosf(point.x/a);
		point.beta = acosf (point.y/a);
		point.gamma = acosf (point.z/a);
		
		position->input_a = 0x7FFFFFFF;
	}
}



void rotate_coordinate_system_with_point (point_and_angles_t* pa)
{
float x2,y2,z2;	
y2 = pa->y * cosf( pa->gamma ) - pa->z * sinf( pa->gamma );
z2 = pa->y * sinf( pa->gamma ) + pa->z * cosf( pa->gamma );
pa->y = y2;
pa->z = z2;

//������ ������� ������ ��� y �� ���� beta

x2 = pa->z * sinf( pa->beta ) + pa->x * cosf( pa->beta );
z2 = pa->z * cosf( pa->beta ) - pa->x * sinf( pa->beta );
pa->x = x2;
pa->z = z2;

//������ ������� ������ ��� z �� ���� alfa

x2 = pa->x * cosf( pa->alfa ) - pa->y * sinf( pa->alfa );
y2 = pa->x * sinf( pa->alfa ) + pa->y * cosf( pa->alfa );
pa->x = x2;
pa->y = y2;
}





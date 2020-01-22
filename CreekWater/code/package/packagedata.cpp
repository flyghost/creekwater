#include "packagedata.h"


//数传0x10
//拓空者0x05
int device_name = 0x00;
bool device_find = false;
bool device_0x10 = false;//数传是否连接
bool device_0x05 = false;//拓空者是否连接
bool device_0x04 = false;//领航者是否连接

//float g_f_angle_rol;//横滚
//float g_f_angle_pit;//俯仰
//float g_f_angle_yaw;//偏航

//int32_t g_alt;
//uint8_t g_fly_mode;//飞行模式：1-姿态飞行  2-定高飞行  3-定点
//uint8_t g_armed;//0：上锁   1：解锁

//int16_t g_THR;
//int16_t g_YAW;
//int16_t g_ROL;
//int16_t g_PIT;
//int16_t g_AUX1;
//int16_t g_AUX2;
//int16_t g_AUX3;
//int16_t g_AUX4;
//int16_t g_AUX5;
//int16_t g_AUX6;


//int16_t g_ACC_X;
//int16_t g_ACC_Y;
//int16_t g_ACC_Z;
//int16_t g_GYRO_X;
//int16_t g_GYRO_Y;
//int16_t g_GYRO_Z;
//int16_t g_MAG_X;
//int16_t g_MAG_Y;
//int16_t g_MAG_Z;

//uint16_t g_PWM_MOTO1;
//uint16_t g_PWM_MOTO2;
//uint16_t g_PWM_MOTO3;
//uint16_t g_PWM_MOTO4;
//uint16_t g_PWM_MOTO5;
//uint16_t g_PWM_MOTO6;
//uint16_t g_PWM_MOTO7;
//uint16_t g_PWM_MOTO8;


//float g_f_ALT_BAR;
//float g_f_ALT_ADDITION;

//float g_f_Voltage;
//float g_f_Current;


////GPS信息
//uint8_t g_gps_state;//定位状态
//uint8_t g_gps_satellite_num;//卫星数量

//float g_gps_longitude;// * 10 000 000
//float g_gps_latitude;// * 10 000 000
//float g_gps_angle;// * 10度

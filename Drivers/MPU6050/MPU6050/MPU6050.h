#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "STM32_I2C.h"


typedef struct
{
	float acc;
	float gyro;
	float angle_last;
	float angle;
}angle_t;

typedef struct
{
	float x;
	float y;
	float z;
}point_t;



int MPU_init(void);								// 初始化MPU6050模块，返回0表示失败
void MPU_getdata(void);						// 获取六轴数据和姿态角，更新全局变量
void MPU6050_ReturnTemp(float*Temperature);	// 读取MPU6050器件温度

extern float q0, q1, q2, q3;			// 四元数
extern __IO float fAX, fAY, fAZ;				// 三个姿态角（pitch俯仰角, roll滚转角, yaw偏航角）
extern __IO short ax, ay, az, gx, gy, gz;	// 六轴数据

void 	mpu6050_read6axis	(void);
void 	get_angle			(void);
uint8   gyro_detect         (void);

extern angle_t pitch, roll;
#endif

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



int MPU_init(void);								// ��ʼ��MPU6050ģ�飬����0��ʾʧ��
void MPU_getdata(void);						// ��ȡ�������ݺ���̬�ǣ�����ȫ�ֱ���
void MPU6050_ReturnTemp(float*Temperature);	// ��ȡMPU6050�����¶�

extern float q0, q1, q2, q3;			// ��Ԫ��
extern __IO float fAX, fAY, fAZ;				// ������̬�ǣ�pitch������, roll��ת��, yawƫ���ǣ�
extern __IO short ax, ay, az, gx, gy, gz;	// ��������

void 	mpu6050_read6axis	(void);
void 	get_angle			(void);
uint8   gyro_detect         (void);

extern angle_t pitch, roll;
#endif
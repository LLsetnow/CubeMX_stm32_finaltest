#ifndef __key_H
#define __key_H

#include "stm32f407xx.h"
#include "stdint.h"
#include "main.h"


#define KEY_LIST                    {K1_Pin,K2_Pin,K3_Pin,K4_Pin,K5_Pin,K6_Pin}
#define KEY_PORT_LIST               {K1_GPIO_Port, K2_GPIO_Port,K3_GPIO_Port, K4_GPIO_Port, K5_GPIO_Port, K6_GPIO_Port}


#define KEY_RELEASE_LEVEL           (GPIO_PIN_RESET)// ������Ĭ��״̬ Ҳ���ǰ����ͷ�״̬�ĵ�ƽ
#define KEY_TOUCH_LEVEL             (GPIO_PIN_SET)  // ��������״̬�ĵ�ƽ
#define KEY_MAX_SHOCK_PERIOD        (10       )     // �����������ʱ�� ��λ���� �������ʱ�����źŻᱻ��Ϊ���Ӳ�����
#define KEY_LONG_PRESS_PERIOD       (1000     )     // ��С����ʱ�� ��λ����


typedef enum
{
    KEY_UP,  
    KEY_LEFT,      
    KEY_RIGHT,    
    KEY_DOWN,           
    KEY_DL,
    KEY_DR,   
    KEY_NUMBER,
}key_index_enum;


typedef enum
{
    KEY_RELEASE,         // �����ͷ�״̬
    KEY_CHECK_SHOCK,     // ��������״̬
    KEY_SHORT_PRESS,     // �����̰�״̬
    KEY_LONG_PRESS,      // ��������״̬
}key_state_enum;



void            key_scanner     (void);                 // ����״̬ɨ��
key_state_enum  key_get_state   (key_index_enum key_n); // ��ȡ����״̬
uint8           key_init        (uint32 period);        // ������ʼ��
void            key_beep        (uint8 keynum);         // ������Ч




#endif	
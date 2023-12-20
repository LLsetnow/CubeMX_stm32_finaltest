#ifndef __key_H
#define __key_H

#include "stm32f407xx.h"
#include "stdint.h"
#include "main.h"


#define KEY_LIST                    {K1_Pin,K2_Pin,K3_Pin,K4_Pin,K5_Pin,K6_Pin}
#define KEY_PORT_LIST               {K1_GPIO_Port, K2_GPIO_Port,K3_GPIO_Port, K4_GPIO_Port, K5_GPIO_Port, K6_GPIO_Port}


#define KEY_RELEASE_LEVEL           (GPIO_PIN_RESET)// 按键的默认状态 也就是按键释放状态的电平
#define KEY_TOUCH_LEVEL             (GPIO_PIN_SET)  // 按键按下状态的电平
#define KEY_MAX_SHOCK_PERIOD        (10       )     // 按键消抖检测时长 单位毫秒 低于这个时长的信号会被认为是杂波抖动
#define KEY_LONG_PRESS_PERIOD       (1000     )     // 最小长按时长 单位毫秒


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
    KEY_RELEASE,         // 按键释放状态
    KEY_CHECK_SHOCK,     // 按键消抖状态
    KEY_SHORT_PRESS,     // 按键短按状态
    KEY_LONG_PRESS,      // 按键长按状态
}key_state_enum;



void            key_scanner     (void);                 // 按键状态扫描
key_state_enum  key_get_state   (key_index_enum key_n); // 获取按键状态
uint8           key_init        (uint32 period);        // 按键初始化
void            key_beep        (uint8 keynum);         // 按键音效




#endif	
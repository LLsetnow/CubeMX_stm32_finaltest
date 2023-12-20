#include "key.h"
#include "stdint.h"
#include "Beep.h"

static uint32               scanner_period = 0;             // 按键的扫描周期
static uint32               key_press_time[KEY_NUMBER];     // 按键信号持续时长
static key_state_enum       key_state[KEY_NUMBER];          // 按键状态

static const uint16  key_index[KEY_NUMBER] = KEY_LIST;
static GPIO_TypeDef*  key_port_index[KEY_NUMBER] = KEY_PORT_LIST;


//按键状态扫描
void key_scanner (void)
{
    uint8 i = 0;
    for(i = 0; i < KEY_NUMBER - 2; i ++)
    {
        switch(key_state[i])
        {
            case KEY_RELEASE:
                if(KEY_TOUCH_LEVEL != HAL_GPIO_ReadPin(key_port_index[i], key_index[i]))
                {
                    if(++ key_press_time[i] >= KEY_MAX_SHOCK_PERIOD / scanner_period)
                    {
                        key_state[i] = KEY_SHORT_PRESS;
                    }
                    else
                    {
                        key_state[i] = KEY_CHECK_SHOCK;
                    }
                }
                break;
            case KEY_CHECK_SHOCK:
                if(KEY_TOUCH_LEVEL != HAL_GPIO_ReadPin(key_port_index[i], (key_index[i])))
                {
                    if(++ key_press_time[i] >= KEY_MAX_SHOCK_PERIOD / scanner_period)
                    {
                        key_state[i] = KEY_SHORT_PRESS;
                    }
                }
                else
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;
            case KEY_SHORT_PRESS:
                if(++ key_press_time[i] >= KEY_LONG_PRESS_PERIOD / scanner_period)
                {
                    key_state[i] = KEY_LONG_PRESS;
                }
                if(KEY_TOUCH_LEVEL == HAL_GPIO_ReadPin(key_port_index[i], key_index[i]))
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;
            case KEY_LONG_PRESS:
                if(KEY_TOUCH_LEVEL == HAL_GPIO_ReadPin(key_port_index[i], (key_index[i])))
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;

        }
    }
    
    for(i = KEY_NUMBER - 2; i < KEY_NUMBER; i ++)
    {
        switch(key_state[i])
        {
            case KEY_RELEASE:
                if(KEY_RELEASE_LEVEL != HAL_GPIO_ReadPin(key_port_index[i], key_index[i]))
                {
                    if(++ key_press_time[i] >= KEY_MAX_SHOCK_PERIOD / scanner_period)
                    {
                        key_state[i] = KEY_SHORT_PRESS;
                    }
                    else
                    {
                        key_state[i] = KEY_CHECK_SHOCK;
                    }
                }
                break;
            case KEY_CHECK_SHOCK:
                if(KEY_RELEASE_LEVEL != HAL_GPIO_ReadPin(key_port_index[i], (key_index[i])))
                {
                    if(++ key_press_time[i] >= KEY_MAX_SHOCK_PERIOD / scanner_period)
                    {
                        key_state[i] = KEY_SHORT_PRESS;
                    }
                }
                else
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;
            case KEY_SHORT_PRESS:
                if(++ key_press_time[i] >= KEY_LONG_PRESS_PERIOD / scanner_period)
                {
                    key_state[i] = KEY_LONG_PRESS;
                }
                if(KEY_RELEASE_LEVEL == HAL_GPIO_ReadPin(key_port_index[i], key_index[i]))
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;
            case KEY_LONG_PRESS:
                if(KEY_RELEASE_LEVEL == HAL_GPIO_ReadPin(key_port_index[i], (key_index[i])))
                {
                    key_state[i] = KEY_RELEASE;
                    key_press_time[i] = 0;
                }
                break;

        }
    }
}



//获取按键状态
key_state_enum key_get_state (key_index_enum key_n)
{
    return key_state[key_n];
}


//按键初始化
uint8 key_init (uint32 period)
{
    uint8 loop_temp = 0;


    for(loop_temp = 0; loop_temp < KEY_NUMBER; loop_temp ++)
    {
        key_state[loop_temp] = KEY_RELEASE;
    }
    scanner_period = period;
    return 0;
}


void key_beep(uint8 keynum)
{
    switch(keynum)
    {
        case KEY_UP:    Buzzer_Beep(500 , 5, 50); break;
        case KEY_LEFT:  Buzzer_Beep(1000, 5, 50); break;
        case KEY_RIGHT: Buzzer_Beep(1500, 5, 50); break;
        case KEY_DOWN:  Buzzer_Beep(2000, 5, 50); break;
        case KEY_DL:    Buzzer_Beep(2500, 5, 50); break;
        case KEY_DR:    Buzzer_Beep(3000, 5, 50); break;
        
        
    }

}



















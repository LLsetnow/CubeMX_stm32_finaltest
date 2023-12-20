
#include "tim.h"
#include "variables.h"
#include "stdio.h"

// 设置PWM频率和占空比
void Set_Buzzer_Frequency_And_DutyCycle(uint32_t frequency, uint32_t dutyCycle)
{
    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq() * 2;
    uint32_t prescaler = (timer_clock / frequency / 1000) - 1; 
    uint32_t period = 1000 - 1;					 		// 1000分频
    uint32_t pulse = (dutyCycle * period) / 100; 		// 计算占空比

    htim3.Init.Prescaler = prescaler;
    htim3.Init.Period = period;
    HAL_TIM_PWM_Init(&htim3);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

    
}

/*		控制蜂鸣器响		*/
// 参数说明： frequency 	蜂鸣器频率 			单位： Hz
// 参数说明： volume 	蜂鸣器响度（占空比） 	50 即为 50%
// 参数说明： duration 	蜂鸣器响的时间 		单位： ms
void Buzzer_Beep(uint32_t frequency, uint32_t volume, uint32_t duration)
{
    Set_Buzzer_Frequency_And_DutyCycle(frequency, volume);
	
	//设置定时器5的周期
    htim5.Init.Period = duration * 500   - 1;
    printf("period = %d\r\n", duration * 500  - 1);
	
    
    HAL_TIM_Base_Init(&htim5);
	
	//启动定时器5和PWM
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}


//tim5_count 为全局变量
// 定时器5的回调函数
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == TIM5)
//    {
//		static uint32 tim5_count = 0; 
//		tim5_count++;
//		
//    if (htim->Instance == TIM5)
//    {
//		tim5_count++;

//		if(tim5_count == 2)
//		{
//			tim5_count = 0;
//			// 停止PWM和定时器3
//			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//			HAL_TIM_Base_Stop_IT(&htim5);
//		}

//    }
//    }
//}










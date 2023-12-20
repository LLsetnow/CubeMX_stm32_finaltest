
#include "tim.h"




// ����PWMƵ�ʺ�ռ�ձ�
void Set_Buzzer_Frequency_And_DutyCycle(uint32_t frequency, uint32_t dutyCycle)
{
    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq() * 2;
    uint32_t prescaler = (timer_clock / frequency / 1000) - 1; 
    uint32_t period = 1000 - 1; // 1000��Ƶ���õ�����Ϊ0.1%
    uint32_t pulse = (dutyCycle * period) / 100; // ����ռ�ձ�

    htim3.Init.Prescaler = prescaler;
    htim3.Init.Period = period;
    HAL_TIM_PWM_Init(&htim3);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

// ���Ʒ�������
void Buzzer_Beep(uint32_t frequency, uint32_t volume, uint32_t duration)
{
    Set_Buzzer_Frequency_And_DutyCycle(frequency, volume);
    HAL_Delay(duration);
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1); // ֹͣ������
}



//int main(void)
//{
//    HAL_Init();
//    MX_TIM3_Init();

//    // ���Է�������Ƶ��1000Hz��ռ�ձ�50%������ʱ��1000ms
//    Buzzer_Beep(1000, 50, 1000);

//    while (1)
//    {
//    }
//}














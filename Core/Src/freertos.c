/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "usart.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <ctype.h>

#include "GUI.h"
#include "lcd_drv.h"
#include "DS18B20.h"
#include "touch.h"
#include "DIALOG.h"
#include "Beep.h"
#include "GUI_func.h"
#include "key.h"
#include "variables.h"
#include "music.h"
#include "MPU6050.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WIDTH 	320
#define HIGH	240
#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */



/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */






/* USER CODE END Variables */
/* Definitions for MainTask */
osThreadId_t MainTaskHandle;
const osThreadAttr_t MainTask_attributes = {
  .name = "MainTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskGUI */
osThreadId_t TaskGUIHandle;
const osThreadAttr_t TaskGUI_attributes = {
  .name = "TaskGUI",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTaskKey */
osThreadId_t myTaskKeyHandle;
const osThreadAttr_t myTaskKey_attributes = {
  .name = "myTaskKey",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for myTaskAlarm */
osThreadId_t myTaskAlarmHandle;
const osThreadAttr_t myTaskAlarm_attributes = {
  .name = "myTaskAlarm",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTaskMPU6050 */
osThreadId_t myTaskMPU6050Handle;
const osThreadAttr_t myTaskMPU6050_attributes = {
  .name = "myTaskMPU6050",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


/* USER CODE END FunctionPrototypes */

void StartMainTask(void *argument);
void StartTaskGUI(void *argument);
void StartTaskKey(void *argument);
void StartTaskAlarm(void *argument);
void StartTaskMPU6050(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MainTask */
  MainTaskHandle = osThreadNew(StartMainTask, NULL, &MainTask_attributes);

  /* creation of TaskGUI */
  TaskGUIHandle = osThreadNew(StartTaskGUI, NULL, &TaskGUI_attributes);

  /* creation of myTaskKey */
  myTaskKeyHandle = osThreadNew(StartTaskKey, NULL, &myTaskKey_attributes);

  /* creation of myTaskAlarm */
  myTaskAlarmHandle = osThreadNew(StartTaskAlarm, NULL, &myTaskAlarm_attributes);

  /* creation of myTaskMPU6050 */
  myTaskMPU6050Handle = osThreadNew(StartTaskMPU6050, NULL, &myTaskMPU6050_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartMainTask */
/**
  * @brief  Function implementing the MainTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartMainTask */
void StartMainTask(void *argument)
{
  /* USER CODE BEGIN StartMainTask */
    key_init    (1);
    MPU_init    ();
    GUI_My_Init ();
  /* Infinite loop */
  for(;;)
  {
    //闹铃图表闪烁
    if(flag_alarm) warning();
      
    osDelay(1);
  }
  /* USER CODE END StartMainTask */
}

/* USER CODE BEGIN Header_StartTaskGUI */
/**
* @brief Function implementing the TaskGUI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskGUI */
void StartTaskGUI(void *argument)
{
  /* USER CODE BEGIN StartTaskGUI */
  /* Infinite loop */

    
	osDelay(100);
	GUI_Init();
    GUI_My_Init();
    GUI_Clear();
    
    GUI_DrawBitmap(&bmHDU, 100, 20);
    osDelay(1000);
     GUI_DispStringAt("简易电子钟设计", 80, 140);
    osDelay(2000);
    GUI_DispStringAt("22040932徐晨茗", 80, 170);
    osDelay(2000);
    
    //菜单初始化
    menu_init();

    for(;;)
    {
        //menu0 1 时间实时刷新
        if(gui_menu == 0 || gui_menu == 1) show_time();
        
        //基于按键的界面切换
        switch_menu();
        
        osDelay(1);
    }
  /* USER CODE END StartTaskGUI */
}

/* USER CODE BEGIN Header_StartTaskKey */
/**
* @brief Function implementing the myTaskKey thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskKey */
void StartTaskKey(void *argument)
{
  /* USER CODE BEGIN StartTaskKey */
    
  /* Infinite loop */
  for(;;)
  {
    //按键扫描
    key_scanner();
    osDelay(1);
  }
  /* USER CODE END StartTaskKey */
}

/* USER CODE BEGIN Header_StartTaskAlarm */
/**
* @brief Function implementing the myTaskAlarm thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskAlarm */
void StartTaskAlarm(void *argument)
{
  /* USER CODE BEGIN StartTaskAlarm */
  /* Infinite loop */
    for(;;)
    {
        //闹铃判断
        alarm_detect();
        osDelay(1);
    }
  /* USER CODE END StartTaskAlarm */
}

/* USER CODE BEGIN Header_StartTaskMPU6050 */
/**
* @brief Function implementing the myTaskMPU6050 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskMPU6050 */
void StartTaskMPU6050(void *argument)
{
  /* USER CODE BEGIN StartTaskMPU6050 */
  /* Infinite loop */
  for(;;)
  {
    if(gyro_detect()) flag_alarm = 0;
    osDelay(1);
  }
  /* USER CODE END StartTaskMPU6050 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */





void HAL_UARTEx_ReEventCallback(UART_HandleTypeDef *huart, uint16 Size)
{
	huart -> gState = HAL_UART_STATE_READY;
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	
	// 串口1接收数据处理
//	if (huart == &huart1) 
//	{ 
//	  HAL_UART_DMAStop(huart);  // 停止DMA请求
//		
//	  rx1_buf[Size] = '\0';      // 末尾加字符串结束符
//		
//	  osMessageQueuePut(QueueUart1Handle, rx1_buf, NULL, 0);  // 发送消息到队列1
//		
//	  // 重启串口1的DMA接收
//	  __HAL_UNLOCK(huart);
//		
//	  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx1_buf, sizeof(rx1_buf));
//	}
	
	// 串口6接收数据处理
//	if (huart == &huart6) 
//	{ 
//		HAL_UART_DMAStop(huart);   // 停止DMA请求
//		
//		rx6_buf[Size] = '\0';      // 末尾加字符串结束符
//		
//		osMessageQueuePut(QueueUart6Handle, rx6_buf, NULL, 0); // 发送消息到队列6
//		
//		// 重启串口6的DMA接收
//		__HAL_UNLOCK(huart);
//		
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart6, rx6_buf, sizeof(rx6_buf));
//	}
}






/* USER CODE END Application */


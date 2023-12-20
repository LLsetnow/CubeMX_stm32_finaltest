#include "GUI_func.h"
#include "stdio.h"
#include "GUI.h"
#include "rtc.h"
#include "key.h"
#include "cmsis_os.h"
#include "variables.h"
#include "beep.h"
#include "music.h"

RTC_DateTypeDef GetData;
RTC_TimeTypeDef GetTime;

uint16 Buff_Year;
uint8 Buff_Mon;
uint8 Buff_Dat;
uint8 Buff_Hour;
uint8 Buff_Min;
uint8 Buff_Sec;


//菜单参数初始化
void GUI_My_Init(void)
{
    //设置字体为24*24
	GUI_SetFont(&GUI_FontHZ_SimSun_24);
	//设置背景颜色
	GUI_SetBkColor(GUI_WHITE);
	//设置字体颜色
	GUI_SetColor(GUI_BLACK);
}



void GUI_DispIntAt(int value, int x, int y) 
{
    char str[12]; 

    // 将整型转换为字符串
    sprintf(str, "%d", value);

    // 使用GUI函数在指定位置显示字符串
    GUI_DispStringAt(str, x, y);
}

void GUI_DispFloatAt(float value, int b, int x, int y) 
{
    char str[20]; // 足够容纳浮点数转换成的字符串，包括结束符

    // 格式化浮点数为字符串
    // %*.*f 是一个格式化占位符，其中前一个 * 表示总字段宽度，后一个 * 表示小数点后的位数
    sprintf(str, "%.*f", b, value);

    // 使用GUI函数在指定位置显示字符串
    GUI_DispStringAt(str, x, y);
}


void show_string(const char * s, int x, int y)
{
    GUI_DispStringAt(s, x, y * 24); 
}

void show_int(int value, int x, int y) 
{
    GUI_DispIntAt(value, x, y * 24); 
}

// y行添加光标
void point_add(int y)
{
    show_string("->", 20, y);
}

// y行删去光标
void point_del(int y)
{
    show_string("  ", 20, y);
}

// 根据年月日 计算星期
uint8 calculateWeekday(int year, int month, int day) 
{
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int weekday = (day + 2*month + 3*(month+1)/5 + year + year/4 - year/100 + year/400 + 1) % 7;
    return weekday;
}


void show_time(void)
{
    char displayString[100]; 
    
    ReadRTCDateTime();
    
    uint8 week;
    
    week = calculateWeekday(RTC_Year, RTC_Mon, RTC_Dat);
    switch(week)
    {
        case 0: show_string("星期日", 320 - 24 * 3 - 1, 0); break;
        case 1: show_string("星期一", 320 - 24 * 3 - 1, 0); break;
        case 2: show_string("星期二", 320 - 24 * 3 - 1, 0); break;
        case 3: show_string("星期三", 320 - 24 * 3 - 1, 0); break;
        case 4: show_string("星期四", 320 - 24 * 3 - 1, 0); break;
        case 5: show_string("星期五", 320 - 24 * 3 - 1, 0); break;
        case 6: show_string("星期六", 320 - 24 * 3 - 1, 0); break;
    }
    
    sprintf(displayString, "%04d/%02d/%02d %02d:%02d:%02d", 
    RTC_Year, RTC_Mon, RTC_Dat, 
    RTC_Hour, RTC_Min, RTC_Sec);
      
    show_string(displayString, 10, 0); 
    
}

void warning(void)
{ 
    osDelay(200);
    GUI_DrawBitmap(&bmalarm, 219, 39);
    osDelay(200);
    GUI_ClearRect(219, 39, 319, 139);
}

void menu_init(void)
{
    GUI_Clear();
    menu(gui_menu);
    point_add(gui_point);
    
}

void menu0(void)
{
    show_time();
    
    show_string("时间设置", 50, 2);
    show_string("闹铃曲目", 50, 4);
    show_string("上网校准", 50, 6);
    show_string("其他", 50, 8);


}


void menu1(void)
{
    //show_string("时间设置:", 20, 0);
    Buff_Year = RTC_Year;
    Buff_Mon  = RTC_Mon;
    Buff_Dat  = RTC_Dat;
    
    Buff_Hour = RTC_Hour;
    Buff_Min  = RTC_Min;
    Buff_Sec  = RTC_Sec;
    
    
    show_string("年:", 50, 2);
    show_int(RTC_Year, 98, 2);
        
    show_string("月:", 50, 3);
    show_int(RTC_Mon,  98, 3);
    
    show_string("日:", 50, 4);
    show_int(RTC_Dat,  98, 4);
    
    show_string("时:", 50, 5);
    show_int(RTC_Hour, 98, 5);
    
    show_string("分:", 50, 6);
    show_int(RTC_Min,  98, 6);
    
    show_string("秒:", 50, 7);
    show_int(RTC_Sec,  98, 7);
    
    
    show_string("时间", 210, 8);
    show_string("设置", 210, 9);
    
    show_string("闹铃", 270, 8);
    show_string("设置", 270, 9);
}

void menu2(void)
{
    show_string("闹铃曲目:", 20, 0);
    
    show_string("1: BAD APPLE", 50, 2);
    show_string("2: LEMON TREE", 50, 4);
    show_string("3: ALIEZ", 50, 6);
    
    show_string("试听", 210, 9);
    show_string("设置", 270, 9);
    
}

//上网
void menu3(void)
{
    show_string("上网校准:", 20, 0);

    
}

void menu4(void)
{
    show_string("其他:", 20, 0);
    
}

void menu(int menu_num)
{
    switch(menu_num)
    {
        case 0: menu0(); break;
        case 1: menu1(); break;
        case 2: menu2(); break;
        case 3: menu3(); break;
    }
}



void switch_menu(void)
{
    //上
    if( (key_get_state(KEY_UP) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_UP) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_UP;
        key_beep(key_num);

        switch(gui_menu)
        {
            case 0:
            {
                point_del(gui_point);
                gui_point -= 2;
                if(gui_point == 0) gui_point = 8;
                point_add(gui_point);
            }break;
            case 1:
            {
                switch(gui_point)
                {
                    //年
                    case 2:
                    {
                        Buff_Year += 1;
                        show_string("    ", 98, 2);
                        show_int(Buff_Year, 98, 2);
                    }break;
                    //月
                    case 3:
                    {
                        Buff_Mon += 1;
                        if(Buff_Mon == 13) Buff_Mon = 1;
                        show_string("  ", 98, 3);
                        show_int(Buff_Mon, 98, 3);
                    }break;
                    //日
                    case 4:
                    {
                        Buff_Dat += 1;
                        if(Buff_Dat == 32) Buff_Dat = 1;
                        show_string("  ", 98, 4);
                        show_int(Buff_Dat, 98, 4);
                    }break;
                    //月
                    case 5:
                    {
                        Buff_Hour += 1;
                        if(Buff_Hour == 24) Buff_Hour = 0;
                        show_string("  ", 98, 5);
                        show_int(Buff_Hour, 98, 5);
                    }break;
                    //月
                    case 6:
                    {
                        Buff_Min += 1;
                        if(Buff_Min == 60) Buff_Min = 0;
                        show_string("  ", 98, 6);
                        show_int(Buff_Min, 98, 6);
                    }break;
                    //月
                    case 7:
                    {
                        Buff_Sec += 1;
                        if(Buff_Sec == 60) Buff_Sec = 0;
                        show_string("  ", 98, 7);
                        show_int(Buff_Sec, 98, 7);
                    }break;               
                }
            }break;
            case 2:
            {
                point_del(gui_point);
                gui_point -= 2;
                if(gui_point == 0) gui_point = 6;
                point_add(gui_point);
            }break;
            
        }

        
    }
    //下
    if( (key_get_state(KEY_DOWN) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_DOWN) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_DOWN;
        key_beep(key_num);
        
        switch(gui_menu)
        {
            case 0:
            {
                point_del(gui_point);
                gui_point += 2;
                if(gui_point == 10) gui_point = 2;
                point_add(gui_point);
            }break;
            case 1:
            {
                switch(gui_point)
                {
                    //年
                    case 2:
                    {
                        Buff_Year -= 1;
                        show_string("    ", 98, 2);
                        show_int(Buff_Year, 98, 2);
                    }break;
                    //月
                    case 3:
                    {
                        Buff_Mon -= 1;
                        if(Buff_Mon == 0) Buff_Mon = 12;
                        show_string("  ", 98, 3);
                        show_int(Buff_Mon, 98, 3);
                    }break;
                    //日
                    case 4:
                    {
                        Buff_Dat -= 1;
                        if(Buff_Dat == 0) Buff_Dat = 30;
                        show_string("  ", 98, 4);
                        show_int(Buff_Dat, 98, 4);
                    }break;
                    //月
                    case 5:
                    {
                        Buff_Hour -= 1;
                        if(Buff_Hour == 0) Buff_Hour = 59;
                        show_string("  ", 98, 5);
                        show_int(Buff_Hour, 98, 5);
                    }break;
                    //月
                    case 6:
                    {
                        Buff_Min -= 1;
                        if(Buff_Min == 0) Buff_Min = 59;
                        show_string("  ", 98, 6);
                        show_int(Buff_Min, 98, 6);
                    }break;
                    //月
                    case 7:
                    {
                        Buff_Sec -= 1;
                        if(Buff_Sec == 0) Buff_Sec = 59;
                        show_string("  ", 98, 7);
                        show_int(Buff_Sec, 98, 7);
                    }break;               
                }
            }break;
            case 2:
            {
                point_del(gui_point);
                gui_point += 2;
                if(gui_point == 8) gui_point = 2;
                point_add(gui_point);
            }break;
        }
        
    }
    //左 返回
    if( (key_get_state(KEY_LEFT) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_LEFT) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_LEFT;
        key_beep(key_num);
        
        if(gui_menu >= 1 && gui_menu <= 4)
        {
            gui_menu = 0;
            gui_point = 2;
            GUI_Clear();
            menu(gui_menu);
            point_add(gui_point);
        }

        
    }
    //右 确定
    if( (key_get_state(KEY_RIGHT) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_RIGHT) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_RIGHT;
        key_beep(key_num);
        
        switch(gui_menu)
        {
            case 0:
            {
                gui_menu = gui_point / 2;
                GUI_Clear();
                menu(gui_menu);
                gui_point = 2;
                point_add(gui_point);
            }break;
            case 1:
            {
                point_del(gui_point);
                gui_point += 1;
                if(gui_point == 8) gui_point = 2;
                point_add(gui_point);
            }break;
        }
    }
    
    //独立左按键
    if( (key_get_state(KEY_DL) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_DL) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_DL;
        key_beep(key_num);
        
        
        switch(gui_menu)
        {
            //时间更改
            case 1:
            {
                show_string("set", 220, 7);
                
                RTC_TimeTypeDef sTime = {0};
                RTC_DateTypeDef sDate = {0};
                
                sTime.Hours     =   Buff_Hour;
                sTime.Minutes   =   Buff_Min;
                sTime.Seconds   =   Buff_Sec;
                sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
                sTime.StoreOperation = RTC_STOREOPERATION_RESET;
                if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
                {
                    Error_Handler();
                }
                sDate.WeekDay = RTC_WEEKDAY_FRIDAY;
                sDate.Month = Buff_Mon;
                sDate.Date = Buff_Dat;
                sDate.Year = Buff_Year % 100;
                
                if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
                {
                    Error_Handler();
                }
                    
                SetRTCTime(sTime.Hours, sTime.Minutes, sTime.Seconds);
                SetRTCDate(sDate.Year, sDate.Month, sDate.Date);
                
  

                osDelay(300);
                show_string("   ", 220, 7);
            }break;
            
            //试听
            case 2:
            {
                 show_string("ing", 220, 8);
                 play_music_5(gui_point / 2 - 1);
                
                
                 show_string("   ", 220, 8);
            }break;
            
        }

    }
    
    //独立右按键
    if( (key_get_state(KEY_DR) == KEY_SHORT_PRESS && flag_key) || key_get_state(KEY_DR) == KEY_LONG_PRESS)
    {
        osDelay(50);
        flag_key = 0;
        key_num = KEY_DR;
        key_beep(key_num);
        
        
        switch(gui_menu)
        {
            //闹铃时间设置
            case 1:
            {
                show_string("set", 280, 7);
                
                Alarm_Hour = Buff_Hour;
                Alarm_Min  = Buff_Min;
                Alarm_Sec  = Buff_Sec;
                
                osDelay(300);
                show_string("   ", 280, 7);
            }break;
            
            //闹铃歌曲设置
            case 2:
            {
                 show_string("set", 280, 8);
                 music = gui_point / 2 - 1;
                 osDelay(300);
                 show_string("   ", 280, 8);
                
            }break;
            
        }
   
    }
    
    //清除短按标志位
    if(key_get_state(key_num) == KEY_RELEASE)
    {
        flag_key = 1;
    }
    
    
}
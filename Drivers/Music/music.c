#include "music.h"
#include "stdint.h"
#include "variables.h"
#include "Beep.h"
#include "cmsis_os.h"
#include "rtc.h"

#define		DO_L			261
#define		RE_L			293
#define		MI_L			329
#define		FA_L			349
#define		SO_L			392
#define		LA_L			440
#define		SI_L			493

#define     DO              523
#define		RE              578
#define		MI              659
#define		FA              698
#define		SO              784
#define		LA              880
#define		SI              988

#define		DO_H            1046
#define		RE_H            1175
#define		MI_H            1318
#define		FA_H            1397
#define		SO_H            1568
#define		LA_H            1760
#define		SI_H            1976

#define     PAUSE           0       // ”√”⁄±Ì æ‘›Õ£
#define     pai             62.5    // 1/16 ≈ƒ


const uint16 bad_apple_scale[] ={
    
    SO, LA, MI, RE, MI, RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, LA, SI,
    DO_H, SI, LA, SO, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, MI, SO,
    
    
    
    SO, LA, MI, RE, MI, RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, SO_L, LA_L,
    SI_L, DO, RE, MI, LA_L, MI, SO,
    
    SO, LA, MI, RE, MI ,RE, MI,
    SO, LA, MI, RE, MI, LA, SI,
    DO_H, SI, LA, SO, MI, RE, MI,
    RE, DO, SI_L, SO_L, LA_L, MI, SO,
    

};

const uint16 bad_apple_time[] ={
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 4, 2, 2,
};
    
const uint16 lemon_tree_scale[] ={

    MI, MI, LA, LA, LA,
    RE, RE, SO, SO,
    MI, MI, MI, MI, MI, RE, DO, DO,
    
    RE, RE, MI, MI,
    MI, MI, MI, LA, LA, LA,
    RE, RE, RE, MI, MI,
    
    RE, RE, DO, RE, RE, DO,
    RE, RE, RE, RE, MI,
    PAUSE, SO, RE, RE, RE, DO,
    
    RE, MI, PAUSE, RE, MI,
    RE, DO, LA_L,
    
    PAUSE, PAUSE, PAUSE, RE,
    MI, FA, SO, MI,
    SO, LA, RE, MI,
    
    DO, DO, DO, DO, DO, DO, DO, RE,
    MI, SO, RE, MI, MI,
    RE, DO, DO, DO,
    
    RE, MI, PAUSE, MI,
    RE, RE, RE, DO, MI, DO,
    LA_L, PAUSE, RE,
    
    MI, MI, FA, SO, MI,
    SO, LA, RE, MI, MI,
    DO, DO, DO, DO, DO, DO, DO, RE,

};

const uint16 lemon_tree_time[] ={

    2, 6, 4, 2, 2,
    4, 4, 6, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    
    4, 2, 8, 2,
    4, 2, 2, 4, 2, 2,
    4, 2, 2, 6, 2,
    
    4, 2, 2, 4, 2, 2,
    2, 2, 4, 2, 6,
    6, 2, 2, 2, 2, 2,
    
    2, 6, 4, 2, 2,
    2, 2, 12,
    
    4, 4, 6, 2,
    4, 2, 8, 2,
    4, 4, 2, 6,
    
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 6, 2, 4, 2,
    4, 4, 4, 4,
    
    2, 6, 6, 2,
    2, 2, 2, 2, 2, 6,
    8, 6, 2,
    
    2, 2, 2, 8, 2,
    2, 6, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 
};


const uint16 lemon_scale[] ={
    DO_H, RE_H, FA, PAUSE,
    FA, SO, LA, SO, FA,
    MI, SO, DO_H, DO_H,
    SI, SI, LA, SI,
    
    DO_H, RE_H, MI_H, RE_H, DO_H,
    LA, DO_H, PAUSE, MI_H, SO_H, PAUSE,
    RE_H, DO_H, PAUSE, RE_H, MI_H, RE_H, DO_H,
    LA, DO_H, PAUSE, MI_H, SO_H, PAUSE,
    
    RE_H, DO_H, PAUSE, RE_H, MI_H, RE_H, DO_H,
    LA, DO_H, PAUSE, MI_H, SO_H, PAUSE,
    LA_H, SO_H, PAUSE, SO_H, DO_H, PAUSE,
    SI_L, SO_H, PAUSE, MI_L, SO_H, PAUSE,

};

const uint16 lemon_time[] ={
    4, 4, 4, 4,
    6, 2, 4, 2, 2,
    4, 4, 4, 4,
    6, 2, 6, 2,
    
    8, 2, 2, 2, 2,
    2, 2, 4, 2, 2, 4,
    2, 2, 4, 2, 2, 2, 2,
    2, 2, 4, 2, 2, 4,
    
    2, 2, 4, 2, 2, 2, 2,
    2, 2, 4, 2, 2, 4,
    2, 2, 4, 2, 2, 4,
    2, 2, 4, 2, 2, 4,

};

const uint16 aLIEz_scale[] ={
    PAUSE, PAUSE, MI, MI, MI, MI, MI, SO, LA,
    PAUSE, PAUSE, MI, MI, MI, MI, MI, SO, LA,
    PAUSE, MI, MI, SO, LA, PAUSE, MI, MI, SO, LA,
    SI, DO_H, SI, DO_H, SI, SO, SO,
    
    PAUSE, PAUSE, MI, MI, MI, MI, MI, SO, LA,
    PAUSE, DO_H, SI, DO_H, LA,
    PAUSE, LA, SI, DO_L, LA, SI, DO_H,
    RE_H, DO_H, DO_H, SI, SI, MI,
    
    LA, SO, LA, DO_H, LA, SO, LA, DO_H, RE_H,
    DO_H, DO_H, LA, RE_H, LA,
    MI, DO_H, SI, SO, LA, DO_H, SI, LA,
    SI, MI_H, LA,
    
    MI_H, SO_H, MI_H, MI_H, MI_H, LA,
    MI_H, SO_H,MI_H, MI_H, MI_H, LA,
    MI_H, FA_H, MI_H, MI_H, MI_H, LA,
    RE_H, DO_H, RE_H, DO_H, MI_H, LA, LA, 
};

const uint16 aLIEz_time[] ={
    4, 2, 1, 1, 2, 1, 1, 2, 2,
    4, 2, 1, 1, 2, 1, 1, 2, 2,
    2, 1, 1, 2, 2, 2, 1, 1, 2, 2,
    2, 2, 2, 2, 2, 2, 4,
    
    4, 2, 1, 1, 2, 1, 1, 2, 2,
    4, 2, 4, 2, 4,
    4, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 5,
    
    2, 2, 2, 1, 3, 2, 2, 1, 3,
    2, 2, 2, 2, 5,
    2, 2, 2, 1, 3, 2, 2, 1, 3,
    2, 2, 2, 2, 5,
    
    2, 2, 2, 1, 3, 2, 2, 1, 3,
    2, 2, 2, 2, 5,
    2, 2, 2, 1, 3, 2, 2, 2,
    10, 3, 3, 


};



// ≤•∑≈5√Î“Ù¿÷
void play_music_5(uint8 music)
{
    uint16 i = 0;
    uint32 time_sum = 0;
    
    switch(music)
    {
		case 0:
		{
			for(i = 0; i < 100; i++)
			{
				Buzzer_Beep(bad_apple_scale[i], 1, bad_apple_time[i] * pai);
				osDelay(2 * pai);
                
                time_sum += bad_apple_time[i] * pai;
                if(time_sum >= 5000) break;
			}
		}break;
		case 1:
		{
			for(i = 0; i < 100; i++)
			{
                Buzzer_Beep(lemon_tree_scale[i], 1, lemon_tree_time[i] * pai);
				osDelay(2 * pai);
                
                time_sum += lemon_tree_time[i] * pai;
                if(time_sum >= 5000) break;
			}
		}break;
        case 2:
		{
			for(i = 0; i < 100; i++)
			{
                Buzzer_Beep(aLIEz_scale[i], 1, aLIEz_time[i] * pai);
				osDelay(2 * pai);
                
                time_sum += aLIEz_time[i] * pai;
                if(time_sum >= 5000) break;
			}
		}break;
    }
    
}


// ≤•∑≈30√Î“Ù¿÷
void play_music_30(uint8 music)
{
    uint16 i = 0;
    uint32 time_sum = 0;
    
    switch(music)
    {
		case 0:
		{
            while(1)
            {
                Buzzer_Beep(bad_apple_scale[i], 1, bad_apple_time[i] * pai);
                osDelay(2 * pai);
                time_sum += bad_apple_time[i] * pai;
                i++;
                if(i == sizeof(bad_apple_scale) ) i = 0;
                if(time_sum > 30000) break;
                if(flag_alarm == 0)  break;
            }
		}break;
		case 1:
		{
            while(1)
            {
                Buzzer_Beep(lemon_scale[i], 1, lemon_scale[i] * pai);
                osDelay(2 * pai);
                time_sum += lemon_time[i] * pai;
                i++;
                if(i == sizeof(lemon_scale) ) i = 0;
                if(time_sum > 30000) break;
                if(flag_alarm == 0)  break;
            }
		}break;
        case 2:
		{
            while(1)
            {
                Buzzer_Beep(aLIEz_scale[i], 1, aLIEz_scale[i] * pai);
                osDelay(2 * pai);
                time_sum += aLIEz_time[i] * pai;
                i++;
                if(i == sizeof(aLIEz_scale) ) i = 0;
                if(time_sum > 30000) break;
                if(flag_alarm == 0)  break;
            }
		}break;
    }
}


// ƒ÷¡ÂºÏ≤‚≤¢≤•∑≈“Ù¿÷
void alarm_detect(void)
{
    if( Alarm_Hour == RTC_Hour
        && Alarm_Min == RTC_Min
        && Alarm_Sec == RTC_Sec)
    {
        
        flag_alarm = 1;
        play_music_30(music);
        flag_alarm = 0;
        GUI_SetBkColor(GUI_WHITE);
        GUI_ClearRect(219, 39, 319, 139);
    }
        
}









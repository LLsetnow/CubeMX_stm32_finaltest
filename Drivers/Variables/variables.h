#ifndef __variables_H
#define __variables_H


#include "stdint.h"
#include "GUI.h"


extern const GUI_FONT GUI_FontHZ_SimSun_24;
extern GUI_CONST_STORAGE GUI_BITMAP bmHDU;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm;

extern uint8  flag_key;
extern int8   key_num;
extern uint8  gui_menu;
extern uint8  gui_point;
extern uint32 tim5_count;
extern uint8  music;

extern uint8  Alarm_Hour;
extern uint8  Alarm_Min ;
extern uint8  Alarm_Sec ;
extern uint8  flag_alarm;


#endif	
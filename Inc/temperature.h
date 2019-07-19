#ifndef _temperature_h
#define _temperature_h

#include "stm32f1xx_hal.h"

#define NTC_Res_Table_Size  (uint16_t)(301) //定义表长度 
#define Senor_Temp_Max_Value  (int16_t)(250)
#define Senor_Temp_Min_Value  (int16_t)(-50)

int16_t Get_Senor_Temperature(uint32_t res);


#endif

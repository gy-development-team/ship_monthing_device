#ifndef  _senor_h
#define  _senor_h
#include "stm32f1xx_hal.h"
#include "string.h"
#include "temperature.h"


// typedef struct  senor_def 
// {
//     uint16_t bat_adc;
//     uint16_t press_adc;
//     uint16_t oiltemp_adc;
//     uint16_t watertemp_adc;
// }senor_t;
enum
{
    Bat_Voltage=(uint8_t)0x00,
    Press_Value,
    Oiltemp_Value,
    Watertemp_Value
};
void senor_init(ADC_HandleTypeDef *p_adc_device);

uint16_t get_senor_adc(uint8_t index);
/*uint16_t get_senor_volrt(uint8_t index); */
uint16_t get_senor_batvoltage_rt_value(uint8_t index);
uint16_t get_senor_watertemp_rt_value(uint8_t index);
uint16_t get_senor_oiltemp_rt_value(uint8_t index);


#endif




/*
 * @Author: Liang Weiwei
 * @Date: 2019-07-17 10:19:34
 * @LastEditTime: 2019-07-17 14:23:46
 * @Description: Do not edit
 * @Company: Zhejiang Geyao Technology Co. LTD  Development Team
 */

#include "senor.h"
static uint16_t Senor_Adc[4];

static uint32_t ADC_Value[100];
static ADC_HandleTypeDef *adc_device;
void senor_init(ADC_HandleTypeDef *p_adc_device)
{
    memset((uint8_t *)&Senor_Adc[0], 0, sizeof(Senor_Adc));
    memset((uint8_t *)&ADC_Value[0], 0, sizeof(ADC_Value));

    adc_device = p_adc_device;
    HAL_ADC_Start_DMA(adc_device, (uint32_t *)&ADC_Value, 100);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    /*read DMA data*/
    uint16_t j;
    uint32_t sum[4] = {0};
    for (j = 0; j < 100;)
    {
        sum[0] += ADC_Value[j];
        j++;
        sum[1] += ADC_Value[j];
        j++;
        sum[2] += ADC_Value[j];
        j++;
        sum[3] += ADC_Value[j];
        j++;
    }
    Senor_Adc[Bat_Voltage] = (uint16_t)(sum[0] / 25);
    Senor_Adc[Press_Value] = (uint16_t)(sum[1] / 25);
    Senor_Adc[Oiltemp_Value] = (uint16_t)(sum[2] / 25);
    Senor_Adc[Watertemp_Value] = (uint16_t)(sum[3] / 25);
    /*get temp */
    HAL_ADC_Start_DMA(adc_device, (uint32_t *)&ADC_Value, 100);
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
uint16_t get_senor_adc(uint8_t index)
{
    return Senor_Adc[index];
}
/* 
uint16_t get_senor_volrt(uint8_t index)
{   
    uint16_t bat_voltage_rt_value = 0;
	float adc_float;
	adc_float=(float)get_senor_adc(index);
    bat_voltage_rt_value=(uint16_t)(adc_float*0.095479);
    return bat_voltage_rt_value;
}
*/
uint16_t get_senor_batvoltage_rt_value(uint8_t index)
{
    uint16_t bat_voltage_rt_value = 0;
    float bat_float;
    if (index == Bat_Voltage)
    {
        bat_float = (float)get_senor_adc(Bat_Voltage);
        bat_voltage_rt_value = (uint16_t)(bat_float * 0.013432 * 10 - 97.544);
        return bat_voltage_rt_value;
    }
    else
    {
        return 0;
    }
}
uint16_t get_senor_watertemp_rt_value(uint8_t index)
{
    uint32_t water_temp_res;
    float water_float;
    if (index == Watertemp_Value)
    {
        water_float = (float)get_senor_adc(Watertemp_Value);
        water_temp_res = (uint32_t)(water_float * 330000 / (13516.8 - water_float * 3.3));
        return Get_Senor_Temperature(water_temp_res);
    }
    else
    {
        return 0;
    }
}
uint16_t get_senor_oiltemp_rt_value(uint8_t index)
{
    uint32_t oil_temp_res;
    float oil_float;
    if (index == Oiltemp_Value)
    {
        oil_float = (float)get_senor_adc(Oiltemp_Value);
        oil_temp_res = (uint32_t)(oil_float * 330000 / (13516.8 - oil_float * 3.3));
        return Get_Senor_Temperature(oil_temp_res);
    }
    else
    {
        return 0;
    }
}

/* uint16_t get_senor_volrt(uint8_t index)
{  
    uint32_t water_temp_res;
    uint32_t oil_temp_res;
    uint16_t bat_voltage_rt_value = 0;
    float adc_float;
    switch (index)
    {
    case Bat_Voltage:
        adc_float=(float)get_senor_adc(Bat_Voltage);
        bat_voltage_rt_value=(uint16_t)(adc_float*0.013432*10-97.544);
        return bat_voltage_rt_value;
        break;
    case Press_Value:
        return 0;
        break;
    case Oiltemp_Value:
        adc_float=(float)get_senor_adc(Oiltemp_Value);
        oil_temp_res=(uint32_t)(adc_float*330000/(13516.8-adc_float*3.3));
        return Get_Senor_Temperature(oil_temp_res);
        break;
    case Watertemp_Value:
        adc_float=(float)get_senor_adc(Watertemp_Value);
        water_temp_res=(uint32_t)(adc_float*330000/(13516.8-adc_float*3.3));
        return Get_Senor_Temperature(water_temp_res);
        break;
    }
}
*/

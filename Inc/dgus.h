#ifndef  _dgus_h
#define  _dgus_h
#include "stm32f1xx_hal.h"
#include "USART.h"

#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_14
#define LED3_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_15
#define LED2_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOA
#define Relay1_Pin GPIO_PIN_3
#define Relay1_GPIO_Port GPIOB
#define Relay2_Pin GPIO_PIN_4
#define Relay2_GPIO_Port GPIOB
#define Relay3_Pin GPIO_PIN_5
#define Relay3_GPIO_Port GPIOB
#define Relay4_Pin GPIO_PIN_6
#define Relay4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define LED1_ON HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED1_OFF HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED2_ON HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#define LED2_OFF HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED3_ON HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET)
#define LED3_OFF HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET)
#define LED4_ON HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET)
#define LED4_OFF HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET)
#define LED5_ON HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET)
#define LED5_OFF HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET)
#define BEEP_ON HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define BEEP_OFF HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)
#define Relay1_ON HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_SET)
#define Relay1_OFF HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_RESET)
#define Relay2_ON HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_SET)
#define Relay2_OFF HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_RESET)
#define Relay3_ON HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_SET)
#define Relay3_OFF HAL_GPIO_WritePin(Relay3_GPIO_Port, Relay3_Pin, GPIO_PIN_RESET)
#define Relay4_ON HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_SET)
#define Relay4_OFF HAL_GPIO_WritePin(Relay4_GPIO_Port, Relay4_Pin, GPIO_PIN_RESET)

#define Water_Temp_RT_Value_DWaddress 0x0120
#define Oil_Temp_RT_Value_DWaddress 0x0140
#define Oil_Press_RT_Value_DWaddress 0x0160
#define Engine_Speed_RT_Value_DWaddress 0x0180
#define Battery_Voltage_RT_Value_DWaddress 0x0200
#define Water_Level_RT_Value_DWaddress 0x0220
#define Water_Level_RT_Button_DWaddress 0x0000
#define Water_Level_Warning_Value_DWaddress 0x0240
#define Water_Level_Draining_Value_DWaddress 0x0260
#define Engine_Speed_Warning_Value_DWaddress 0x0280
#define Engine_Speed_Stopping_Value_DWaddress 0x0300
#define Oil_Temp_Warning_Value_DWaddress 0x0320
#define Water_Temp_Warning_Value_DWaddress 0x0340
#define Oil_Press_Warning_Value_DWaddress 0x0360
#define Battery_Voltage_Charging_Value_DWaddress 0x0380
#define Water_Temp_ADC_Value_DWaddress 0x0C00
#define Water_Temp_RT_Value_DWaddress_1 0x0420
#define Oil_Temp_ADC_Value_DWaddress 0x0D00
#define Oil_Temp_RT_Value_DWaddress_1 0x0460
#define Oil_Press_ADC_Value_DWaddress 0x0E00
#define Oil_Press_RT_Value_DWaddress_1 0x0500
#define Engine_Speed_RT_Value_DWaddress_1 0x0520
#define Engine_Speed_Number_Value_DWaddress 0x0540
#define Battery_Voltage_ADC_Value_DWaddress 0x0F00
#define Battery_Voltage_RT_Value_DWaddress_1 0x0580
#define Water_Level_RT_Value_DWaddress_1 0x0600
#define Engine_Speed_Warning_Value_DWaddress_1 0x0620
#define Water_Temp_Warning_Value_DWaddress_1 0x0640
#define Oil_Temp_Warning_Value_DWaddress_1 0x0660
#define Oil_Press_Warning_Value_DWaddress_1 0x0680
#define Water_Level_Warning_Value_DWaddress_1 0x0700
#define Water_Level_Draining_Value_DWaddress_1 0x0720
#define Battery_Voltage_Charging_Value_DWaddress_1 0x0740

#define Test_page_Relay1_control 0x1120
#define Test_page_Relay2_control 0x1140
#define Test_page_Relay3_control 0x1160
#define Test_page_Relay4_control 0x1180
#define Test_page_BEEP_control 0x1200
#define Test_page_Relay1_ON 0x4170
#define Test_page_Relay2_ON 0x4180
#define Test_page_Relay3_ON 0x4190
#define Test_page_Relay4_ON 0x4200
#define Test_page_BEEP_ON 0x4210
#define Home_page_Reset_control 0x1040
#define Home_page_Quiet_control 0x1060
#define Home_page_Reset_ON 0x4010
#define Home_page_Quiet_ON 0x4020
#define Reset_page_Reset_control 0x1240
#define Reset_page_Reset_ON 0x4220
#define Home_page_turn_Test_page_control 0x1080
#define Home_page_turn_Test_page_ON 0x4030
#define Home_page_turn_Settings_page_control 0x1100
#define Home_page_turn_Settings_page_ON 0x4040
#define Settings_page_turn_Reset_page_control 0x1104
#define Settings_page_turn_Reset_page_ON 0x4050
#define Settings_page_turn_Home_page_control 0x1108
#define Settings_page_turn_Hme_page_ON 0x4060
#define Reset_page_turn_Settings_page_control 0x1260
#define Reset_page_turn_Settings_page_ON 0x4230
#define Test_page_turn_Home_page_control 0x1220
#define Test_page_turn_Home_page_ON 0x4220























void dgus_write_var(uint16_t addr, uint8_t *p_data, uint8_t len);

void dgus_init(UART_HandleTypeDef *handler);
void dgus_poll(void);

#endif

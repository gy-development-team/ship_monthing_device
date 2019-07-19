/*
 * @Author: Liang Weiwei
 * @Date: 2019-05-14 08:43:18
 * @LastEditTime: 2019-05-18 16:37:57
 * @Description: Do not edit
 * @Company: Zhejiang geyao technology co. LTD  Development Team
 */
#ifndef _USART_H
#define _USART_H
#include "stm32f1xx_hal.h"
#include "RingBuffer.h"

/*波特率定义*/
#define BAUDRATE 115200

/*发送缓冲区与接收缓冲区长度定义*/
#define USAR1_TX_RingBuff_Len 255
#define USAR1_RX_RingBuff_Len 50

void USART_Initialization(UART_HandleTypeDef *handler);
uint8_t Get_USART_RX_Buffer_Data_Num(void);
uint8_t Get_USART_RX_Buffer_Data(void);
void USART1_TX_Dat(uint8_t *p_data, uint8_t len);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handler);


#endif // !1

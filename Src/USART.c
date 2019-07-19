/*
 * @Author: Liang Weiwei
 * @Date: 2019-05-17 17:56:17
 * @LastEditTime: 2019-05-18 16:37:45
 * @Description: 串口控制，基于环形缓存区机制收发数据
 * @Company: Zhejiang geyao technology co. LTD  Development Team
 */

#include "USART.h"

/*定义控制块*/
static UART_HandleTypeDef *port;
static ringbuffer_t USAR1_TX_RingBuff_Ctrl;
static ringbuffer_t USAR1_RX_RingBuff_Ctrl;
/*定义缓存区数据保存数组*/
static uint8_t USAR1_TX_RingBuff[USAR1_TX_RingBuff_Len];
static uint8_t USAR1_RX_RingBuff[USAR1_RX_RingBuff_Len];
/*发送状态标志位*/
static uint8_t TX_Flag;
static uint8_t RX_Data;
/**
 * @description: 串口初始化
 * @param {type} 
 * @return: 
 */
void USART_Initialization(UART_HandleTypeDef *handler)
{
    /*建立串接发送与接收环形缓存区*/
    create_ringBuffer(&USAR1_TX_RingBuff_Ctrl, (uint8_t *)&USAR1_TX_RingBuff[0], sizeof(USAR1_TX_RingBuff));
    create_ringBuffer(&USAR1_RX_RingBuff_Ctrl, (uint8_t *)&USAR1_RX_RingBuff[0], sizeof(USAR1_RX_RingBuff));
    clear_ringBuffer(&USAR1_TX_RingBuff_Ctrl);
    clear_ringBuffer(&USAR1_RX_RingBuff_Ctrl);

    RX_Data = 0;
    port = handler;

    HAL_UART_Receive_IT(port, &RX_Data, 1);

    TX_Flag = 0;
}
/**
 * @description: 向串口发送数据
 * @param {type} p_data     目标数据地址
 * 				 len   		目标数据长度
 * @return: 
 */
void USART1_TX_Dat(uint8_t *p_data, uint8_t len)
{
    if (TX_Flag == 0)
    {
        TX_Flag = 1;
        HAL_UART_Transmit_IT(port, p_data, 1);
        /*继续写入剩余的数据*/
        len--;
        /*如果没有数据，就不继续写入*/
        if (len > 0)
        {
            p_data++;
            write_ringBuffer(p_data, len, &USAR1_TX_RingBuff_Ctrl);
        }
    }
    else
    {
        /*如果已经处于发送状态则把把要发送的数据直接写入环形缓存区*/
        write_ringBuffer(p_data, len, &USAR1_TX_RingBuff_Ctrl);
    }
}

/* 
 * @description: 串口接收中断服务子程序
 * @param {type} 
 * @return: 
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handler)
	{
    if (handler->Instance == port->Instance)
    {
        write_ringBuffer(&RX_Data, 1, &USAR1_RX_RingBuff_Ctrl); /*写入环形缓冲区*/
        HAL_UART_Receive_IT(port, &RX_Data, 1);
    }
}
/**
 * @description:  串口发送中断服务子程序
 * @param {type} 
 * @return: 
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *handler)
{
    uint8_t _txdat = 0;
    /*判断环形缓存区有效数据长度*/
    if (get_ringBuffer_btoRead(&USAR1_TX_RingBuff_Ctrl) == 0)
    {
        TX_Flag = 0;
    }
    else
    {
        /*继续从环形缓存区读出一个数据*/
        read_ringBuffer(&_txdat, 1, &USAR1_TX_RingBuff_Ctrl);
        /*写入串口*/
        HAL_UART_Transmit_IT(port, &_txdat, 1);
    }
}
/**
 * @description: 获取数据接收缓冲区有效数据长度
 * @param {type} 
 * @return: 
 */
uint8_t Get_USART_RX_Buffer_Data_Num(void)
{
    return get_ringBuffer_btoRead(&USAR1_RX_RingBuff_Ctrl);
}
/**
 * @description: 从数据接收缓冲区读出一个数据
 * @param {type} 
 * @return: 
 */
uint8_t Get_USART_RX_Buffer_Data(void)
{
    uint8_t _dat = 0;
    read_ringBuffer(&_dat, 1, &USAR1_RX_RingBuff_Ctrl);
    return _dat;
}

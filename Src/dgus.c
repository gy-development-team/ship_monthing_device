#include "dgus.h"
/* 调用头文件 */
#include "USART.h"
/* 声明huart1数据句柄*/

static uint8_t send_test[] = {0x5a, 0xa5, 0x05, 0x82, 0x00, 0x00};
static uint8_t _buf[8] = {0};
/**
 * @description: 数字大小端转换
 * @param {type} p_data     目标数据的地址
 *               len        目标数据长度
 * @return: 
 */
static void data_conver(uint8_t *p_data, uint8_t len)
{
  uint8_t *b_data;
  uint8_t n;
  b_data = p_data + len - 1;
  for (n = 0; n < len; n++)
  {
    _buf[n] = *(b_data);
    b_data--;
  }
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void dgus_write_var(uint16_t addr, uint8_t *p_data, uint8_t len)
{
  uint8_t data_len = 0;
  send_test[4] = (uint8_t)(addr >> 8);
  send_test[5] = (uint8_t)(addr);
  data_len = len + 3;
  send_test[2] = data_len;
  USART1_TX_Dat(&send_test[0], 6);
  data_conver(p_data, len);
  USART1_TX_Dat(&_buf[0], len);
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void dgus_init(UART_HandleTypeDef *handler)
{
  USART_Initialization(handler);
}
/**
 * @description: 数据帧帧头检查
 * @param {type} 
 * @return: 1      帧头正确
 *          0      帧头错误
 */
static uint8_t dgus_check_head(void)
{
  if (Get_USART_RX_Buffer_Data() == 0x5a)
  {
    if (Get_USART_RX_Buffer_Data() == 0xa5)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}
/**
 * @description: 根据传入的数据与命令地址进行相应的处理
 * @param {type} addr     变量地址
 *               data_buf 数据
 * @return: 
 */
static void dgus_cmmand_match(uint16_t addr, uint16_t data_buf)
{
  switch (addr)
  {
  case Test_page_Relay1_control:
    if (data_buf == Test_page_Relay1_ON)
    {
      Relay1_ON;
    }
    else
    {
      Relay1_OFF;
    }
    break;
  case Test_page_Relay2_control:
    if (data_buf == Test_page_Relay2_ON)
    {
      Relay2_ON;
    }
    else
    {
      Relay2_OFF;
    }
    break;
  case Test_page_Relay3_control:
    if (data_buf == Test_page_Relay3_ON)
    {
      Relay3_ON;
    }
    else
    {
      Relay3_OFF;
    }
    break;
  case Test_page_Relay4_control:
    if (data_buf == Test_page_Relay4_ON)
    {
      Relay4_ON;
    }
    else
    {
      Relay4_OFF;
    }
    break;
  case Test_page_BEEP_control:
    if (data_buf == Test_page_BEEP_ON)
    {
      BEEP_ON;
    }
    else
    {
      BEEP_OFF;
    }
    break;
  }
  /*后面再加 */
}
/**
 * @description: 轮询并解析从DGUS下发至环形缓存区的数据
 * @param {type} 
 * @return: 
 */
void dgus_poll(void)
{
  uint8_t arrays_len = 0; /* 数据长度*/
  uint8_t m = 0;
  uint8_t arrays[10];
  uint16_t addr;     /* 变量地址*/
  uint32_t data_buf; /* 变量值*/
  /*如果数据帧长度符合最小数据帧长度要求，帧头正确则开始解析*/
  if (Get_USART_RX_Buffer_Data_Num() >= 8 && dgus_check_head())
  {
    arrays_len = Get_USART_RX_Buffer_Data(); //获取数据长度
    for (m = 0; m < arrays_len; m++)         /*读取剩余的数据字节 */
    {
      arrays[m] = Get_USART_RX_Buffer_Data();
    }
    if (arrays[0] == 0x83 || arrays[0] == 0x82) /*判断命令字节 */
    {
      addr = (arrays[1] << 8 | arrays[2]);  /*获取变量地址 */
      if (addr <= 0x0390 && addr >= 0x0230) /*判断地址范围 */
      {
        data_buf = (arrays[3] << 8 | arrays[4]);
      }
      else
      {
        data_buf = (arrays[4] << 8 | arrays[5]);
      }
      dgus_cmmand_match(addr, data_buf); /*进行命令与数据解析 */
    }
  }
}

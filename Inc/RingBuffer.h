/*
 * @Author: Liang Weiwei
 * @Date: 2019-05-17 17:56:17
 * @LastEditTime: 2019-05-18 16:34:19
 * @Description: 环形缓存区控制头文件
 * @Company: Zhejiang geyao technology co. LTD  Development Team
 */

#ifndef   _RingBuffer_H
#define   _RingBuffer_H
#include "stm32f1xx_hal.h"
#include "string.h"
/*环形缓存区控制块结构体定义*/
typedef struct {
    uint8_t *source;
    uint8_t br;
    uint8_t bw;
    uint8_t btoRead;
    uint8_t length;
}ringbuffer_t;
void create_ringBuffer(ringbuffer_t *ringBuf, uint8_t *buf, uint8_t buf_len);
void clear_ringBuffer(ringbuffer_t *ringBuf);
uint8_t read_ringBuffer(uint8_t *buffer, uint8_t size, ringbuffer_t *ringBuf);
uint8_t write_ringBuffer(uint8_t *buffer, uint8_t size, ringbuffer_t *ringBuf);
uint8_t get_ringBuffer_btoRead(ringbuffer_t *ringBuf);

#endif // !RingBuffer_


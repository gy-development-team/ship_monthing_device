/*
 * @Author: Liang Weiwei
 * @Date: 2019-05-17 17:56:17
 * @LastEditTime: 2019-05-18 16:33:35
 * @Description: 环形缓存区控制接口
 * @Company: Zhejiang geyao technology co. LTD  Development Team
 */

#include "RingBuffer.h"


/**
 * @description: 创建一个环形缓存区
 * @param {type} ringBuf    环形缓存区控制结构体
 *               buf        环形缓存区数据存放地址
 *               buf_len    环形缓存区的大小   
 * @return: 
 */

void create_ringBuffer(ringbuffer_t *ringBuf, uint8_t *buf, uint8_t buf_len)
{
	ringBuf->br = 0;
	ringBuf->bw = 0;
	ringBuf->btoRead = 0;
	ringBuf->source = buf;
	ringBuf->length = buf_len;
}
/**
 * @description: 清除环形缓存区数据
 * @param {type} ringBuf    环形缓存区控制结构体
 * @return: 
 */
void clear_ringBuffer(ringbuffer_t *ringBuf)
{
	ringBuf->br = 0;
	ringBuf->bw = 0;
	ringBuf->btoRead = 0;
	memset((uint8_t *)ringBuf->source, 0, ringBuf->length);
}
/**
 * @description: 从环形缓存区读入指定长度的数据
 * @param {type} buffer     读出数据存放地址
 *               size       要读出的数据长度
 *               ringBuf    环形缓存区控制结构体
 * @return: 
 */
uint8_t read_ringBuffer(uint8_t *buffer, uint8_t size, ringbuffer_t *ringBuf)  
{
	uint8_t len = 0;
	uint8_t ringBuf_br = ringBuf->br;
	uint8_t ringBuf_len = ringBuf->length;
	uint8_t *ringBuf_source = ringBuf->source;

	if ((ringBuf_br + size) <= ringBuf_len)
	{
		memcpy(buffer, ringBuf_source + ringBuf_br, size);
	}
	else
	{
		len = ringBuf_len - ringBuf_br;
		memcpy(buffer, ringBuf_source + ringBuf_br, len);
		memcpy(buffer + len, ringBuf_source, size - len);
	}

	ringBuf->br = (ringBuf->br + size) % ringBuf_len;
	ringBuf->btoRead -= size;

	return size;
}
/**
 * @description: 向环形缓存区写入数据
 * @param {type} buffer             要写入的目标数据地址
 *               size               要写入的数据长度
 *               ringBuf            环形缓存区控制结构体 
 * @return: 
 */
uint8_t write_ringBuffer(uint8_t *buffer, uint8_t size, ringbuffer_t *ringBuf)
{
	uint8_t len = 0;
	uint8_t ringBuf_bw = ringBuf->bw;
	uint8_t ringBuf_len = ringBuf->length;
	uint8_t *ringBuf_source = ringBuf->source;

	if ((ringBuf_bw + size) <= ringBuf_len)
	{
		memcpy(ringBuf_source + ringBuf_bw, buffer, size);
	}
	else
	{
		len = ringBuf_len - ringBuf_bw;
		memcpy(ringBuf_source + ringBuf_bw, buffer, len);
		memcpy(ringBuf_source, buffer + len, size - len);
	}

	ringBuf->bw = (ringBuf->bw + size) % ringBuf_len;
	ringBuf->btoRead += size;

	return size;
}
/**
 * @description: 获取环形缓存区有效数据的长度
 * @param {type} ringBuf            环形缓存区控制结构体
 * @return:      环形缓存区有限数据的长度
 */
uint8_t get_ringBuffer_btoRead(ringbuffer_t *ringBuf)
{
	return ringBuf->btoRead;
}

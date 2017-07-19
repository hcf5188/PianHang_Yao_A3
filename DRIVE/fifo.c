/*********************************************************
*文    件：               fifo.c
*功能描述：循环队列，用于存储接收自CAN的数据包
*作    者：洪春峰
*时    间：2017.7.17
***********************************************************/

#include "fifo.h"

bool CanFifo_Init(pCanFifo  ptr,void **start,uint8_t size,uint8_t fifo[][8])
{
	uint8_t i;
	if(ptr == (pCanFifo) 0)
		return false;
	if(start ==  0)
		return false;
	if(size <= 1)
		return false;
	if(fifo[0] == (uint8_t *)0)
		return false;
	ptr->ptrStart = start;
	ptr->ptrEnd   = &start[size];
	ptr->ptrIn    = start;
	ptr->ptrOut   = start;
	ptr->length   = size;
	ptr->count    = 0u;
	for(i = 0;i < size;i++)
		start[i] = fifo[i];
	return true;
}
bool CanFifo_Request(pCanFifo  ptr,uint8_t a[8])
{
	uint8_t *pmsg;
	uint8_t i=0;
	if(ptr == (pCanFifo) 0)
		return false;
	if(ptr->count <= 0)
		return false;
	if(a == (uint8_t *)0)
		return false;
	
	pmsg = *ptr->ptrOut++;
	ptr->count --;
	if(ptr->ptrOut == ptr->ptrEnd)
		ptr->ptrOut = ptr->ptrStart;
	for(i=0;i<8;i++)
		a[i] = *(pmsg + i);
	for(i=0;i<8;i++)
		*(pmsg + i) = 0;
	return true;
}
bool CanFifo_Post(pCanFifo  ptr,uint8_t a[8])
{
	uint8_t *pmsg;
	uint8_t i=0;
	if(ptr == (pCanFifo) 0)
		return false;
	if(ptr->count > ptr->length)
		return false;
	if(a == (uint8_t *)0)
		return false;
	
	pmsg = *ptr->ptrIn++;
	ptr->count ++;
	if(ptr->ptrIn == ptr->ptrEnd)
		ptr->ptrIn = ptr->ptrStart;
	for(i=0;i<8;i++)
		*(pmsg + i) = a[i];
	
	return true;
}

uint8_t CaFifo_GetCount(pCanFifo  ptr)
{
	if(ptr == (pCanFifo) 0)
		return 0;
	return ptr->count;
}







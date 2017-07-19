
#ifndef __FIFO_H
#define __FIFO_H


#include "system.h"


//循环队列结构体
typedef struct 
{
	void **ptrStart; //指向指针数组起始地址
	void **ptrEnd;   //指向指针数组结束地址
	void **ptrOut;   //指向被取出数据包的位置
	void **ptrIn;    //指向插入一条数据包的位置
	
	uint8_t length;  //循环队列总长度
	uint8_t count;   //当前未处理的数据包数量
}CanFifo,*pCanFifo;



bool CanFifo_Init(pCanFifo  ptr,void **start,uint8_t size,uint8_t fifo[][8]);
bool CanFifo_Request(pCanFifo  ptr,uint8_t a[8]);
bool CanFifo_Post(pCanFifo  ptr,uint8_t a[8]);

#endif

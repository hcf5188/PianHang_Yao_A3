
#ifndef __FIFO_H
#define __FIFO_H


#include "system.h"


//ѭ�����нṹ��
typedef struct 
{
	void **ptrStart; //ָ��ָ��������ʼ��ַ
	void **ptrEnd;   //ָ��ָ�����������ַ
	void **ptrOut;   //ָ��ȡ�����ݰ���λ��
	void **ptrIn;    //ָ�����һ�����ݰ���λ��
	
	uint8_t length;  //ѭ�������ܳ���
	uint8_t count;   //��ǰδ��������ݰ�����
}CanFifo,*pCanFifo;



bool CanFifo_Init(pCanFifo  ptr,void **start,uint8_t size,uint8_t fifo[][8]);
bool CanFifo_Request(pCanFifo  ptr,uint8_t a[8]);
bool CanFifo_Post(pCanFifo  ptr,uint8_t a[8]);

#endif

#ifndef __ALLDEAL_H__
#define __ALLDEAL_H__
#include "system.h"
#include "System_Init.h"
/******************      Ƶ�ʱ仯��ֵ         ******************/

#define   MOTOR_ONE_LIMIT11    100  //������� 1  ����Ƶ�ʱ仯��ֵ
#define   MOTOR_ONE_LIMIT12    300   //������� 1  ��ֹͣƵ�ʱ仯��ֵ

#define   MOTOR_ONE_LIMIT21    40  //ƫ�����   ����Ƶ�ʱ仯��ֵ
#define   MOTOR_ONE_LIMIT22    30   //ƫ�����   ��ֹͣƵ�ʱ仯��ֵ

/******************     ����ͣ��غ�    ************************/

#define FRE_MIN_LIMIT1   5000
#define FRE_MAX_LIMIT1   30000

#define FRE_MIN_LIMIT2   1250
#define FRE_MAX_LIMIT2   7500

#define temp_stop1   45    //��ֹͣ�������ϵ��
#define temp_stop2   110    //��ֹͣ�������ϵ��

#define   SOFT_FRE_START_MIN1    2000   //���1����������ʼƵ��
#define   SOFT_FRE_START_NUM1    300   //������Ƶ�ʱ仯�Ĵ���
#define   SOFT_FRE_START_TIME1   1     //������Ƶ�ʸ���ʱ��(ms)
#define   SOFT_FRE_STOP_MIN1     1000    //���1��ֹͣ�����Ƶ��
#define   SOFT_FRE_STOP_NUM1     300   //��ֹͣƵ�ʱ仯�Ĵ���
#define   SOFT_FRE_STOP_TIME1    1     //��ֹͣƵ�ʸ���ʱ��(ms)

#define   SOFT_FRE_START_MIN2    1000   //���2����������ʼƵ��
#define   SOFT_FRE_START_NUM2    300   //������Ƶ�ʱ仯�Ĵ���
#define   SOFT_FRE_START_TIME2   1     //������Ƶ�ʸ���ʱ��(ms)
#define   SOFT_FRE_STOP_MIN2     1000   //���2��ֹͣ�����Ƶ��
#define   SOFT_FRE_STOP_NUM2     300   //��ֹͣƵ�ʱ仯�Ĵ���
#define   SOFT_FRE_STOP_TIME2    1     //��ֹͣƵ�ʸ���ʱ��(ms)

#define  STEP_INDEX_NUM1  1000
#define  STEP_INDEX_NUM2  1000

/********************    ��ģ�鴦����     *************************/

bool Can1_DataDeal(void);        //CAN1���ݴ���

void STEP_Start1(void);
void STEP_Start2(void);
void SOFT_Start_M1(void);
void SOFT_Start_M2(void);



#endif



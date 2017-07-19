#ifndef __ALLDEAL_H__
#define __ALLDEAL_H__
#include "system.h"
#include "System_Init.h"
/******************      频率变化幅值         ******************/

#define   MOTOR_ONE_LIMIT11    100  //腰部电机 1  软起动频率变化幅值
#define   MOTOR_ONE_LIMIT12    300   //腰部电机 1  软停止频率变化幅值

#define   MOTOR_ONE_LIMIT21    40  //偏航电机   软起动频率变化幅值
#define   MOTOR_ONE_LIMIT22    30   //偏航电机   软停止频率变化幅值

/******************     软启停相关宏    ************************/

#define FRE_MIN_LIMIT1   5000
#define FRE_MAX_LIMIT1   30000

#define FRE_MIN_LIMIT2   1250
#define FRE_MAX_LIMIT2   7500

#define temp_stop1   45    //软停止最后步数的系数
#define temp_stop2   110    //软停止最后步数的系数

#define   SOFT_FRE_START_MIN1    2000   //电机1软启动的起始频率
#define   SOFT_FRE_START_NUM1    300   //软启动频率变化的次数
#define   SOFT_FRE_START_TIME1   1     //软启动频率更替时间(ms)
#define   SOFT_FRE_STOP_MIN1     1000    //电机1软停止的最后频率
#define   SOFT_FRE_STOP_NUM1     300   //软停止频率变化的次数
#define   SOFT_FRE_STOP_TIME1    1     //软停止频率更替时间(ms)

#define   SOFT_FRE_START_MIN2    1000   //电机2软启动的起始频率
#define   SOFT_FRE_START_NUM2    300   //软启动频率变化的次数
#define   SOFT_FRE_START_TIME2   1     //软启动频率更替时间(ms)
#define   SOFT_FRE_STOP_MIN2     1000   //电机2软停止的最后频率
#define   SOFT_FRE_STOP_NUM2     300   //软停止频率变化的次数
#define   SOFT_FRE_STOP_TIME2    1     //软停止频率更替时间(ms)

#define  STEP_INDEX_NUM1  1000
#define  STEP_INDEX_NUM2  1000

/********************    各模块处理函数     *************************/

bool Can1_DataDeal(void);        //CAN1数据处理

void STEP_Start1(void);
void STEP_Start2(void);
void SOFT_Start_M1(void);
void SOFT_Start_M2(void);



#endif



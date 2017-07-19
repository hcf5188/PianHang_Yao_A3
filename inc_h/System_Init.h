#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__

#include "system.h"
#include "fifo.h"
//级联限位
#define M1_Read_S1    (ROM_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) & GPIO_PIN_7)
#define M1_Read_S2    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_3) & GPIO_PIN_3)
#define M2_Read_S1    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_2) & GPIO_PIN_2)
#define M2_Read_S2    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1) & GPIO_PIN_1)

//板载限位
//#define M1_Read_S1    (ROM_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_3) & GPIO_PIN_3)
//#define M1_Read_S2    (ROM_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_4) & GPIO_PIN_4)
//#define M2_Read_S1    (ROM_GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6) & GPIO_PIN_6)
//#define M2_Read_S2    (ROM_GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_7) & GPIO_PIN_7)

#define M1_Dir_Forward ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define M1_Dir_Reverse ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0)
#define M1_Disable     ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_PIN_5)
#define M1_Enable      ROM_GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0)
#define M1_Pulse_High  ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define M1_Pulse_Low   ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0)

#define M2_Dir_Reverse ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define M2_Dir_Forward ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0)
#define M2_Disable     ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0,GPIO_PIN_0)
#define M2_Enable      ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0)
#define M2_Pulse_High  ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define M2_Pulse_Low   ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0)

#define LED_OFF  ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define LED_ON   ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0)


#define CLEAE_CAN( A )   (*((volatile unsigned long  *)( (A) + 0x0008)) ) = 0
#define GET_CANERR( A )  (*((volatile unsigned long  *)( (A) + 0x0008)) )

void GPIO_Init(void);            //GPIO初始化

void CAN1_Init(void);
int Can1DatasSend( unsigned char *pSend1Buffer,
				   unsigned char send1Len ,
			       unsigned long msgID1);
void Can1_Read(void);

void Timer_Init(void);           //定时器初始化
void Timer0AStart(uint16_t tim); //启动定时器
void Timer1AStart(uint16_t tim);

void SystemInit(void);

/************     系统全局变量      **********************/
extern FLAGBITS Flagbits; 

extern  UintToUchar Given_Fre1 ;  //电机 1 给定频率
extern  UintToUchar Given_Fre2 ;  //电机 2 给定频率
extern  UintToUchar Given_Step1 ; //电机 1 给定步数
extern  UintToUchar Given_Step2;  //电机 2 给定步数

extern  UintToUchar Step_Num_Cur1;//电机 1 当前已走步数
extern  UintToUchar Step_Num_Cur2;//电机 2 当前已走步数

extern  uint8_t Cmd_IsNew1;       //电机 1 新指令是否最新
extern  uint8_t Cmd_IsNew2;       //电机 2 新指令是否最新

extern  MOTOR_LOCATION M1_state;     //电机 1 运行标志字节
extern  MOTOR_LOCATION M2_state;     //电机 1 运行标志字节


extern  uint16_t  M_ss_cnt1;   //电机 1 软启停频率更改次数
extern  uint16_t  M_ss_cnt2;   //电机 2 软启停频率更改次数

extern  uint16_t Fre_Fuzhi11; //电机 1 软启动幅值
extern  uint16_t Fre_Fuzhi21; //电机 2 软启动幅值

extern  uint16_t Fre_Fuzhi12; //电机 1 软停止幅值
extern  uint16_t Fre_Fuzhi22; //电机 2 软停止幅值

#endif



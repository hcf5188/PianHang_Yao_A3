#include "System_Init.h"

/************************************************
* �� �� �� : void Timer_Init();
* Ӳ����� : DengJh       ������ : HongCf
* ��    ע : ��ʱ��2A��ʼ���Լ����ж�ʱ��ʱ��ʹ��
* �޸�ʱ�� : 2017.07.18
************************************************/
void Timer_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   //Timer0A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   //Timer1A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);   //Timer2A
	
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);//����TIMER2��ʱ��
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//���ö�ʱ��װ��ֵ
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//����Timer2A�ж��¼�Ϊ��ʱ����ʱ
	IntEnable(INT_TIMER0A);                         //ʹ�� NVIC �е� TIMER2A
	IntPrioritySet(INT_TIMER0A,0xe0);
	
	
	TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);//����TIMER2��ʱ��
	TimerLoadSet(TIMER1_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//���ö�ʱ��װ��ֵ
	TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);//����Timer2A�ж��¼�Ϊ��ʱ����ʱ
	IntEnable(INT_TIMER1A);                         //ʹ�� NVIC �е� TIMER2A
	IntPrioritySet(INT_TIMER1A,0xe0);
	
	
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);//����TIMER2��ʱ��
	TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//���ö�ʱ��װ��ֵ
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);//����Timer2A�ж��¼�Ϊ��ʱ����ʱ
	IntEnable(INT_TIMER2A);                         //ʹ�� NVIC �е� TIMER2A
	IntPrioritySet(INT_TIMER2A,0xe0);
	
	TimerDisable(TIMER0_BASE, TIMER_A); 
	TimerDisable(TIMER1_BASE, TIMER_A); 
	
	TimerEnable(TIMER2_BASE, TIMER_A);               //��ʱ��TIMER2Aʹ��
}
/************************************************
* �� �� �� : void TimerXAStart(uint16_t tim)
* Ӳ����� : DengJh       ������ : HongCf
* ��    ע : ������ʱ��
* �޸�ʱ�� : 2017.07.18
************************************************/
void Timer0AStart(uint16_t tim)
{
	TimerDisable(TIMER0_BASE, TIMER_A); 
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);//���ö�ʱ��װ��ֵ
	TimerEnable(TIMER0_BASE, TIMER_A); 
}
void Timer1AStart(uint16_t tim)
{
	TimerDisable(TIMER1_BASE, TIMER_A); 
	TimerLoadSet(TIMER1_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);//���ö�ʱ��װ��ֵ
	TimerEnable(TIMER1_BASE, TIMER_A); 
}




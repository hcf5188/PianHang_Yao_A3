#include "System_Init.h"

/************************************************
* 函 数 名 : void Timer_Init();
* 硬件设计 : DengJh       软件设计 : HongCf
* 备    注 : 定时器2A初始化以及所有定时器时钟使能
* 修改时间 : 2017.07.18
************************************************/
void Timer_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   //Timer0A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);   //Timer1A
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);   //Timer2A
	
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);//配置TIMER2定时器
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//配置定时器装载值
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//配置Timer2A中断事件为定时器超时
	IntEnable(INT_TIMER0A);                         //使能 NVIC 中的 TIMER2A
	IntPrioritySet(INT_TIMER0A,0xe0);
	
	
	TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);//配置TIMER2定时器
	TimerLoadSet(TIMER1_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//配置定时器装载值
	TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);//配置Timer2A中断事件为定时器超时
	IntEnable(INT_TIMER1A);                         //使能 NVIC 中的 TIMER2A
	IntPrioritySet(INT_TIMER1A,0xe0);
	
	
	TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);//配置TIMER2定时器
	TimerLoadSet(TIMER2_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);//配置定时器装载值
	TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);//配置Timer2A中断事件为定时器超时
	IntEnable(INT_TIMER2A);                         //使能 NVIC 中的 TIMER2A
	IntPrioritySet(INT_TIMER2A,0xe0);
	
	TimerDisable(TIMER0_BASE, TIMER_A); 
	TimerDisable(TIMER1_BASE, TIMER_A); 
	
	TimerEnable(TIMER2_BASE, TIMER_A);               //定时器TIMER2A使能
}
/************************************************
* 函 数 名 : void TimerXAStart(uint16_t tim)
* 硬件设计 : DengJh       软件设计 : HongCf
* 备    注 : 启动定时器
* 修改时间 : 2017.07.18
************************************************/
void Timer0AStart(uint16_t tim)
{
	TimerDisable(TIMER0_BASE, TIMER_A); 
	TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);//配置定时器装载值
	TimerEnable(TIMER0_BASE, TIMER_A); 
}
void Timer1AStart(uint16_t tim)
{
	TimerDisable(TIMER1_BASE, TIMER_A); 
	TimerLoadSet(TIMER1_BASE, TIMER_A,ROM_SysCtlClockGet()/tim);//配置定时器装载值
	TimerEnable(TIMER1_BASE, TIMER_A); 
}




#include "System_Init.h"

FLAGBITS Flagbits;
UintToUchar Given_Fre1 ;  //电机 1 给定频率
UintToUchar Given_Fre2 ;  //电机 2 给定频率
UintToUchar Given_Step1 ; //电机 1 给定步数
UintToUchar Given_Step2;  //电机 2 给定步数

UintToUchar Step_Num_Cur1;//电机 1 当前已走步数
UintToUchar Step_Num_Cur2;//电机 2 当前已走步数

uint8_t Cmd_IsNew1;       //电机 1 新指令是否最新
uint8_t Cmd_IsNew2;       //电机 2 新指令是否最新

MOTOR_LOCATION M1_state;     //电机 1 运行标志字节
MOTOR_LOCATION M2_state;     //电机 1 运行标志字节


uint16_t  M_ss_cnt1;   //电机 1 软启停频率更改次数
uint16_t  M_ss_cnt2;   //电机 2 软启停频率更改次数

uint16_t Fre_Fuzhi11; //电机 1 软启动幅值
uint16_t Fre_Fuzhi21; //电机 2 软启动幅值

uint16_t Fre_Fuzhi12; //电机 1 软停止幅值
uint16_t Fre_Fuzhi22; //电机 2 软停止幅值



static void GlobalVar_Init(void );
void SystemInit(void)
{
	IntMasterDisable();
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
			SYSCTL_XTAL_16MHZ);
	
	GlobalVar_Init();
	GPIO_Init();
	Timer_Init();
	CAN1_Init();



	IntMasterEnable();
}
//全局变量初始化
static void GlobalVar_Init(void )
{
	MotorTime_Pulse1    =0; //Timer0A 定时时间到
	MotorTime_Pulse2    =0; //Timer1A 定时时间到
	Motor_reversal1     =0; //控制电机 1 高低电平反转
	Motor_reversal2     =0; //控制电机 2 高低电平反转
	Motor_Hold1         =1; //电机 1 静态保持  上电保持
	Motor_Hold2         =1; //电机 2 静态保持  上电保持
	Motor_Direction1    =0; //电机 1 转向
	Motor_Direction2    =0; //电机 2 转向
	Motor_New_Cmd1      =0; //电机 1 新指令到达
	Motor_New_Cmd2      =0; //电机 2 新指令到达
	LED_CONTROL         =0; //LED反向标志
	
	MOTOR_ISENABLE      =1; //电机驱动使能
	
	Motor_Holdreversal  =0; //电机 12 静态使能反转
	Cmd_55_Flag         =0; //开机 0x55 指令标志
	Drive_Limit_Time    =0; //驱动时间限制标志(40ms后使能)	
	
	Timer_Send_Fre1     =0; //电机 1 软启动频率更改标志
	M_SS_Fre_start1     =0; //电机 1 软启动标志
	M_SS_Fre_stop1      =0; //电机 1 软停止标志
	Timer_Send_Fre2     =0; //电机 2 软启动频率更改标志
	M_SS_Fre_start2     =0; //电机 2 软启动标志
	M_SS_Fre_stop2      =0; //电机 2 软停止标志

	Given_Fre1.word  = 0; //电机 1 给定频率
	Given_Fre2.word  = 0; //电机 2 给定频率
	Given_Step1.word = 0; //电机 1 给定步数
	Given_Step2.word = 0; //电机 2 给定步数

	Step_Num_Cur1.word = 0x0000;//电机 1 当前已走步数
	Step_Num_Cur2.word = 0x0000;//电机 2 当前已走步数

	Cmd_IsNew1 = 0x64;   //电机 1 新指令是否最新
	Cmd_IsNew2 = 0x64;   //电机 2 新指令是否最新
	M1_state.byte = 0x00;   //初始没有认为没有压在限位开关上
	M2_state.byte = 0x00;   //初始没有认为没有压在限位开关上    
	
	M_ss_cnt2   = 0; //软启动初始计数
	Fre_Fuzhi21 = 0; //软启动频率升幅值
	Fre_Fuzhi22 = 0; //软停止频率降幅值
	M_ss_cnt1   = 0;
	Fre_Fuzhi11 = 0;
	Fre_Fuzhi12 = 0;
}


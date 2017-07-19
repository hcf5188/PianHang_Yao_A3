#include "AllDeal.h"

uint16_t  motor_ss1 = 0;   //控制电机 1 软启动频率
uint16_t  motor_ss2 = 0;   //控制电机 2 软启动频率
uint16_t  Stop_index1 = 0;
uint16_t  Stop_index2 = 0;    

static void Motor1_Stop(void );
static void Motor2_Stop(void );

/************************************************
* 函 数 名 : void STEP_StartX(void)
* 硬件设计 : DengJh       软件设计 : HongCf
* 备    注 : 新控制指令到达，初始化配置，启动
* 修改时间 : 2016.11.08
************************************************/
void STEP_Start1(void)
{
	Motor_New_Cmd1   = 0;
	
	MotorTime_Pulse1 = 1;    //脉冲启动
	Motor_Hold1      = 0;    //取消保持，一直使能驱动
	Timer_Send_Fre1  = 1;    //发送频率有效
	M_SS_Fre_start1  = 1;    //软启动有效
	M_SS_Fre_stop1   = 0;    //软停止无效
	Motor_reversal1  = 0;    //初始高脉冲
	M1_state.byte   &= 0x03; //初始清空其他状态
	
	
	M_ss_cnt1          = 0; //Timer2频率反转计数初始化
	Step_Num_Cur1.word = 0; //当前已走步数
	motor_ss1          = SOFT_FRE_START_MIN1; //软启动 初始频率赋值
	//软启动频率变化幅值
	Fre_Fuzhi11 = MOTOR_ONE_LIMIT11;//(Given_Fre1.word - SOFT_FRE_START_MIN1)/SOFT_FRE_START_NUM1; //都设置为固定值试试，效果应该非常好
	//软停止频率变化幅值
	Fre_Fuzhi12 = MOTOR_ONE_LIMIT12;//(Given_Fre1.word - SOFT_FRE_STOP_MIN1)/SOFT_FRE_STOP_NUM1;//设置为固定值试一下
	//软停止步数索引
	Stop_index1 =3; //(Given_Fre1.word - FRE_MIN_LIMIT1)/STEP_INDEX_NUM1;
	
	if(Motor_Direction1 == 1)//方向
		M1_Dir_Forward;				 
	else if(Motor_Direction1 == 0)//方向控制
		M1_Dir_Reverse;			
}
void STEP_Start2(void)
{
	Motor_New_Cmd2   = 0;
	
	MotorTime_Pulse2 = 1;   //脉冲启动
	Motor_Hold2      = 0;   //取消保持，一直使能驱动
	Timer_Send_Fre2  = 1;   //发送频率有效
	M_SS_Fre_start2  = 1;   //软启动有效
	M_SS_Fre_stop2   = 0;   //软停止无效
	Motor_reversal2  = 0;   //初始高脉冲
	
	M_ss_cnt2          = 0; //Timer2频率反转计数初始化
	Step_Num_Cur2.word = 0; //当前已走步数
	motor_ss2          = SOFT_FRE_START_MIN2; //软启动 初始频率赋值

	//软启动频率变化幅值
	Fre_Fuzhi21 = MOTOR_ONE_LIMIT21;//(Given_Fre2.word - SOFT_FRE_START_MIN2)/SOFT_FRE_START_NUM2; 
	//软停止频率变化幅值
	Fre_Fuzhi22 = MOTOR_ONE_LIMIT22;//(Given_Fre2.word - SOFT_FRE_STOP_MIN2)/SOFT_FRE_STOP_NUM2; 
	//软停止步数索引
	Stop_index2 = 1;
	
	if(Motor_Direction2 == 1)//方向		
		M2_Dir_Forward;
	else if(Motor_Direction2 == 0)
		M2_Dir_Reverse;
}
/************************************************
* 函 数 名 : void SOFT_Start_M1(void)
* 硬件设计 : DengJh       软件设计 : HongCf
* 备    注 : 软启动、停止，低频启动，慢慢增加至额定频率
              停止时从额定频率降低至100Hz后停止
* 修改时间 : 2016.11.08
************************************************/
void SOFT_Start_M1(void)
{	
	MotorTime_Pulse1 = 0;
	//频率更改标志到达
	if(Timer_Send_Fre1 == 1)
	{
		Timer_Send_Fre1 = 0;//清标志
		Timer0AStart(motor_ss1);	//重置定时器	
		//软启动整个阶段都可以匹配相应的软停止
		if(motor_ss1 < FRE_MIN_LIMIT1)
			Stop_index1 = 1;
		else
			Stop_index1 = (motor_ss1/temp_stop1)*(SOFT_FRE_STOP_TIME1);
	}//软停止阶段
	if((M_SS_Fre_stop1 == 0)&&(Step_Num_Cur1.word > (Given_Step1.word - Stop_index1)))
	{
		M_SS_Fre_start1= 0;  //关闭软启动，进入软停止
		M_SS_Fre_stop1 = 1;              //软停止标志置位
		M_ss_cnt1 = SOFT_FRE_STOP_NUM1;  //软停止的频率变化次数
	}//步数走完
	if(Step_Num_Cur1.word >= Given_Step1.word)
		Motor1_Stop();
	if(Motor_Direction1 == 1)
	{
		if(M1_state.Limit1)
		{
			Motor1_Stop();
			Motor_New_Cmd1   = 1;
			Motor_Direction1 = 0;
		}
	}
	else
	{
		if(M1_state.Limit2)
		{
			Motor1_Stop();
			Motor_New_Cmd1   = 1;
			Motor_Direction1 = 1;
		}
	}
}
void SOFT_Start_M2(void)
{   
	MotorTime_Pulse2 = 0;
	//软启停频率更改阶段
	if(Timer_Send_Fre2 == 1)
	{
		Timer_Send_Fre2 = 0;//清除Timer2发送的频率更改标志
		Timer1AStart(motor_ss2);
		//软启动在哪个频率，相应的软停止步数也跟着变
		if(motor_ss2 < FRE_MIN_LIMIT2)
			Stop_index2 = 0;
		else
			Stop_index2 = (motor_ss2/temp_stop2)*(SOFT_FRE_STOP_TIME2);
	}//软停止阶段
	if((M_SS_Fre_stop2 == 0)&&(Step_Num_Cur2.word > (Given_Step2.word - Stop_index2)))
	{
		M_SS_Fre_start2= 0;   //关闭软启动，进入软停止
		M_SS_Fre_stop2 = 1;   //软停止标志置位
		M_ss_cnt2 = SOFT_FRE_STOP_NUM2;  //软停止的频率变化次数
	}//步数走完
	if(Step_Num_Cur2.word >= Given_Step2.word) 
		Motor2_Stop();

	if(Motor_Direction2 == 1) //判断电机运行方向
	{
		if(M2_state.Limit1)     //判断是否压到运行方向上的限位
		{
			Motor2_Stop();
			
			Motor_New_Cmd2   = 1;
			Motor_Direction2 = 0;
		}
	}
	else                      //判断电机运行方向
	{
		if(M2_state.Limit2)     //判断是否压到运行方向上的限位
		{
			Motor2_Stop();
			
			Motor_New_Cmd2   = 1;
			Motor_Direction2 = 1;
		}
	}
}
static void Motor1_Stop(void )
{
	TimerDisable(TIMER0_BASE, TIMER_A);  //关闭定时器0，停止脉冲反转
			
	MotorTime_Pulse1 = 0; //脉冲停止	
	Motor_Hold1      = 1; //电机处于停止保持状态
	Timer_Send_Fre1  = 0; //清空Timer2频率更改标志
	M_SS_Fre_start1  = 0; //停止软启动
	M_SS_Fre_stop1   = 0; //停止软停止	
}
static void Motor2_Stop(void )
{
	TimerDisable(TIMER1_BASE, TIMER_A);      //关闭定时器0，停止脉冲反转

	MotorTime_Pulse2 = 0; //脉冲停止	
	Motor_Hold2      = 1; //电机处于停止保持状态
	Timer_Send_Fre2  = 0; //清空Timer2频率更改标志
	M_SS_Fre_start2  = 0; //停止软启动
	M_SS_Fre_stop2   = 0; //停止软停止	
}





#include "AllDeal.h"


/************************************************
* �� �� �� : void TimerIntHandler_stepmotorX(void)
* Ӳ����� : DengJh       ������ : HongCf
* ��    ע : ��ʱʱ�䵽����main�����ź����������巴ת
* �޸�ʱ�� : 2016.11.28
************************************************/
void Timer0AHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	MotorTime_Pulse1 = 1;    //֪ͨ main() ����ͣ
	if(Motor_reversal1 == 0)
	{		
		M1_Pulse_High;
		Motor_reversal1 = 1;						 
	}
	else if(Motor_reversal1 == 1)
	{
		M1_Pulse_Low; 
		Motor_reversal1 = 0;
//		Step_Num_Cur1.word ++; // ��������
	}
	
}  
void Timer1AHandler(void)
{
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	MotorTime_Pulse2 = 1;    //֪ͨ main() ����ͣ
	if(Motor_reversal2 == 0)
	{
		M2_Pulse_High;
		Motor_reversal2 = 1;						 
	}
	else if(Motor_reversal2 == 1)
	{
		M2_Pulse_Low; 
		Motor_reversal2 = 0;
//		Step_Num_Cur2.word ++; // ��������
	}  
}

/************************************************
* �� �� �� : void Timer2IntHandler(void)
* Ӳ����� : DengJh       ������ : LiuXh + HongCf
* ��    ע : ��ʱ��2Aͬ������ϵͳ��ʱ�¼�
* �޸�ʱ�� : 2016.11.08
************************************************/
extern uint16_t motor_ss1;
extern uint16_t motor_ss2;
static uint8_t can1StartSend[8];
void Timer2AHandler(void)
{
	
	
	static uint16_t  Timer2_cnt = 0;
	static uint8_t   start_cnt = 0;
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	Timer2_cnt ++;
	if(Timer2_cnt >= 40&&(Drive_Limit_Time == 0))//��ʱ40msʹ������
	{
		Drive_Limit_Time=1;
		M1_Enable;
		M2_Enable;
	}//��� 1 �������׶�
	if((M_SS_Fre_start1 == 1)&&(M_ss_cnt1 < SOFT_FRE_START_NUM1)&&\
			   (Timer2_cnt % SOFT_FRE_START_TIME1 == 0))
	{
		motor_ss1 = motor_ss1 +  Fre_Fuzhi11;
		M_ss_cnt1 ++;
		Timer_Send_Fre1 = 1;
		if((motor_ss1 >= Given_Fre1.word)||(M_ss_cnt1 >= SOFT_FRE_START_NUM1))
		{
			motor_ss1 = Given_Fre1.word;
			M_SS_Fre_start1 = 0;
		}	
	}//��� 1 ��ֹͣ�׶�
	if((M_SS_Fre_stop1 == 1)&&(M_ss_cnt1 > 0)&&\
		(Timer2_cnt % SOFT_FRE_STOP_TIME1 == 0))
	{
		motor_ss1 = motor_ss1 - Fre_Fuzhi12;
		Timer_Send_Fre1 = 1;
		M_ss_cnt1 --;
		if(motor_ss1 < SOFT_FRE_STOP_MIN1)
		{
			motor_ss1 = SOFT_FRE_STOP_MIN1;
			M_SS_Fre_stop1 = 0;	
			M_ss_cnt1 = 0;
		}		
	}//��� 2 �������׶�
	if((M_SS_Fre_start2 == 1)&&(M_ss_cnt2 < SOFT_FRE_START_NUM2)&&\
		(Timer2_cnt % SOFT_FRE_START_TIME2 == 0))
	{
		motor_ss2 = motor_ss2 +  Fre_Fuzhi21;
		M_ss_cnt2 ++;
		Timer_Send_Fre2 = 1;
		if((motor_ss2 >= Given_Fre2.word)||(M_ss_cnt2 >= SOFT_FRE_START_NUM2))
		{
			motor_ss2 = Given_Fre2.word ;
			M_SS_Fre_start2 = 0;
		}
	}//��� 2 ��ֹͣ�׶�
	if((M_SS_Fre_stop2 == 1)&&(M_ss_cnt2 > 0)&&\
		(Timer2_cnt % SOFT_FRE_STOP_TIME2 == 0))
	{
		motor_ss2 = motor_ss2 - Fre_Fuzhi22;
		Timer_Send_Fre2 = 1;
		M_ss_cnt2 --;
		if(motor_ss2 < SOFT_FRE_STOP_MIN2)
		{
			motor_ss2 = SOFT_FRE_STOP_MIN2;
			M_SS_Fre_stop2 = 0;	
			M_ss_cnt2 = 0;
		}		
	}
	if(Timer2_cnt%500 == 0)       //1s
	{
		//����״̬��Ϣ
		if((Cmd_55_Flag == 0) && (start_cnt < 20))
		{
			can1StartSend[0] = 0x01; 
			can1StartSend[1] = 0x55;
			can1StartSend[2] = M1_state.byte;
			can1StartSend[3] = M2_state.byte;
			can1StartSend[4] = HARDWAREVERSION;
			can1StartSend[5] = (uint8_t)(SOFTWAREVERSION>>8);
			can1StartSend[6] = (uint8_t)(SOFTWAREVERSION&0x00FF);
			can1StartSend[7] = 0x00;						
			Can1DatasSend(can1StartSend,8,0x100);
			start_cnt ++;
		}
		if(LED_CONTROL)
		{LED_CONTROL = 0;LED_ON;}	
		else
		{LED_CONTROL = 1;LED_OFF;}	
	}	
	if((Timer2_cnt%20000)==19999)
	{
		
		//start_cnt1++;
		if(MOTOR_ISENABLE)
		{
			
			//M1_Disable;
			//M2_Disable;
			//Motor_New_Cmd1   = 0;
			//Motor_New_Cmd2   = 0;
			//Timer1_Disble();      //�رն�ʱ��0��ֹͣ���巴ת
		
			MOTOR_ISENABLE = 0;
		}
		else
		{
//			M1_Enable;
//			M2_Enable;
//			Motor_New_Cmd1   = 1;
//		//	Motor_New_Cmd2   = 0;
//			TimerLoadSet(TIMER0_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
//			TimerLoadSet(TIMER1_BASE, TIMER_A,ROM_SysCtlClockGet()/1000);
//			//Timer1_Enable();      //�رն�ʱ��0��ֹͣ���巴ת
//			
			MOTOR_ISENABLE = 1;
		}
	}
}   





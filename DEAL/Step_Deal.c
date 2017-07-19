#include "AllDeal.h"

uint16_t  motor_ss1 = 0;   //���Ƶ�� 1 ������Ƶ��
uint16_t  motor_ss2 = 0;   //���Ƶ�� 2 ������Ƶ��
uint16_t  Stop_index1 = 0;
uint16_t  Stop_index2 = 0;    

static void Motor1_Stop(void );
static void Motor2_Stop(void );

/************************************************
* �� �� �� : void STEP_StartX(void)
* Ӳ����� : DengJh       ������ : HongCf
* ��    ע : �¿���ָ����ʼ�����ã�����
* �޸�ʱ�� : 2016.11.08
************************************************/
void STEP_Start1(void)
{
	Motor_New_Cmd1   = 0;
	
	MotorTime_Pulse1 = 1;    //��������
	Motor_Hold1      = 0;    //ȡ�����֣�һֱʹ������
	Timer_Send_Fre1  = 1;    //����Ƶ����Ч
	M_SS_Fre_start1  = 1;    //��������Ч
	M_SS_Fre_stop1   = 0;    //��ֹͣ��Ч
	Motor_reversal1  = 0;    //��ʼ������
	M1_state.byte   &= 0x03; //��ʼ�������״̬
	
	
	M_ss_cnt1          = 0; //Timer2Ƶ�ʷ�ת������ʼ��
	Step_Num_Cur1.word = 0; //��ǰ���߲���
	motor_ss1          = SOFT_FRE_START_MIN1; //������ ��ʼƵ�ʸ�ֵ
	//������Ƶ�ʱ仯��ֵ
	Fre_Fuzhi11 = MOTOR_ONE_LIMIT11;//(Given_Fre1.word - SOFT_FRE_START_MIN1)/SOFT_FRE_START_NUM1; //������Ϊ�̶�ֵ���ԣ�Ч��Ӧ�÷ǳ���
	//��ֹͣƵ�ʱ仯��ֵ
	Fre_Fuzhi12 = MOTOR_ONE_LIMIT12;//(Given_Fre1.word - SOFT_FRE_STOP_MIN1)/SOFT_FRE_STOP_NUM1;//����Ϊ�̶�ֵ��һ��
	//��ֹͣ��������
	Stop_index1 =3; //(Given_Fre1.word - FRE_MIN_LIMIT1)/STEP_INDEX_NUM1;
	
	if(Motor_Direction1 == 1)//����
		M1_Dir_Forward;				 
	else if(Motor_Direction1 == 0)//�������
		M1_Dir_Reverse;			
}
void STEP_Start2(void)
{
	Motor_New_Cmd2   = 0;
	
	MotorTime_Pulse2 = 1;   //��������
	Motor_Hold2      = 0;   //ȡ�����֣�һֱʹ������
	Timer_Send_Fre2  = 1;   //����Ƶ����Ч
	M_SS_Fre_start2  = 1;   //��������Ч
	M_SS_Fre_stop2   = 0;   //��ֹͣ��Ч
	Motor_reversal2  = 0;   //��ʼ������
	
	M_ss_cnt2          = 0; //Timer2Ƶ�ʷ�ת������ʼ��
	Step_Num_Cur2.word = 0; //��ǰ���߲���
	motor_ss2          = SOFT_FRE_START_MIN2; //������ ��ʼƵ�ʸ�ֵ

	//������Ƶ�ʱ仯��ֵ
	Fre_Fuzhi21 = MOTOR_ONE_LIMIT21;//(Given_Fre2.word - SOFT_FRE_START_MIN2)/SOFT_FRE_START_NUM2; 
	//��ֹͣƵ�ʱ仯��ֵ
	Fre_Fuzhi22 = MOTOR_ONE_LIMIT22;//(Given_Fre2.word - SOFT_FRE_STOP_MIN2)/SOFT_FRE_STOP_NUM2; 
	//��ֹͣ��������
	Stop_index2 = 1;
	
	if(Motor_Direction2 == 1)//����		
		M2_Dir_Forward;
	else if(Motor_Direction2 == 0)
		M2_Dir_Reverse;
}
/************************************************
* �� �� �� : void SOFT_Start_M1(void)
* Ӳ����� : DengJh       ������ : HongCf
* ��    ע : ��������ֹͣ����Ƶ�����������������Ƶ��
              ֹͣʱ�ӶƵ�ʽ�����100Hz��ֹͣ
* �޸�ʱ�� : 2016.11.08
************************************************/
void SOFT_Start_M1(void)
{	
	MotorTime_Pulse1 = 0;
	//Ƶ�ʸ��ı�־����
	if(Timer_Send_Fre1 == 1)
	{
		Timer_Send_Fre1 = 0;//���־
		Timer0AStart(motor_ss1);	//���ö�ʱ��	
		//�����������׶ζ�����ƥ����Ӧ����ֹͣ
		if(motor_ss1 < FRE_MIN_LIMIT1)
			Stop_index1 = 1;
		else
			Stop_index1 = (motor_ss1/temp_stop1)*(SOFT_FRE_STOP_TIME1);
	}//��ֹͣ�׶�
	if((M_SS_Fre_stop1 == 0)&&(Step_Num_Cur1.word > (Given_Step1.word - Stop_index1)))
	{
		M_SS_Fre_start1= 0;  //�ر���������������ֹͣ
		M_SS_Fre_stop1 = 1;              //��ֹͣ��־��λ
		M_ss_cnt1 = SOFT_FRE_STOP_NUM1;  //��ֹͣ��Ƶ�ʱ仯����
	}//��������
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
	//����ͣƵ�ʸ��Ľ׶�
	if(Timer_Send_Fre2 == 1)
	{
		Timer_Send_Fre2 = 0;//���Timer2���͵�Ƶ�ʸ��ı�־
		Timer1AStart(motor_ss2);
		//���������ĸ�Ƶ�ʣ���Ӧ����ֹͣ����Ҳ���ű�
		if(motor_ss2 < FRE_MIN_LIMIT2)
			Stop_index2 = 0;
		else
			Stop_index2 = (motor_ss2/temp_stop2)*(SOFT_FRE_STOP_TIME2);
	}//��ֹͣ�׶�
	if((M_SS_Fre_stop2 == 0)&&(Step_Num_Cur2.word > (Given_Step2.word - Stop_index2)))
	{
		M_SS_Fre_start2= 0;   //�ر���������������ֹͣ
		M_SS_Fre_stop2 = 1;   //��ֹͣ��־��λ
		M_ss_cnt2 = SOFT_FRE_STOP_NUM2;  //��ֹͣ��Ƶ�ʱ仯����
	}//��������
	if(Step_Num_Cur2.word >= Given_Step2.word) 
		Motor2_Stop();

	if(Motor_Direction2 == 1) //�жϵ�����з���
	{
		if(M2_state.Limit1)     //�ж��Ƿ�ѹ�����з����ϵ���λ
		{
			Motor2_Stop();
			
			Motor_New_Cmd2   = 1;
			Motor_Direction2 = 0;
		}
	}
	else                      //�жϵ�����з���
	{
		if(M2_state.Limit2)     //�ж��Ƿ�ѹ�����з����ϵ���λ
		{
			Motor2_Stop();
			
			Motor_New_Cmd2   = 1;
			Motor_Direction2 = 1;
		}
	}
}
static void Motor1_Stop(void )
{
	TimerDisable(TIMER0_BASE, TIMER_A);  //�رն�ʱ��0��ֹͣ���巴ת
			
	MotorTime_Pulse1 = 0; //����ֹͣ	
	Motor_Hold1      = 1; //�������ֹͣ����״̬
	Timer_Send_Fre1  = 0; //���Timer2Ƶ�ʸ��ı�־
	M_SS_Fre_start1  = 0; //ֹͣ������
	M_SS_Fre_stop1   = 0; //ֹͣ��ֹͣ	
}
static void Motor2_Stop(void )
{
	TimerDisable(TIMER1_BASE, TIMER_A);      //�رն�ʱ��0��ֹͣ���巴ת

	MotorTime_Pulse2 = 0; //����ֹͣ	
	Motor_Hold2      = 1; //�������ֹͣ����״̬
	Timer_Send_Fre2  = 0; //���Timer2Ƶ�ʸ��ı�־
	M_SS_Fre_start2  = 0; //ֹͣ������
	M_SS_Fre_stop2   = 0; //ֹͣ��ֹͣ	
}





#include "System_Init.h"

FLAGBITS Flagbits;
UintToUchar Given_Fre1 ;  //��� 1 ����Ƶ��
UintToUchar Given_Fre2 ;  //��� 2 ����Ƶ��
UintToUchar Given_Step1 ; //��� 1 ��������
UintToUchar Given_Step2;  //��� 2 ��������

UintToUchar Step_Num_Cur1;//��� 1 ��ǰ���߲���
UintToUchar Step_Num_Cur2;//��� 2 ��ǰ���߲���

uint8_t Cmd_IsNew1;       //��� 1 ��ָ���Ƿ�����
uint8_t Cmd_IsNew2;       //��� 2 ��ָ���Ƿ�����

MOTOR_LOCATION M1_state;     //��� 1 ���б�־�ֽ�
MOTOR_LOCATION M2_state;     //��� 1 ���б�־�ֽ�


uint16_t  M_ss_cnt1;   //��� 1 ����ͣƵ�ʸ��Ĵ���
uint16_t  M_ss_cnt2;   //��� 2 ����ͣƵ�ʸ��Ĵ���

uint16_t Fre_Fuzhi11; //��� 1 ��������ֵ
uint16_t Fre_Fuzhi21; //��� 2 ��������ֵ

uint16_t Fre_Fuzhi12; //��� 1 ��ֹͣ��ֵ
uint16_t Fre_Fuzhi22; //��� 2 ��ֹͣ��ֵ



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
//ȫ�ֱ�����ʼ��
static void GlobalVar_Init(void )
{
	MotorTime_Pulse1    =0; //Timer0A ��ʱʱ�䵽
	MotorTime_Pulse2    =0; //Timer1A ��ʱʱ�䵽
	Motor_reversal1     =0; //���Ƶ�� 1 �ߵ͵�ƽ��ת
	Motor_reversal2     =0; //���Ƶ�� 2 �ߵ͵�ƽ��ת
	Motor_Hold1         =1; //��� 1 ��̬����  �ϵ籣��
	Motor_Hold2         =1; //��� 2 ��̬����  �ϵ籣��
	Motor_Direction1    =0; //��� 1 ת��
	Motor_Direction2    =0; //��� 2 ת��
	Motor_New_Cmd1      =0; //��� 1 ��ָ���
	Motor_New_Cmd2      =0; //��� 2 ��ָ���
	LED_CONTROL         =0; //LED�����־
	
	MOTOR_ISENABLE      =1; //�������ʹ��
	
	Motor_Holdreversal  =0; //��� 12 ��̬ʹ�ܷ�ת
	Cmd_55_Flag         =0; //���� 0x55 ָ���־
	Drive_Limit_Time    =0; //����ʱ�����Ʊ�־(40ms��ʹ��)	
	
	Timer_Send_Fre1     =0; //��� 1 ������Ƶ�ʸ��ı�־
	M_SS_Fre_start1     =0; //��� 1 ��������־
	M_SS_Fre_stop1      =0; //��� 1 ��ֹͣ��־
	Timer_Send_Fre2     =0; //��� 2 ������Ƶ�ʸ��ı�־
	M_SS_Fre_start2     =0; //��� 2 ��������־
	M_SS_Fre_stop2      =0; //��� 2 ��ֹͣ��־

	Given_Fre1.word  = 0; //��� 1 ����Ƶ��
	Given_Fre2.word  = 0; //��� 2 ����Ƶ��
	Given_Step1.word = 0; //��� 1 ��������
	Given_Step2.word = 0; //��� 2 ��������

	Step_Num_Cur1.word = 0x0000;//��� 1 ��ǰ���߲���
	Step_Num_Cur2.word = 0x0000;//��� 2 ��ǰ���߲���

	Cmd_IsNew1 = 0x64;   //��� 1 ��ָ���Ƿ�����
	Cmd_IsNew2 = 0x64;   //��� 2 ��ָ���Ƿ�����
	M1_state.byte = 0x00;   //��ʼû����Ϊû��ѹ����λ������
	M2_state.byte = 0x00;   //��ʼû����Ϊû��ѹ����λ������    
	
	M_ss_cnt2   = 0; //��������ʼ����
	Fre_Fuzhi21 = 0; //������Ƶ������ֵ
	Fre_Fuzhi22 = 0; //��ֹͣƵ�ʽ���ֵ
	M_ss_cnt1   = 0;
	Fre_Fuzhi11 = 0;
	Fre_Fuzhi12 = 0;
}


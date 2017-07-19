#include "system.h"
#include "System_Init.h"
#include "AllDeal.h"

static void LimitButtonCheck(void);

int main(void)
{
	SystemInit();
	while(1)
	{
		LimitButtonCheck();      //��λ���
		Can1_DataDeal();         //����CAN���ݰ�
		
		
		if(Motor_New_Cmd1 == 1)//��� 1 �¿���ָ���
			STEP_Start1();//��� 1 ������ʼ��
		 
		if(Motor_New_Cmd2 == 1)//��� 2 �¿���ָ���
			STEP_Start2();//��� 2 ������ʼ��
		
		if(MotorTime_Pulse1 == 1)//�µĲ���ִ�����  ����ͣ
			SOFT_Start_M1();
		
		if(MotorTime_Pulse2 == 1)//�µĲ���ִ�����  ����ͣ
			SOFT_Start_M2();
	}	
}



#define Delay_Limit  100
uint8_t cnt1 = 0,cnt2 = 0,cnt3 	= 0,cnt4 = 0;
static void LimitButtonCheck(void)
{
if(M1_Read_S1 == 0x00)    //����������λ
	{
		cnt1 ++;
		if(cnt1 > Delay_Limit)
			M1_state.Limit1 = 1; 
	}		
	else{	
		cnt1 = 0;
		M1_state.Limit1 = 0;
	}	
	if(M1_Read_S2 == 0x00)    //����������λ
	{
		cnt2 ++;
		if(cnt2 > Delay_Limit)
			M1_state.Limit2 = 1; 
	}
	else{
		cnt2 = 0;
		M1_state.Limit2 = 0; 
	}
	
	if(M2_Read_S1 == 0x00)    //����������λ���ӱ��濴��
	{
		cnt3 ++;
		if(cnt3 > Delay_Limit)
			M2_state.Limit1 = 1; 
	}	 
	else{
		cnt3 = 0;
		M2_state.Limit1 = 0;
	} 
	if(M2_Read_S2 == 0x00)    //����������λ���ӱ��濴��
	{
		cnt4 ++;
		if(cnt4 > Delay_Limit)
			M2_state.Limit2 = 1; 
	}	
	else{
		cnt4 = 0;
		M2_state.Limit2 = 0; 
	}		
}





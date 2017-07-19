#include "AllDeal.h"
 
#define MOTOR1     0x90    //���Ƶ�� 1 ��ָ�� �������
#define MOTOR2     0x30	   //���Ƶ�� 2 ��ָ�� ƫ�����
#define INTERFACE  0x00    //�ز��ӿڰ�

extern CanFifo can1RxFifo;
static uint8_t can1RxDatas[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//��ȡ���ݰ�

static void DataToMotor1(void );
static void DataToMotor2(void );
static void InterFaceDeal(void);

bool Can1_DataDeal(void)
{
	bool isRxNull = CanFifo_Request(&can1RxFifo,can1RxDatas);//����ն�����ȡ����
	if(!isRxNull)           //������û������ֱ�ӷ���
		return false;
	switch(can1RxDatas[0])
	{
		case MOTOR1:DataToMotor1();break;//���1�����ݰ�
		case MOTOR2:DataToMotor2();break;//���2�����ݰ�
		case INTERFACE:	InterFaceDeal();break;	//���������Ե�ָ�
		default:	break;
	}
	return true;
}

static void DataToMotor1(void )
{
	switch(can1RxDatas[1])
	{
		case 0xF4:                //0xF4ָ��
			if(Cmd_IsNew1 != can1RxDatas[6])
			{
				Cmd_IsNew1 = can1RxDatas[6];
				Given_Fre1.byte[1] = can1RxDatas[2];//����Ƶ��
				Given_Fre1.byte[0] = can1RxDatas[3];
				Given_Step1.byte[1] = can1RxDatas[4];//��������
				Given_Step1.byte[0] = can1RxDatas[5];
				Step_Num_Cur1.byte[0] = 0x00;//���߲�������
				Step_Num_Cur1.byte[1] = 0x00;//���߲�������
				if(can1RxDatas[7] == 0x00)
					Motor_Direction1 = 0;
				else 
					Motor_Direction1 = 1;
				Motor_New_Cmd1 = 1;
			}break;
		case 0xF3: 
			can1RxDatas[1] = 0xF3;break;
		default:break;
	}		
	can1RxDatas[0] = MOTOR1 + 1;
	can1RxDatas[2] = Step_Num_Cur1.byte[1];//���ص�ǰ���߲���
	can1RxDatas[3] = Step_Num_Cur1.byte[0];//
	can1RxDatas[4] = M1_state.byte;		   //���ص�ǰ��λ״̬	
	can1RxDatas[5] = 0;can1RxDatas[6] = 0;
	can1RxDatas[7] = Cmd_IsNew1;
	Can1DatasSend(can1RxDatas,8,0x100);
}
static void DataToMotor2(void )
{
	switch(can1RxDatas[1])
	{
		case 0xF4:                   //0xF4ָ��
			if(Cmd_IsNew2 != can1RxDatas[6])
			{
				Cmd_IsNew2 = can1RxDatas[6];
				Given_Fre2.byte[1] = can1RxDatas[2];
				Given_Fre2.byte[0] = can1RxDatas[3];
				Given_Step2.byte[1] = can1RxDatas[4];
				Given_Step2.byte[0] = can1RxDatas[5];
				Step_Num_Cur2.byte[0] = 0x00;//���߲�������
				Step_Num_Cur2.byte[1] = 0x00;//���߲�������
				if(can1RxDatas[7] == 0x00)
					Motor_Direction2 = 0;
				else 
					Motor_Direction2 = 1;
				Motor_New_Cmd2 = 1;
			}break;
		case 0xF3: 
			can1RxDatas[1] = 0xF3;break;
		default:break;
	}		
	can1RxDatas[0] = MOTOR2 + 1;
	can1RxDatas[2] = Step_Num_Cur2.byte[1];//���ص�ǰ���߲���
	can1RxDatas[3] = Step_Num_Cur2.byte[0];//
	can1RxDatas[4] = M2_state.byte;	       //���ص�ǰ��λ״̬
	can1RxDatas[5] = 0;can1RxDatas[6] = 0;
	can1RxDatas[7] = Cmd_IsNew2;
	Can1DatasSend(can1RxDatas,8,0x100);
}
static void InterFaceDeal(void)
{
	switch(can1RxDatas[1])
	{
		case 0x55:    //�յ��ظ�ָ��
			can1RxDatas[0] = 0x02;
			can1RxDatas[1] = 0x55;
			can1RxDatas[2] = M1_state.byte;
			can1RxDatas[3] = M2_state.byte;
			can1RxDatas[4] = HARDWAREVERSION;
			can1RxDatas[5] = (uint8_t)(SOFTWAREVERSION>>8);
			can1RxDatas[6] = (uint8_t)(SOFTWAREVERSION&0x00FF);
			can1RxDatas[7] = 0x00;
			Can1DatasSend(can1RxDatas,8,0x100);
			Cmd_55_Flag	 = 1;break;
		case 0x80:
			can1RxDatas[0] = 0x02;
			can1RxDatas[1] = 0x81;
			can1RxDatas[4] = 0x00;
			can1RxDatas[5] = 0x00;
			can1RxDatas[6] = 0x00;
			can1RxDatas[7] = 0x00;
			Can1DatasSend(can1RxDatas,8,0x100);break;
		case 0x50:break;//����ָ��   δ�����������
		default:break;
	}
}









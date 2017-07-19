#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__

#include "system.h"
#include "fifo.h"
//������λ
#define M1_Read_S1    (ROM_GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) & GPIO_PIN_7)
#define M1_Read_S2    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_3) & GPIO_PIN_3)
#define M2_Read_S1    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_2) & GPIO_PIN_2)
#define M2_Read_S2    (ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1) & GPIO_PIN_1)

//������λ
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

void GPIO_Init(void);            //GPIO��ʼ��

void CAN1_Init(void);
int Can1DatasSend( unsigned char *pSend1Buffer,
				   unsigned char send1Len ,
			       unsigned long msgID1);
void Can1_Read(void);

void Timer_Init(void);           //��ʱ����ʼ��
void Timer0AStart(uint16_t tim); //������ʱ��
void Timer1AStart(uint16_t tim);

void SystemInit(void);

/************     ϵͳȫ�ֱ���      **********************/
extern FLAGBITS Flagbits; 

extern  UintToUchar Given_Fre1 ;  //��� 1 ����Ƶ��
extern  UintToUchar Given_Fre2 ;  //��� 2 ����Ƶ��
extern  UintToUchar Given_Step1 ; //��� 1 ��������
extern  UintToUchar Given_Step2;  //��� 2 ��������

extern  UintToUchar Step_Num_Cur1;//��� 1 ��ǰ���߲���
extern  UintToUchar Step_Num_Cur2;//��� 2 ��ǰ���߲���

extern  uint8_t Cmd_IsNew1;       //��� 1 ��ָ���Ƿ�����
extern  uint8_t Cmd_IsNew2;       //��� 2 ��ָ���Ƿ�����

extern  MOTOR_LOCATION M1_state;     //��� 1 ���б�־�ֽ�
extern  MOTOR_LOCATION M2_state;     //��� 1 ���б�־�ֽ�


extern  uint16_t  M_ss_cnt1;   //��� 1 ����ͣƵ�ʸ��Ĵ���
extern  uint16_t  M_ss_cnt2;   //��� 2 ����ͣƵ�ʸ��Ĵ���

extern  uint16_t Fre_Fuzhi11; //��� 1 ��������ֵ
extern  uint16_t Fre_Fuzhi21; //��� 2 ��������ֵ

extern  uint16_t Fre_Fuzhi12; //��� 1 ��ֹͣ��ֵ
extern  uint16_t Fre_Fuzhi22; //��� 2 ��ֹͣ��ֵ

#endif



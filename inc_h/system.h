#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <cstdlib>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <hw_memmap.h>
#include <debug.h>
#include <gpio.h>
#include <rom.h>
#include <sysctl.h>
#include <hw_flash.h>
#include <hw_ints.h>
#include <hw_sysctl.h>
#include <hw_types.h>
#include <hw_uart.h>
#include <hw_adc.h>
#include <hw_can.h>
#include <interrupt.h>
#include <eeprom.h>
#include <hw_eeprom.h>
#include <hw_gpio.h>
#include <hw_nvic.h>
#include <hw_i2c.h>
#include <hw_timer.h>
#include <i2c.h>
#include <can.h>
#include <interrupt.h>
#include <cpu.h>
#include <timer.h>
#include <uart.h>
#include <pin_map.h>
#include <uartstdio.h>
#include <systick.h>
#include <pwm.h>
#include <hw_pwm.h>
#include <adc.h>

typedef union
{
	uint16_t word;
	uint8_t  byte[2];
}UintToUchar;

typedef union
{
	int16_t word;
	int8_t  byte[2];
}intToUchar;

typedef union
{
	uint32_t word;
  uint16_t byte16[2];
	uint8_t  byte[4];
}UlongToUchar;

typedef union
{
	int32_t word;
  int16_t byte16[2];
	uint8_t byte[4];
}longToUchar;



#pragma anon_unions
typedef union
{
   uint8_t byte;
   struct
   {
       unsigned Limit1 :1;    
       unsigned Limit2 :1;  
       unsigned :1; 
       unsigned :1; 
       unsigned :1;   
       unsigned :1;     
       unsigned :1;
       unsigned :1;  
       unsigned :1;
   };
}MOTOR_LOCATION;
typedef union tagFLAGBITS{
	uint16_t byte[4];
	struct
	{
			unsigned fg0:1;
			unsigned fg1:1;
			unsigned fg2:1;
			unsigned fg3:1;
			unsigned fg4:1;
			unsigned fg5:1;
			unsigned fg6:1;
			unsigned fg7:1;
			unsigned fg8:1;
			unsigned fg9:1;
			unsigned fg10:1;
			unsigned fg11:1;
			unsigned fg12:1;
			unsigned fg13:1;
			unsigned fg14:1;
			unsigned fg15:1;
			unsigned fg16:1;
			unsigned fg17:1;
			unsigned fg18:1;
			unsigned fg19:1;
			unsigned fg20:1;
			unsigned fg21:1;
			unsigned fg22:1;
			unsigned fg23:1;
			unsigned fg24:1;
			unsigned fg25:1;
			unsigned fg26:1;
			unsigned fg27:1;
			unsigned fg28:1;
			unsigned fg29:1;
			unsigned fg30:1;
			unsigned fg31:1;	
  };
}FLAGBITS;
extern FLAGBITS Flagbits;
#define MotorTime_Pulse1           Flagbits.fg0  //Timer0A ��ʱʱ�䵽
#define MotorTime_Pulse2           Flagbits.fg1  //Timer1A ��ʱʱ�䵽
#define Motor_reversal1            Flagbits.fg2  //���Ƶ�� 1 �ߵ͵�ƽ��ת
#define Motor_reversal2            Flagbits.fg3  //���Ƶ�� 2 �ߵ͵�ƽ��ת
#define Motor_Hold1                Flagbits.fg4  //��� 1 ��̬����
#define Motor_Hold2                Flagbits.fg5	 //��� 2 ��̬����
#define Motor_Direction1           Flagbits.fg6  //��� 1 ת��
#define Motor_Direction2           Flagbits.fg7  //��� 2 ת��
#define Motor_New_Cmd1             Flagbits.fg8  //��� 1 ��ָ���
#define Motor_New_Cmd2             Flagbits.fg9  //��� 2 ��ָ���

#define Cmd_55_Flag                Flagbits.fg10 //���� 0x55 ָ���־
#define Motor_Holdreversal         Flagbits.fg11 //��� 12 ��̬ʹ�ܷ�ת
#define Drive_Limit_Time           Flagbits.fg12 //�������ʹ���ӳ�ʱ�䵽���־

#define Timer_Send_Fre1            Flagbits.fg13 //��� 1 Ƶ�ʸ��ı�־
#define M_SS_Fre_start1            Flagbits.fg14 //��� 1 ��������־
#define M_SS_Fre_stop1             Flagbits.fg15 //��� 1 ��ֹͣ��־ 

#define Timer_Send_Fre2            Flagbits.fg16 //��� 2 Ƶ�ʸ��ı�־
#define M_SS_Fre_start2            Flagbits.fg17 //��� 2 ��������־
#define M_SS_Fre_stop2             Flagbits.fg18 //��� 2 ��ֹͣ��־ 

#define LED_CONTROL                Flagbits.fg19 //����LED��˸

#define MOTOR_ISENABLE             Flagbits.fg20 //�����õ������ת


#define SOFTWAREVERSION   20   //����汾
#define HARDWAREVERSION   20   //Ӳ���汾




//  boot������
#define DELAPPCOMA  0xaaaaaaaa
#define DELAPPCOMB  0x55555555
#define JMPSPIADDR     100

#define BOARDCONFIGADDR     300
#define BOARDCONFIGSIZE     5

#define BOARDHARDWARE_VER   0 
#define BOARDSOFTWARE_VER   1
#define BOARDCANID          2
#define BOARDSELFCANID      3
#define BOARDMACCANID       4

/****************************************************************************
                               variable
****************************************************************************/




#ifdef DUBUG
extern uint8_t Computer_Rec_Cortex_SendHMI_Data[10];
extern uint8_t Computer_Rec_HMI_SendCortex_Data[10];
#endif
extern  uint16_t SoftWareVersion;
extern  int16_t   TempAdcVal;
extern  UintToUchar Cpu_Tmp_Buf;
extern  int32_t temperature;



#endif






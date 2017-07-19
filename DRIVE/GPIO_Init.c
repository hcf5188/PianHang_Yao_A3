#include "System_Init.h"

void GPIO_Init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	HWREG(GPIO_PORTD_BASE  + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE  + GPIO_O_CR) |= 0x80;				

//  ������λ����
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);//M1_Limit1
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_3);//M1_limit2	
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_2);//M2_Limit1
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);//M2_Limit2
	
//  ������λ
//	ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_3);//M1_Limit1
//	ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4);//M1_limit2	
//	ROM_GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);//M2_Limit1
//	ROM_GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);//M2_Limit2
	
	
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);//DIR1
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);//EN1
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);//PULSE1
	
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);//DIR2
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);//EN2
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);//PULSE2	

	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);//LED test
	
	M1_Dir_Forward;		//����		
	M1_Disable;
	M1_Pulse_High;
	
	M2_Dir_Forward;				
	M2_Disable;
	M2_Pulse_High;
	
	LED_OFF;
}




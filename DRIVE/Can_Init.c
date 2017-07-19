#include "System_Init.h"

#define CAN1RXID                0x102
#define RX1BJECT                1
#define CAN1TXID                0x100
#define TX1BJECT                25

void CAN1_Handler (void);       //CAN中断函数声明


tCANMsgObject can1RxMessage;
tCANMsgObject can1TxMessage;
uint8_t Ui8TxMsgDataCAN1[8] = {0x03,0x11,0x44,0x33,0x66,0x55,0x88,0x77};
uint8_t Ui8RxMsgDataCAN1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


CanFifo can1RxFifo;      //CAN接收队列控制块
void  *rxMsg[15];        //指针数组
uint8_t rxFifo[15][8];   //CAN数据包缓冲区

void CAN1_Init(void)
{
	int id_can1rx = 0;
	
	CanFifo_Init(&can1RxFifo,rxMsg,15,rxFifo);
	
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );				
	GPIOPinConfigure(GPIO_PA0_CAN1RX);
	GPIOPinConfigure(GPIO_PA1_CAN1TX);						 
	GPIOPinTypeCAN( GPIO_PORTA_BASE, GPIO_PIN_1 | GPIO_PIN_0 );
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
	CANInit(CAN1_BASE);
	
	// Set up the bit rate for the CAN bus.  This function sets up the CAN
	// bus timing for a nominal configuration.  You can achieve more control
	// over the CAN bus timing by using the function CANBitTimingSet() instead
	// of this one, if needed.
	// In this example, the CAN bus is set to 500 kHz.
	CANBitRateSet(CAN1_BASE, ROM_SysCtlClockGet(), 500000);
	// Enable interrupts on the CAN peripheral.  This example uses static
	// allocation of interrupt handlers which means the name of the handler
	// is in the vector table of startup code.
	CANIntEnable(CAN1_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	// Enable the CAN interrupt on the processor (NVIC).
	IntEnable(INT_CAN1);
	// Enable the CAN for operation.
	CANEnable(CAN1_BASE);
	// Initialize a message object to be used for receiving CAN messages with
	// any CAN ID.  In order to receive any CAN ID, the ID and mask must both
	// be set to 0, and the ID filter enabled.
	can1RxMessage.ui32MsgID     = CAN1RXID;
	can1RxMessage.ui32MsgIDMask = 0xFFFFF;
	can1RxMessage.ui32Flags     = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER | MSG_OBJ_FIFO);
	can1RxMessage.ui32MsgLen    = sizeof(Ui8RxMsgDataCAN1);
	// Now load the message object into the CAN peripheral.  Once loaded the
	// CAN will receive any message on the bus, and an interrupt will occur.
	// Use message object RX1BJECT for receiving messages (this is not the
	// same as the CAN ID which can be any value in this example).				
	// CANMessageSet(CAN1_BASE, RX1BJECT, &can1RxMessage, MSG_OBJ_TYPE_RX);		
	for(id_can1rx = 0;id_can1rx < 16;id_can1rx ++)
		CANMessageSet( CAN1_BASE, id_can1rx+1, 
			&can1RxMessage, MSG_OBJ_TYPE_RX );
	// Initialize the message object that will be used for sending CAN
	// messages.  The message will be 1 bytes that will contain the character
	// received from the other controller. Initially it will be set to 0.
	can1TxMessage.ui32MsgID = CAN1TXID;
	can1TxMessage.ui32MsgIDMask = 0;
	can1TxMessage.ui32Flags = MSG_OBJ_FIFO;
	can1TxMessage.ui32MsgLen = sizeof(Ui8TxMsgDataCAN1);
	can1TxMessage.pui8MsgData = Ui8TxMsgDataCAN1;
	CANIntRegister(CAN1_BASE, CAN1_Handler);
}

int Can1DatasSend( unsigned char *pSend1Buffer,
				   unsigned char send1Len ,
			       unsigned long msgID1)
{
	static unsigned char u1TxMsgObjNr = 17;
	tCANMsgObject MsgObjectTx;
	
	u1TxMsgObjNr ++;   
	if( u1TxMsgObjNr >32 )
		u1TxMsgObjNr = 17;
	
	MsgObjectTx.ui32Flags     = MSG_OBJ_FIFO;		
	MsgObjectTx.ui32MsgIDMask = 0;
	MsgObjectTx.ui32MsgID	  = msgID1;
	
	MsgObjectTx.ui32MsgLen	= send1Len;
	MsgObjectTx.pui8MsgData	= pSend1Buffer;
	
	CLEAE_CAN( CAN1_BASE );
	
	CANMessageSet( CAN1_BASE,u1TxMsgObjNr, 
						&MsgObjectTx, MSG_OBJ_TYPE_TX); 
    
	return send1Len;
}

void CAN1_Handler (void)
{
    tCANMsgObject   MsgObjectBuf;
    uint32_t   ulMsgObjID;
    uint32_t   ulNewData = 0;
	unsigned char   ucTemp[8];
    unsigned char   i = 0;
	
	ulMsgObjID = CANIntStatus( CAN1_BASE, CAN_INT_STS_CAUSE );
	CANIntClear(CAN1_BASE, CAN_INT_INTID_STATUS );

	CLEAE_CAN( CAN1_BASE );
	if( ulMsgObjID != 0 )
	{       		
		ulNewData  = CANStatusGet( CAN1_BASE, CAN_STS_NEWDAT );
		MsgObjectBuf.pui8MsgData = ucTemp;
		if( ulNewData != 0 )
		{		
			for( i = 0; i < 32; i ++ )
			{
				if( ulNewData &( 1 << i ) )
				{                         
					CANMessageGet(CAN1_BASE,1+i,&MsgObjectBuf, true ); 	
					CanFifo_Post(&can1RxFifo,ucTemp);
					CANIntClear( CAN1_BASE,i + 1 );
				}
			}		
		}
	} 
}





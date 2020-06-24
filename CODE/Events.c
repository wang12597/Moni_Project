/** ###################################################################
**     Filename  : Events.C
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/1, 11:03
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "includes.h"
volatile stSystemState g_stSystemState;
/*
** ===================================================================
**     Event       :  Uart_OnError (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be
**         read using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  Uart_OnError(void)
{
 /* Write your code here ... */
 
}

/*
** ===================================================================
**     Event       :  Uart_OnRxChar (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the
**         <Receiver> property is enabled or the <SCI output mode>
**         property (if supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
volatile uint8 g_u8RxdNum = 0;   //接收字节计数器
volatile uint8 g_u8RxdBuff[64];  //接收字节缓冲区
void  Uart_OnRxChar(void)
{
 /* Write your code here ... */
 	uint8 l_u8RecChr = 0;
  Uart_RecvChar(&l_u8RecChr);
  if(g_u8RxdNum < sizeof(g_u8RxdBuff)) {
    g_u8RxdBuff[g_u8RxdNum] = l_u8RecChr;
    g_u8RxdNum++;
  }
}

/*
** ===================================================================
**     Event       :  Uart_OnTxChar (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  Uart_OnTxChar(void)
{
 /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Uart_OnFullRxBuf (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  Uart_OnFullRxBuf(void)
{
 /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Uart_OnFreeTxBuf (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  Uart_OnFreeTxBuf(void)
{
 /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
volatile uint32 g_u32DelayCounter = 0;
volatile uint32 g_u32DelayTimer = 0; 
volatile uint8  g_u8MoniFlag = 0; 
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
   MYUART_485RxMoni();
   g_u32DelayCounter++;
   if(g_u32DelayCounter == 1000)
   {
      g_u32DelayCounter   = 0;
      g_u8MoniFlag = 1;
   }
}

/*
** ===================================================================
**     Event       :  Uart_OnTxComplete (module Events)
**
**     Component   :  Uart [AsynchroSerial]
**     Description :
**         This event indicates that the transmitter is finished
**         transmitting all data, preamble, and break characters and
**         is idle. It can be used to determine when it is safe to
**         switch a line driver (e.g. in RS-485 applications).
**         The event is available only when both <Interrupt
**         service/event> and <Transmitter> properties are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
volatile uint8 UartTxSendOkFlag = 0;
void Uart_OnTxComplete(void)
{
  /* Write your code here ... */
  RS485W_EN_PutVal(0);
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

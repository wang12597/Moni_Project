/** ###################################################################
**     Filename  : Events.H
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

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "RS485W_EN.h"
#include "Uart.h"
#include "LED.h"
#include "TI1.h"
#include "SPI7708CS.h"
#include "SPI7708CLK.h"
#include "SPI7708SDI.h"
#include "SPI7708SDO.h"
#include "MYEEPROM.h"
#include "SPI7708EN.h"


void Uart_OnError(void);
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

void Uart_OnRxChar(void);
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

void Uart_OnTxChar(void);
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

void Uart_OnFullRxBuf(void);
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

void Uart_OnFreeTxBuf(void);
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

void TI1_OnInterrupt(void);
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

void Uart_OnTxComplete(void);
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

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

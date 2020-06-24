/** ###################################################################
**     Filename  : Dilute_Test.C
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Version   : Driver 01.11
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/1, 14:26
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Dilute_Test */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "includes.h"
extern volatile uint32 g_u32DelayTimer;
extern volatile uint8 g_u8RxdBuff[64];  //接收字节缓冲区
extern volatile uint8  g_u8MoniFlag; //监控标志
void main(void)
{
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  SystemInit();
  LED_PutVal(0);
  for(;;)
  {
    MYUART_485Driver();
   if(g_u8MoniFlag ==1 )
   {
      g_u8MoniFlag=0;
      RealStateMoni();
   }
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END Dilute_Test */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

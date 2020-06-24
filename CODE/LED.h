/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : LED.H
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.21, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/1, 14:32
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       24            |  PTB1_PIB1_ADP9
**             ----------------------------------------------------
**
**         Port name                   : PTB
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 1
**         Initial pull option         : off
**
**         Port data register          : PTBD      [$0002]
**         Port control register       : PTBDD     [$0003]
**
**         Optimization for            : speed
**     Contents  :
**         SetDir - void LED_SetDir(bool Dir);
**         GetVal - bool LED_GetVal(void);
**         PutVal - void LED_PutVal(bool Val);
**         ClrVal - void LED_ClrVal(void);
**         SetVal - void LED_SetVal(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef LED_H_
#define LED_H_

/* MODULE LED. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  LED_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define LED_GetVal() ( \
    (bool)((getReg8(PTBD) & 0x02))     /* Return port data */ \
  )

/*
** ===================================================================
**     Method      :  LED_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void LED_PutVal(bool Val);

/*
** ===================================================================
**     Method      :  LED_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**           a) direction = Input  : sets the output value to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define LED_ClrVal() ( \
    (void)clrReg8Bits(PTBD, 0x02)      /* PTBD1=0x00 */, \
    Shadow_PTB &= (byte)~0x02          /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  LED_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**           a) direction = Input  : sets the output value to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define LED_SetVal() ( \
    (void)setReg8Bits(PTBD, 0x02)      /* PTBD1=0x01 */, \
    Shadow_PTB |= (byte)0x02           /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  LED_SetDir (component BitIO)
**
**     Description :
**         This method sets direction of the bean.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Dir        - Direction to set (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
**     Returns     : Nothing
** ===================================================================
*/
void LED_SetDir(bool Dir);



/* END LED. */
#endif /* #ifndef __LED_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

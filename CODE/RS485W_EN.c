/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : RS485W_EN.C
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.21, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/1, 13:30
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Output direction only.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       1             |  PTA7_PIA7_ADP7_IRQ
**             ----------------------------------------------------
**
**         Port name                   : PTA
**
**         Bit number (in port)        : 7
**         Bit mask of the port        : $0080
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTAD      [$0000]
**         Port control register       : PTADD     [$0001]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool RS485W_EN_GetVal(void);
**         PutVal - void RS485W_EN_PutVal(bool Val);
**         ClrVal - void RS485W_EN_ClrVal(void);
**         SetVal - void RS485W_EN_SetVal(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE RS485W_EN. */

#include "RS485W_EN.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  RS485W_EN_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This bean is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool RS485W_EN_GetVal(void)

**  This method is implemented as a macro. See RS485W_EN.h file.  **
*/

/*
** ===================================================================
**     Method      :  RS485W_EN_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void RS485W_EN_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PTAD, 0x80);           /* PTAD7=0x01 */
  } else { /* !Val */
    clrReg8Bits(PTAD, 0x80);           /* PTAD7=0x00 */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  RS485W_EN_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void RS485W_EN_ClrVal(void)

**  This method is implemented as a macro. See RS485W_EN.h file.  **
*/

/*
** ===================================================================
**     Method      :  RS485W_EN_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void RS485W_EN_SetVal(void)

**  This method is implemented as a macro. See RS485W_EN.h file.  **
*/


/* END RS485W_EN. */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

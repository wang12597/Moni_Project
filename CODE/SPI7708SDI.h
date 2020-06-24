/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : SPI7708SDI.H
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.21, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/3, 9:17
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
**                       11            |  PTE4_SCL_MOSI
**             ----------------------------------------------------
**
**         Port name                   : PTE
**
**         Bit number (in port)        : 4
**         Bit mask of the port        : $0010
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTED      [$0008]
**         Port control register       : PTEDD     [$0009]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool SPI7708SDI_GetVal(void);
**         PutVal - void SPI7708SDI_PutVal(bool Val);
**         ClrVal - void SPI7708SDI_ClrVal(void);
**         SetVal - void SPI7708SDI_SetVal(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef SPI7708SDI_H_
#define SPI7708SDI_H_

/* MODULE SPI7708SDI. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  SPI7708SDI_GetVal (component BitIO)
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
#define SPI7708SDI_GetVal() ( \
    (bool)((getReg8(PTED) & 0x10))     /* Return port data */ \
  )

/*
** ===================================================================
**     Method      :  SPI7708SDI_PutVal (component BitIO)
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
void SPI7708SDI_PutVal(bool Val);

/*
** ===================================================================
**     Method      :  SPI7708SDI_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define SPI7708SDI_ClrVal() ( \
    (void)clrReg8Bits(PTED, 0x10)      /* PTED4=0x00 */ \
  )

/*
** ===================================================================
**     Method      :  SPI7708SDI_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define SPI7708SDI_SetVal() ( \
    (void)setReg8Bits(PTED, 0x10)      /* PTED4=0x01 */ \
  )



/* END SPI7708SDI. */
#endif /* #ifndef __SPI7708SDI_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

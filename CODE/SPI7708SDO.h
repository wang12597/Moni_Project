/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : SPI7708SDO.H
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.21, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/3, 9:17
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Input direction only.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       12            |  PTE5_SDA_MISO
**             ----------------------------------------------------
**
**         Port name                   : PTE
**
**         Bit number (in port)        : 5
**         Bit mask of the port        : $0020
**
**         Initial direction           : Input (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : up
**
**         Port data register          : PTED      [$0008]
**         Port control register       : PTEDD     [$0009]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool SPI7708SDO_GetVal(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef SPI7708SDO_H_
#define SPI7708SDO_H_

/* MODULE SPI7708SDO. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  SPI7708SDO_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This bean is set to work in Input direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define SPI7708SDO_GetVal() ( \
    (bool)((getReg8(PTED) & 0x20))     /* Return port data */ \
  )



/* END SPI7708SDO. */
#endif /* #ifndef __SPI7708SDO_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : MYEEPROM.H
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : IntEEPROM
**     Version   : Component 02.190, Driver 01.06, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/6, 11:18
**     Abstract  :
**         This device "IntEEPROM" implements internal EEPROM
**     Settings  :
**         Initialization:
**              Wait in methods        : Enabled
**              EEPROM clock           : 182 kHz
**
**     Contents  :
**         SetByte - byte MYEEPROM_SetByte(MYEEPROM_TAddress Addr, byte Data);
**         GetByte - byte MYEEPROM_GetByte(MYEEPROM_TAddress Addr, byte *Data);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __MYEEPROM
#define __MYEEPROM

/* MODULE MYEEPROM. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "Cpu.h"

/* Public constants */
#define MYEEPROM_AREA_START            0x1400U /* Start address of the selected EEPROM address range */
#define MYEEPROM_AREA_SIZE             0x0400U /* Size of the selected EEPROM address range */
#define MYEEPROM_AREA_END              0x17FFU /* Last address of the selected EEPROM address range */
#define MYEEPROM_AREA_SECTOR_SIZE      0x08U /* EEPROM area sector size: minimal erasable unit (in bytes). */
/* Deprecated constants */
#define EEPROM                         MYEEPROM_AREA_START
#define MYEEPROM_EEPROMSize            0x0400U /* Size of on-chip EEPROM */
/* TRUE if the bean setting allows clear bits of already programmed flash memory location without destruction of the value in surrounding addresses by sector erase. */
#define MYEEPROM_ALLOW_CLEAR           (TRUE)
/* Size of programming phrase, i.e. number of bytes that must be programmed at once */
#define MYEEPROM_PROGRAMMING_PHRASE    (0x01U)


#ifndef __BWUserType_MYEEPROM_TAddress
#define __BWUserType_MYEEPROM_TAddress
  typedef word MYEEPROM_TAddress;      /* User type for address to the EEPROM */
#endif

byte MYEEPROM_SetByte(MYEEPROM_TAddress Addr, byte Data);
/*
** ===================================================================
**     Method      :  MYEEPROM_SetByte (component IntEEPROM)
**
**     Description :
**         This method writes a given byte to a specified address in
**         EEPROM. The method also sets address pointer for <SetActByte>
**         and <GetActByte> methods (applicable only if these methods
**         are enabled). The pointer is set to address passed as the
**         parameter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - Address to EEPROM
**         Data            - Data to write
**     Returns     :
**         ---             - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_SPEED - the bean does not work in the
**                           active speed mode 
**                           - ERR_BUSY - device is busy 
**                           - ERR_VALUE - verification of written data
**                           failed (read value does not match with
**                           written value) 
**                           - ERR_NOTAVAIL - other device-specific
**                           error 
**                           - ERR_RANGE - parameter Addr is out of range
** ===================================================================
*/

byte MYEEPROM_GetByte(MYEEPROM_TAddress Addr, byte *Data);
/*
** ===================================================================
**     Method      :  MYEEPROM_GetByte (component IntEEPROM)
**
**     Description :
**         This method reads a byte from a specified EEPROM address.
**         The method also sets address pointer for <SetActByte> and
**         <GetActByte> methods (applicable only if these methods are
**         enabled). The pointer is set to address passed as the
**         parameter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - EEPROM Address
**       * Data            - A pointer to the returned 8-bit data
**     Returns     :
**         ---             - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_BUSY - device is busy 
**                           - ERR_RANGE - parameter Addr is out of range
** ===================================================================
*/

void MYEEPROM_Init(void);
/*
** ===================================================================
**     Method      :  MYEEPROM_Init (component IntEEPROM)
**
**     Description :
**         Initializes the associated peripheral(s) and the bean internal 
**         variables. The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



/* END MYEEPROM. */

#endif
/* ifndef __MYEEPROM */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

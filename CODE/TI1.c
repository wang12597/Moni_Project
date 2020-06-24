/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI1.C
**     Project   : Dilute_Test
**     Processor : MC9S08DZ60MLC
**     Component : TimerInt
**     Version   : Component 02.157, Driver 01.18, CPU db: 3.00.019
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2020/6/1, 19:56
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : RTC (8-bit)
**         Compare name                : RTCmod
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 31250 Hz
**           Initial period/frequency
**             Xtal ticks              : 7936
**             microseconds            : 992
**             milliseconds            : 1
**             seconds (real)          : 0.000992
**             Hz                      : 1008
**             kHz                     : 1
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : RTCCNT    [$006D]
**              Mode                   : RTCSC     [$006C]
**              Run                    : RTCSC     [$006C]
**              Prescaler              : RTCSC     [$006C]
**
**         Compare registers
**              Compare                : RTCMOD    [$006E]
**
**         Flip-flop registers
**     Contents  :
**         Enable       - byte TI1_Enable(void);
**         Disable      - byte TI1_Disable(void);
**         EnableEvent  - byte TI1_EnableEvent(void);
**         DisableEvent - byte TI1_DisableEvent(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE TI1. */

#include "Events.h"
#include "PE_Error.h"
#include "TI1.h"
#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */
#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter X declared in function F but not referenced */

static bool EnUser;                    /* Enable device by user */
bool TI1_EnEvent;                      /* Enable/Disable events */
/*** Internal macros and method prototypes ***/

/*
** ===================================================================
**     Method      :  SetCV (component TimerInt)
**
**     Description :
**         The method computes and sets compare eventually modulo value 
**         for time measuring.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define TI1_SetCV(_Val) \
  (RTCMOD = (byte)(_Val))

/*
** ===================================================================
**     Method      :  HWEnDi (component TimerInt)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void);


/*** End of internal method prototypes ***/

/*
** ===================================================================
**     Method      :  HWEnDi (component TimerInt)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {
    /* RTCSC: RTIF=1,RTCLKS=2,RTIE=1,RTCPS=8 */
    setReg8(RTCSC, 0xD8);              /* Run RTC - select clock source; set frequency and enable interrupt */ 
  } else {
    /* RTCSC: RTCPS=0 */
    clrReg8Bits(RTCSC, 0x0F);          /* Stop counter (RTCPS[0:3] = 000) */ 
  }
}

/*
** ===================================================================
**     Method      :  TI1_Enable (component TimerInt)
**
**     Description :
**         This method enables the component - it starts the timer.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TI1_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_Disable (component TimerInt)
**
**     Description :
**         This method disables the component - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TI1_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_EnableEvent (component TimerInt)
**
**     Description :
**         This method enables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte TI1_EnableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  TI1_DisableEvent (component TimerInt)
**
**     Description :
**         This method disables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte TI1_DisableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  TI1_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TI1_Init(void)
{
  /* RTCSC: RTIF=0,RTCLKS=0,RTIE=0,RTCPS=0 */
  setReg8(RTCSC, 0x00);                /* Stop HW */ 
  EnUser = TRUE;                       /* Enable device */
  TI1_EnEvent = TRUE;                  /* Enable event */
  TI1_SetCV(0x1E);                     /* Inicialize appropriate value to the compare/modulo/reload register */
  RTCMOD = RTCMOD;                     /* Reset HW counter */
  HWEnDi();
}


/*
** ===================================================================
**     Method      :  TI1_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(TI1_Interrupt)
{
  /* RTCSC: RTIF=1 */
  setReg8Bits(RTCSC, 0x80);            /* Reset real-time counter request flag */ 
  if (TI1_EnEvent) {                   /* Are the events enabled? */
    TI1_OnInterrupt();                 /* Invoke user event */
  }
}



/* END TI1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.46]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

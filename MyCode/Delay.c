/** ###################################################################
**     模块名称  : Delay.c
**     工程名称  : AN1000_Analog
**     模块功能  : 延时文件
**     开发平台  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     创建日期  : 2013-4-22, 08:00
**     版本信息  : Ver1.00.00
**     作    者  : 刘全义
**     
**     修改信息  : 无
**
** ###################################################################*/
#include "includes.h"

extern volatile stSystemState g_stSystemState;
/******************************************************
函数名称：void DelayNus(unsigned int n)
函数功能：延时Nus
入口参数：n
出口参数：
说    明：总线频率16M 外部8M晶振   100us = 100us 1000us = 960us
*******************************************************/
void DelayNus(uint16 u16Delay)
{
    uint16 l_u16Loop = 0;
    uint8  l_u8LoopB = 0;
    
    for(l_u16Loop = 0; l_u16Loop < u16Delay; l_u16Loop = l_u16Loop + 5)
    {
        for(l_u8LoopB = 0; l_u8LoopB < 3; l_u8LoopB++)
        {          
          asm(NOP);
        }
    }
}

extern volatile unsigned int gDelayCounter;

/******************************************************
函数名称：void DelayNms(unsigned int n)
函数功能：延时Nms
入口参数：n
出口参数：
说    明：
*******************************************************/
void DelayNms(uint32 n)  
{
    uint32 l_u32Loop = 0;
    uint16 l_u16LoopB = 0;
    
    for(l_u32Loop = 0; l_u32Loop < n; l_u32Loop++)
    {
        for(l_u16LoopB = 0; l_u16LoopB < 580; l_u16LoopB++)
        {          
          asm(NOP);
          asm(NOP);
          asm(NOP);
          asm(NOP);
          asm(NOP);
        }
    }
}

extern volatile uint32 g_u32DelayTimer;
void SetDelayNms(uint32 u32n)
{
    __DI();
    g_u32DelayTimer = u32n;
    g_stSystemState.u8DelayEnd = 1;
    __EI();
}
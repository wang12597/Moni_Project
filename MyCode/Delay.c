/** ###################################################################
**     ģ������  : Delay.c
**     ��������  : AN1000_Analog
**     ģ�鹦��  : ��ʱ�ļ�
**     ����ƽ̨  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     ��������  : 2013-4-22, 08:00
**     �汾��Ϣ  : Ver1.00.00
**     ��    ��  : ��ȫ��
**     
**     �޸���Ϣ  : ��
**
** ###################################################################*/
#include "includes.h"

extern volatile stSystemState g_stSystemState;
/******************************************************
�������ƣ�void DelayNus(unsigned int n)
�������ܣ���ʱNus
��ڲ�����n
���ڲ�����
˵    ��������Ƶ��16M �ⲿ8M����   100us = 100us 1000us = 960us
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
�������ƣ�void DelayNms(unsigned int n)
�������ܣ���ʱNms
��ڲ�����n
���ڲ�����
˵    ����
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
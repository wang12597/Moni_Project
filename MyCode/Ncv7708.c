/** ###################################################################
**     模块名称  : Ncv7708.c
**     工程名称  : AN1000_Driver
**     模块功能  : Ncv7708电磁阀驱动函数
**     开发平台  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     创建日期  : 2013-4-23, 08:00
**     版本信息  : Ver1.00.00
**     作    者  : 刘全义
**     
**     修改信息  : 无
**
** ###################################################################*/
#include "includes.h"


extern volatile uint8 g_u8SpiRecOk;
extern volatile stSystemState g_stSystemState;
extern stMoni g_stMoni;
/*
**============================================================
**  函数名  ： SPI7708_Enable
**  
**  功能描述： NCV7708使能操作
**
**  参数    ：
**
**   [参数1]:  无
**
**  返回值  ： 无
**
**============================================================
*/
void NCV7708_Enable(void)
{
   SPI7708EN_PutVal(1);  
}

/*
**============================================================
**  函数名  ： NCV7708_Disable
**  
**  功能描述： NCV7708禁止操作
**
**  参数    ：
**
**   [参数1]:  无
**
**  返回值  ： 无
**
**============================================================
*/
void NCV7708_Disable(void)
{
   SPI7708EN_PutVal(0);    
}

/*
**============================================================
**  函数名  ： NCV7708_Send16Bits
**  
**  功能描述： NCV7708写操作
**
**  参数    ：
**
**   [参数1]:  写16位数据
**
**  返回值  ： 返回16位数据
**
**============================================================
*/
uint16 NCV7708_Send16Bits(uint16 d)
{
	uint8 i;
	uint16 l_u16Return= 0;
	for ( i = 0; i < 16; i ++ ) {
		SPI7708CLK_PutVal(0);
		DelayNus(20);
		if ( d & 0x01 ) SPI7708SDI_PutVal(1);
		else SPI7708SDI_PutVal(0);
		d >>= 1;  /* 数据位是高位在前 */
		SPI7708CLK_PutVal(1); /* CH376在时钟上升沿采样输入 */
		DelayNus(20);
	    l_u16Return >>= 1;	
		if(SPI7708SDO_GetVal()) 
		{
			l_u16Return |= 0x8000;
		}	
				
	}
    SPI7708CLK_PutVal(0);
	DelayNus(20);
	return l_u16Return;
}

/*
**============================================================
**  函数名  : NCV7708_Write16Bits
**  
**  功能描述: SPI模拟NCV7708发送16位数据
**
**  
**  参数    : 
**
**   [参数1]:uint16 u16Value
**  
**  返回值  : SPI返回值 
**
**============================================================
*/
uint16 NCV7708_Write16Bits(uint16 u16Value)
{
	uint16 l_u16ValveReturnA = 0;
	uint16 l_u16ValveReturnB = 0;
  NCV7708_Enable();              //使能
	DelayNus(10);
  SPI7708CS_PutVal(0);           //CS = 0;
	DelayNus(100);
	l_u16ValveReturnB = NCV7708_Send16Bits(u16Value);    //返回值 合并
	DelayNus(20);
  SPI7708CS_PutVal(1);            //CS = 1;
  	

	if(
		(u16Value & (~0xE001)) == (l_u16ValveReturnB & (~0xE001))        //读取的阀状态正确
		&& ((l_u16ValveReturnB & 0xE001) == 0x0000))                     //读取的阀控制系统 无超负载 空载等信息
	{
		return 1;                                                        //阀操作执行成功
		
	}
	else  
	{
		return 0;	                                                    //阀操作执行失败
	}

}

/*
**============================================================
**  函数名  : SetValve
**  
**  功能描述: 开关电磁阀
**
**  
**  参数    : 
**
**   [参数1]:uint16 u16ValueOn
**  
**   [参数2]:uint16 u16ValueOff
** 
**  返回值  : 无
**
**============================================================
*/
extern volatile uint8 g_u8MotorStopFlag;
uint16 s_u16ValveState = 0;
void SetValve(uint16 u16ValveOn, uint16 u16ValveOff)
{
    
    uint8  l_u8ErrTimer = 0;

    s_u16ValveState = s_u16ValveState | u16ValveOn;      //记录 所有开阀的信息
    s_u16ValveState = s_u16ValveState & (~u16ValveOff);  //记录 所有关阀的信息

    
    while( (0 == NCV7708_Write16Bits(s_u16ValveState)) && (l_u8ErrTimer < 10))    //当16位阀发送和接收的状态 连续10次 不一致
    {                                                                              //或10次之内 阀发送 == 接收时 跳出
        l_u8ErrTimer++;
        DelayNus(800);
    }
                                                                                                                                              

    if(l_u8ErrTimer > 5)                                 //若错误计数器超过5次 认为阀操作失败
    {
      	s_u16ValveState = 0;
        g_stSystemState.u16ErrorMessage = VALVE_ERR_RETURN;   
        //SendError();
        return;       	
    }
    else
    {
      	g_stSystemState.u16ErrorMessage = 0;        //执行正常 清除错误标志
      	if(u16ValveOn == RELAY)g_stMoni.u16RelayState = OPEN;
      	if(u16ValveOff == RELAY)g_stMoni.u16RelayState = OFF;
    }
    
}
     
void ValveTest(void)
{
    SetValve(SV1,SV12|SRR|OCD|ULD|OVLO);
    DelayNms(3000);        
    SetValve(SV2,SV1);
    DelayNms(3000);
    SetValve(SV3,SV2);
    DelayNms(3000); 
    SetValve(SV4,SV3);
    DelayNms(3000); 
    SetValve(SV5,SV4);
    DelayNms(3000); 
    SetValve(SV6,SV5);
    DelayNms(3000); 
    SetValve(SV7,SV6);
    DelayNms(3000); 
    SetValve(SV8,SV7);
    DelayNms(3000); 
    SetValve(SV9,SV8);
    DelayNms(3000);
    SetValve(SV10,SV9);
    DelayNms(3000);
    SetValve(SV11,SV10);
    DelayNms(3000);
    SetValve(SV12,SV11);
    DelayNms(3000);  
    SetValve(0,SV12);
    SetValve(SRR|OCD|ULD|OVLO,0);  
}


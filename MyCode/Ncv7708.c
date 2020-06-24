/** ###################################################################
**     ģ������  : Ncv7708.c
**     ��������  : AN1000_Driver
**     ģ�鹦��  : Ncv7708��ŷ���������
**     ����ƽ̨  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     ��������  : 2013-4-23, 08:00
**     �汾��Ϣ  : Ver1.00.00
**     ��    ��  : ��ȫ��
**     
**     �޸���Ϣ  : ��
**
** ###################################################################*/
#include "includes.h"


extern volatile uint8 g_u8SpiRecOk;
extern volatile stSystemState g_stSystemState;
extern stMoni g_stMoni;
/*
**============================================================
**  ������  �� SPI7708_Enable
**  
**  ���������� NCV7708ʹ�ܲ���
**
**  ����    ��
**
**   [����1]:  ��
**
**  ����ֵ  �� ��
**
**============================================================
*/
void NCV7708_Enable(void)
{
   SPI7708EN_PutVal(1);  
}

/*
**============================================================
**  ������  �� NCV7708_Disable
**  
**  ���������� NCV7708��ֹ����
**
**  ����    ��
**
**   [����1]:  ��
**
**  ����ֵ  �� ��
**
**============================================================
*/
void NCV7708_Disable(void)
{
   SPI7708EN_PutVal(0);    
}

/*
**============================================================
**  ������  �� NCV7708_Send16Bits
**  
**  ���������� NCV7708д����
**
**  ����    ��
**
**   [����1]:  д16λ����
**
**  ����ֵ  �� ����16λ����
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
		d >>= 1;  /* ����λ�Ǹ�λ��ǰ */
		SPI7708CLK_PutVal(1); /* CH376��ʱ�������ز������� */
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
**  ������  : NCV7708_Write16Bits
**  
**  ��������: SPIģ��NCV7708����16λ����
**
**  
**  ����    : 
**
**   [����1]:uint16 u16Value
**  
**  ����ֵ  : SPI����ֵ 
**
**============================================================
*/
uint16 NCV7708_Write16Bits(uint16 u16Value)
{
	uint16 l_u16ValveReturnA = 0;
	uint16 l_u16ValveReturnB = 0;
  NCV7708_Enable();              //ʹ��
	DelayNus(10);
  SPI7708CS_PutVal(0);           //CS = 0;
	DelayNus(100);
	l_u16ValveReturnB = NCV7708_Send16Bits(u16Value);    //����ֵ �ϲ�
	DelayNus(20);
  SPI7708CS_PutVal(1);            //CS = 1;
  	

	if(
		(u16Value & (~0xE001)) == (l_u16ValveReturnB & (~0xE001))        //��ȡ�ķ�״̬��ȷ
		&& ((l_u16ValveReturnB & 0xE001) == 0x0000))                     //��ȡ�ķ�����ϵͳ �޳����� ���ص���Ϣ
	{
		return 1;                                                        //������ִ�гɹ�
		
	}
	else  
	{
		return 0;	                                                    //������ִ��ʧ��
	}

}

/*
**============================================================
**  ������  : SetValve
**  
**  ��������: ���ص�ŷ�
**
**  
**  ����    : 
**
**   [����1]:uint16 u16ValueOn
**  
**   [����2]:uint16 u16ValueOff
** 
**  ����ֵ  : ��
**
**============================================================
*/
extern volatile uint8 g_u8MotorStopFlag;
uint16 s_u16ValveState = 0;
void SetValve(uint16 u16ValveOn, uint16 u16ValveOff)
{
    
    uint8  l_u8ErrTimer = 0;

    s_u16ValveState = s_u16ValveState | u16ValveOn;      //��¼ ���п�������Ϣ
    s_u16ValveState = s_u16ValveState & (~u16ValveOff);  //��¼ ���йط�����Ϣ

    
    while( (0 == NCV7708_Write16Bits(s_u16ValveState)) && (l_u8ErrTimer < 10))    //��16λ�����ͺͽ��յ�״̬ ����10�� ��һ��
    {                                                                              //��10��֮�� ������ == ����ʱ ����
        l_u8ErrTimer++;
        DelayNus(800);
    }
                                                                                                                                              

    if(l_u8ErrTimer > 5)                                 //���������������5�� ��Ϊ������ʧ��
    {
      	s_u16ValveState = 0;
        g_stSystemState.u16ErrorMessage = VALVE_ERR_RETURN;   
        //SendError();
        return;       	
    }
    else
    {
      	g_stSystemState.u16ErrorMessage = 0;        //ִ������ ��������־
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


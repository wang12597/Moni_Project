/** ###################################################################
**     ģ������  : MyCan.c
**     ��������  : AN1000_Driver
**     ģ�鹦��  : Can��������
**     ����ƽ̨  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     ��������  : 2013-4-29, 17:00
**     �汾��Ϣ  : Ver1.00.00
**     ��    ��  : ��ȫ��
**     
**     �޸���Ϣ  : ��
**
** ###################################################################*/
#include "includes.h"


extern stSystemState g_stSystemState;
extern volatile uint8 UartTxSendOkFlag;
extern volatile uint8 g_u8RxdNum;   //�����ֽڼ�����
extern volatile uint8 g_u8RxdBuff[64];  //�����ֽڻ�����
volatile uint8 g_u8485FrameFlag = 0;
volatile stFactor g_stFactor;
extern stMoni g_stMoni;
void UartAction(unsigned char *buf, unsigned char len)
{
    static uint16 l_u16RegAddr = 0;
    uint16 l_u16ReadLength = 0;
    uint16 l_u16MechCmd;
    static uint16 l_u16TempData = 0;
    unShortToFloat l_unShortToFloat;
    unCharToShort l_unCharToShort;
    unsigned int  crc;
    unsigned char crch, crcl;
    unsigned char buf_Send[30] = {0};
    uint8 i = 0;
    
    if (buf[0] == 3) //�����еı�����ַ�趨Ϊ0x03��
    {                     
         //��ַ���ʱ���ٶԱ�֡���ݽ���У��
        crc = GetCRC16(buf, len-2);  //����CRCУ��ֵ
        crch = crc >> 8;
        crcl = crc & 0xFF;
        if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
        {
            return;   //��CRCУ�鲻��ʱֱ���˳�
        }
        buf_Send[0] = buf[0];
        //��ַ��У���־�����󣬽��������룬ִ����ز���
        switch (buf[1])
        {
          case 0x03:  //��ȡһ���������ļĴ���
            buf_Send[1] = buf[1];
            l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3];
            l_u16ReadLength = ((uint16)buf[4] << 8) | buf[5];
            buf_Send[2] = l_u16ReadLength*2;  //��ȡ���ݵ��ֽ�����Ϊ�Ĵ�����*2
            len = 3;          //֡ǰ�����е�ַ�������롢�ֽ�����3���ֽ�
            switch(l_u16RegAddr)
            {
              case RELAY_STATE:              
                  l_u16TempData = g_stMoni.u16RelayState;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //�Ĵ������ֽڲ�0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //�Ĵ������ֽ�
                  }
              break;
              case RELAY_WAY_STATE:
                  l_u16TempData = g_stFactor.u16RelayCtrlFlag;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //�Ĵ������ֽڲ�0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //�Ĵ������ֽ�
                  }
              break;
              default:
                  l_u16TempData = 0x55AA;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //�Ĵ������ֽڲ�0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //�Ĵ������ֽ�
                  }
              break;
            }
            crc = GetCRC16(buf_Send, len); //���㷵��֡��CRCУ��ֵ
            buf_Send[len++] = crc >> 8;    //CRC���ֽ�
            buf_Send[len++] = crc & 0xFF;  //CRC���ֽ�
            MYUART_485Send(buf_Send, len);      //���ͷ���֡
          break;
          case 0x10:
            for(i=1;i<6;i++) {
              buf_Send[i] = buf[i]; 
            }
            len = 6;
            crc = GetCRC16(buf_Send, len); //���㷵��֡��CRCУ��ֵ
            buf_Send[len++] = crc >> 8;    //CRC���ֽ�
            buf_Send[len++] = crc & 0xFF;  //CRC���ֽ� 
            MYUART_485Send(buf_Send, len);      //���ͷ����  
            l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3];   
            switch(l_u16RegAddr)
            {
              case SET_FACTOR:
                  g_stFactor.u16DOLimitH = ((uint16)buf[7] << 8) | buf[8]; 
                  g_stFactor.u16DOLimitL = ((uint16)buf[9] << 8) | buf[10];
                  g_stFactor.u16TempLimitH = ((uint16)buf[11] << 8) | buf[12];
                  g_stFactor.u16TempLimitL = ((uint16)buf[11] << 8) | buf[12];
                  SaveSetValue();
              break;
              case MANUA_CONTROL:
                  l_u16MechCmd = ((uint16)buf[7] << 8) | buf[8];
                  RelayCtrl(l_u16MechCmd);
              break;
              case REAL_VALUE_W:
                  l_unShortToFloat.ShortType[1] = ((uint16) buf[7] << 8) | buf[8];
                  l_unShortToFloat.ShortType[0] = ((uint16) buf[9] << 8) | buf[10];
                  g_stMoni.fRealDOValue = l_unShortToFloat.FloatType;
                  l_unShortToFloat.ShortType[1] = ((uint16) buf[11] << 8) | buf[12];
                  l_unShortToFloat.ShortType[0] = ((uint16) buf[13] << 8) | buf[14];
                  g_stMoni.fRealTemper = l_unShortToFloat.FloatType;
              break;
              case RELAY_CONTROL_WAY:
                  g_stFactor.u16RelayCtrlFlag = ((uint16)buf[7] << 8) | buf[8];
                  l_unCharToShort.ShortType = g_stFactor.u16RelayCtrlFlag;
                  MYEEPROM_SetByte(EEP_ADDR_RELAY_CTRL,l_unCharToShort.CharType[0]);
                  MYEEPROM_SetByte(EEP_ADDR_RELAY_CTRL + 1,l_unCharToShort.CharType[1]);
              break;
              default:
              break; 
            }
            //MYUART_485Send(buf_Send, len);      //���ͷ���֡
          break;
          default:  //������֧�ֵĹ�����
            buf_Send[1] |= 0x80;  //���������λ��1
            buf_Send[2] = 0x01;   //�����쳣��Ϊ01-��Ч����
            len = 3;
            crc = GetCRC16(buf_Send, len); //���㷵��֡��CRCУ��ֵ
            buf_Send[len++] = crc >> 8;    //CRC���ֽ�
            buf_Send[len++] = crc & 0xFF;  //CRC���ֽ�
            MYUART_485Send(buf_Send, len);      //���ͷ���֡
          break;
        }
    } 
    else if(buf[0] == 1)
    {
        if(buf[2] == 0)      //DTU������
        {
           if(buf[1] == 0x03) 
           {
              crc = GetCRC16(buf, len-2);  //����CRCУ��ֵ
              crch = crc >> 8;
              crcl = crc & 0xFF;
              if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
              {
                  return;   //��CRCУ�鲻��ʱֱ���˳�
              }
              l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3]; 
           }
        } else if(buf[2] == 2)//�Ǳ���
        {
            crc = GetCRC16(buf, len-2);  //����CRCУ��ֵ
            crch = crc >> 8;
            crcl = crc & 0xFF;
            if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
            {
                return;   //��CRCУ�鲻��ʱֱ���˳�
            }
            if(l_u16RegAddr == 0)     //��ȡ�¶�
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealTemper =  (float)l_u16TempData/10.0;  
            }
            if(l_u16RegAddr == 1) //������ֵ
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealDOValue =  (float)l_u16TempData/100.0;
            } 
        }
    }
}
/* ���������������������֡�Ľ��գ����ȹ��ܺ�����������ѭ���е��� */
void  MYUART_485Driver(void)
{
    unsigned char len;
    unsigned char buf[64];
 
    if (g_u8485FrameFlag) //�������ʱ����ȡ���������
    {
        g_u8485FrameFlag = 0;
        len = MYUART_485Rec(buf, sizeof(buf)-2); //�����յ��������ȡ����������
        UartAction(buf, len);  //��������֡�����ö���ִ�к���
    }
}

void  MYUART_485RxMoni(void) {
    static unsigned char cntbkp = 0;
    static unsigned char idletmr = 0;
 
    if (g_u8RxdNum > 0)  //���ռ�����������ʱ��������߿���ʱ��
    {
        if (cntbkp != g_u8RxdNum)  //���ռ������ı䣬���ս��յ�����ʱ��������м�ʱ
        {
            cntbkp = g_u8RxdNum;
            idletmr = 0;
        }
        else                     //���ռ�����δ�ı䣬�����߿���ʱ���ۻ�����ʱ��
        {
            if (idletmr < 30)  //���м�ʱС��30msʱ�������ۼ�
            {
                idletmr++;
                if (idletmr >= 30)  //����ʱ��ﵽ30msʱ�����ж�Ϊһ֡�������
                {
                    g_u8485FrameFlag = 1;  //����֡������ɱ�־
                }
            }
        }
    }
    else
    {
        cntbkp = 0;
    }
}
uint8 MYUART_485Rec(unsigned char *buf, unsigned char len) {
    uint8 l_u8Loop = 0;
    if(len> g_u8RxdNum) {
      len = g_u8RxdNum; 
    }
    
    for(l_u8Loop = 0; l_u8Loop < len; l_u8Loop++) 
    {
      buf[l_u8Loop] = g_u8RxdBuff[l_u8Loop]; 
    }
    
    g_u8RxdNum = 0;
    return len;
}
void  MYUART_485Send(unsigned char *buf, unsigned char len) 
{
    uint8 l_u8SendLen  = 0;
    
    RS485W_EN_PutVal(1);
    Uart_SendBlock(buf,len,&l_u8SendLen);   
}
/******************************************************
�������ƣ�TERMIO_PutChar
�������ܣ�PutChar���� printf�ĵײ��ļ�
��ڲ�����chr
���ڲ�������
˵    ������
*******************************************************/
void TERMIO_PutChar(uint8 chr) //��ӡ printf
{ 
	MYUART_SendChar(chr);
}
void SaveSetValue(void)
{
   unCharToShort l_unCharToShort;
   
   l_unCharToShort.ShortType = g_stFactor.u16DOLimitH;
   MYEEPROM_SetByte(EEP_ADDR_DOLIMITH,l_unCharToShort.CharType[0]);
   MYEEPROM_SetByte(EEP_ADDR_DOLIMITH + 1,l_unCharToShort.CharType[1]);
   
   l_unCharToShort.ShortType = g_stFactor.u16DOLimitL;
   MYEEPROM_SetByte(EEP_ADDR_DOLIMITL,l_unCharToShort.CharType[0]);
   MYEEPROM_SetByte(EEP_ADDR_DOLIMITL + 1,l_unCharToShort.CharType[1]);
   
   l_unCharToShort.ShortType = g_stFactor.u16TempLimitH;
   MYEEPROM_SetByte(EEP_ADDR_TEMPLIMITH,l_unCharToShort.CharType[0]);
   MYEEPROM_SetByte(EEP_ADDR_TEMPLIMITH + 1,l_unCharToShort.CharType[1]);
}
void SystemInit(void)
{
   unCharToShort l_unCharToShort;
   
   MYEEPROM_GetByte(EEP_ADDR_DOLIMITH,&l_unCharToShort.CharType[0]);
   MYEEPROM_GetByte(EEP_ADDR_DOLIMITH + 1,&l_unCharToShort.CharType[1]);
   g_stFactor.u16DOLimitH = l_unCharToShort.ShortType;
   
   MYEEPROM_GetByte(EEP_ADDR_DOLIMITL,&l_unCharToShort.CharType[0]);
   MYEEPROM_GetByte(EEP_ADDR_DOLIMITL + 1,&l_unCharToShort.CharType[1]);
   g_stFactor.u16DOLimitL = l_unCharToShort.ShortType;
   
   MYEEPROM_GetByte(EEP_ADDR_TEMPLIMITH,&l_unCharToShort.CharType[0]);
   MYEEPROM_GetByte(EEP_ADDR_TEMPLIMITH + 1,&l_unCharToShort.CharType[1]);
   g_stFactor.u16TempLimitH = l_unCharToShort.ShortType;
   
   MYEEPROM_GetByte(EEP_ADDR_RELAY_CTRL,&l_unCharToShort.CharType[0]);
   MYEEPROM_GetByte(EEP_ADDR_RELAY_CTRL + 1,&l_unCharToShort.CharType[1]);
   g_stFactor.u16RelayCtrlFlag = l_unCharToShort.ShortType;
   
   g_stMoni.u16RelayState = OFF;
}
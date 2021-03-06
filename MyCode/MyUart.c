/** ###################################################################
**     模块名称  : MyCan.c
**     工程名称  : AN1000_Driver
**     模块功能  : Can驱动函数
**     开发平台  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     创建日期  : 2013-4-29, 17:00
**     版本信息  : Ver1.00.00
**     作    者  : 刘全义
**     
**     修改信息  : 无
**
** ###################################################################*/
#include "includes.h"


extern stSystemState g_stSystemState;
extern volatile uint8 UartTxSendOkFlag;
extern volatile uint8 g_u8RxdNum;   //接收字节计数器
extern volatile uint8 g_u8RxdBuff[64];  //接收字节缓冲区
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
    
    if (buf[0] == 3) //本例中的本机地址设定为0x03，
    {                     
         //地址相符时，再对本帧数据进行校验
        crc = GetCRC16(buf, len-2);  //计算CRC校验值
        crch = crc >> 8;
        crcl = crc & 0xFF;
        if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
        {
            return;   //如CRC校验不符时直接退出
        }
        buf_Send[0] = buf[0];
        //地址和校验字均相符后，解析功能码，执行相关操作
        switch (buf[1])
        {
          case 0x03:  //读取一个或连续的寄存器
            buf_Send[1] = buf[1];
            l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3];
            l_u16ReadLength = ((uint16)buf[4] << 8) | buf[5];
            buf_Send[2] = l_u16ReadLength*2;  //读取数据的字节数，为寄存器数*2
            len = 3;          //帧前部已有地址、功能码、字节数共3个字节
            switch(l_u16RegAddr)
            {
              case RELAY_STATE:              
                  l_u16TempData = g_stMoni.u16RelayState;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //寄存器高字节补0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //寄存器低字节
                  }
              break;
              case RELAY_WAY_STATE:
                  l_u16TempData = g_stFactor.u16RelayCtrlFlag;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //寄存器高字节补0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //寄存器低字节
                  }
              break;
              default:
                  l_u16TempData = 0x55AA;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //寄存器高字节补0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //寄存器低字节
                  }
              break;
            }
            crc = GetCRC16(buf_Send, len); //计算返回帧的CRC校验值
            buf_Send[len++] = crc >> 8;    //CRC高字节
            buf_Send[len++] = crc & 0xFF;  //CRC低字节
            MYUART_485Send(buf_Send, len);      //发送返回帧
          break;
          case 0x10:
            for(i=1;i<6;i++) {
              buf_Send[i] = buf[i]; 
            }
            len = 6;
            crc = GetCRC16(buf_Send, len); //计算返回帧的CRC校验值
            buf_Send[len++] = crc >> 8;    //CRC高字节
            buf_Send[len++] = crc & 0xFF;  //CRC低字节 
            MYUART_485Send(buf_Send, len);      //发送返回�  
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
            //MYUART_485Send(buf_Send, len);      //发送返回帧
          break;
          default:  //其它不支持的功能码
            buf_Send[1] |= 0x80;  //功能码最高位置1
            buf_Send[2] = 0x01;   //设置异常码为01-无效功能
            len = 3;
            crc = GetCRC16(buf_Send, len); //计算返回帧的CRC校验值
            buf_Send[len++] = crc >> 8;    //CRC高字节
            buf_Send[len++] = crc & 0xFF;  //CRC低字节
            MYUART_485Send(buf_Send, len);      //发送返回帧
          break;
        }
    } 
    else if(buf[0] == 1)
    {
        if(buf[2] == 0)      //DTU发命令
        {
           if(buf[1] == 0x03) 
           {
              crc = GetCRC16(buf, len-2);  //计算CRC校验值
              crch = crc >> 8;
              crcl = crc & 0xFF;
              if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
              {
                  return;   //如CRC校验不符时直接退出
              }
              l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3]; 
           }
        } else if(buf[2] == 2)//仪表返回
        {
            crc = GetCRC16(buf, len-2);  //计算CRC校验值
            crch = crc >> 8;
            crcl = crc & 0xFF;
            if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
            {
                return;   //如CRC校验不符时直接退出
            }
            if(l_u16RegAddr == 0)     //读取温度
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealTemper =  (float)l_u16TempData/10.0;  
            }
            if(l_u16RegAddr == 1) //读溶氧值
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealDOValue =  (float)l_u16TempData/100.0;
            } 
        }
    }
}
/* 串口驱动函数，监测数据帧的接收，调度功能函数，需在主循环中调用 */
void  MYUART_485Driver(void)
{
    unsigned char len;
    unsigned char buf[64];
 
    if (g_u8485FrameFlag) //有命令到达时，读取处理该命令
    {
        g_u8485FrameFlag = 0;
        len = MYUART_485Rec(buf, sizeof(buf)-2); //将接收到的命令读取到缓冲区中
        UartAction(buf, len);  //传递数据帧，调用动作执行函数
    }
}

void  MYUART_485RxMoni(void) {
    static unsigned char cntbkp = 0;
    static unsigned char idletmr = 0;
 
    if (g_u8RxdNum > 0)  //接收计数器大于零时，监控总线空闲时间
    {
        if (cntbkp != g_u8RxdNum)  //接收计数器改变，即刚接收到数据时，清零空闲计时
        {
            cntbkp = g_u8RxdNum;
            idletmr = 0;
        }
        else                     //接收计数器未改变，即总线空闲时，累积空闲时间
        {
            if (idletmr < 30)  //空闲计时小于30ms时，持续累加
            {
                idletmr++;
                if (idletmr >= 30)  //空闲时间达到30ms时，即判定为一帧接收完毕
                {
                    g_u8485FrameFlag = 1;  //设置帧接收完成标志
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
函数名称：TERMIO_PutChar
函数功能：PutChar函数 printf的底层文件
入口参数：chr
出口参数：无
说    明：无
*******************************************************/
void TERMIO_PutChar(uint8 chr) //打印 printf
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
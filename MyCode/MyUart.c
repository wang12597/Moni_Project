/** ###################################################################
**     Ä£¿éÃû³Æ  : MyCan.c
**     ¹¤³ÌÃû³Æ  : AN1000_Driver
**     Ä£¿é¹¦ÄÜ  : CanÇı¶¯º¯Êı
**     ¿ª·¢Æ½Ì¨  : MCU : MC9S08DZ60MLC
**                 Freescale CodeWarrior 6.3
**     ´´½¨ÈÕÆÚ  : 2013-4-29, 17:00
**     °æ±¾ĞÅÏ¢  : Ver1.00.00
**     ×÷    Õß  : ÁõÈ«Òå
**     
**     ĞŞ¸ÄĞÅÏ¢  : ÎŞ
**
** ###################################################################*/
#include "includes.h"


extern stSystemState g_stSystemState;
extern volatile uint8 UartTxSendOkFlag;
extern volatile uint8 g_u8RxdNum;   //½ÓÊÕ×Ö½Ú¼ÆÊıÆ÷
extern volatile uint8 g_u8RxdBuff[64];  //½ÓÊÕ×Ö½Ú»º³åÇø
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
    
    if (buf[0] == 3) //±¾ÀıÖĞµÄ±¾»úµØÖ·Éè¶¨Îª0x03£¬
    {                     
         //µØÖ·Ïà·ûÊ±£¬ÔÙ¶Ô±¾Ö¡Êı¾İ½øĞĞĞ£Ñé
        crc = GetCRC16(buf, len-2);  //¼ÆËãCRCĞ£ÑéÖµ
        crch = crc >> 8;
        crcl = crc & 0xFF;
        if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
        {
            return;   //ÈçCRCĞ£Ñé²»·ûÊ±Ö±½ÓÍË³ö
        }
        buf_Send[0] = buf[0];
        //µØÖ·ºÍĞ£Ñé×Ö¾ùÏà·ûºó£¬½âÎö¹¦ÄÜÂë£¬Ö´ĞĞÏà¹Ø²Ù×÷
        switch (buf[1])
        {
          case 0x03:  //¶ÁÈ¡Ò»¸ö»òÁ¬ĞøµÄ¼Ä´æÆ÷
            buf_Send[1] = buf[1];
            l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3];
            l_u16ReadLength = ((uint16)buf[4] << 8) | buf[5];
            buf_Send[2] = l_u16ReadLength*2;  //¶ÁÈ¡Êı¾İµÄ×Ö½ÚÊı£¬Îª¼Ä´æÆ÷Êı*2
            len = 3;          //Ö¡Ç°²¿ÒÑÓĞµØÖ·¡¢¹¦ÄÜÂë¡¢×Ö½ÚÊı¹²3¸ö×Ö½Ú
            switch(l_u16RegAddr)
            {
              case RELAY_STATE:              
                  l_u16TempData = g_stMoni.u16RelayState;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //¼Ä´æÆ÷¸ß×Ö½Ú²¹0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //¼Ä´æÆ÷µÍ×Ö½Ú
                  }
              break;
              case RELAY_WAY_STATE:
                  l_u16TempData = g_stFactor.u16RelayCtrlFlag;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //¼Ä´æÆ÷¸ß×Ö½Ú²¹0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //¼Ä´æÆ÷µÍ×Ö½Ú
                  }
              break;
              default:
                  l_u16TempData = 0x55AA;
                  while (l_u16ReadLength--)
                  {
                      buf_Send[len++] = ((l_u16TempData) >> 8) & 0xFF;            //¼Ä´æÆ÷¸ß×Ö½Ú²¹0
                      buf_Send[len++] = (l_u16TempData) & 0xFF; //¼Ä´æÆ÷µÍ×Ö½Ú
                  }
              break;
            }
            crc = GetCRC16(buf_Send, len); //¼ÆËã·µ»ØÖ¡µÄCRCĞ£ÑéÖµ
            buf_Send[len++] = crc >> 8;    //CRC¸ß×Ö½Ú
            buf_Send[len++] = crc & 0xFF;  //CRCµÍ×Ö½Ú
            MYUART_485Send(buf_Send, len);      //·¢ËÍ·µ»ØÖ¡
          break;
          case 0x10:
            for(i=1;i<6;i++) {
              buf_Send[i] = buf[i]; 
            }
            len = 6;
            crc = GetCRC16(buf_Send, len); //¼ÆËã·µ»ØÖ¡µÄCRCĞ£ÑéÖµ
            buf_Send[len++] = crc >> 8;    //CRC¸ß×Ö½Ú
            buf_Send[len++] = crc & 0xFF;  //CRCµÍ×Ö½Ú 
            MYUART_485Send(buf_Send, len);      //·¢ËÍ·µ»ØÖ  
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
            //MYUART_485Send(buf_Send, len);      //·¢ËÍ·µ»ØÖ¡
          break;
          default:  //ÆäËü²»Ö§³ÖµÄ¹¦ÄÜÂë
            buf_Send[1] |= 0x80;  //¹¦ÄÜÂë×î¸ßÎ»ÖÃ1
            buf_Send[2] = 0x01;   //ÉèÖÃÒì³£ÂëÎª01-ÎŞĞ§¹¦ÄÜ
            len = 3;
            crc = GetCRC16(buf_Send, len); //¼ÆËã·µ»ØÖ¡µÄCRCĞ£ÑéÖµ
            buf_Send[len++] = crc >> 8;    //CRC¸ß×Ö½Ú
            buf_Send[len++] = crc & 0xFF;  //CRCµÍ×Ö½Ú
            MYUART_485Send(buf_Send, len);      //·¢ËÍ·µ»ØÖ¡
          break;
        }
    } 
    else if(buf[0] == 1)
    {
        if(buf[2] == 0)      //DTU·¢ÃüÁî
        {
           if(buf[1] == 0x03) 
           {
              crc = GetCRC16(buf, len-2);  //¼ÆËãCRCĞ£ÑéÖµ
              crch = crc >> 8;
              crcl = crc & 0xFF;
              if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
              {
                  return;   //ÈçCRCĞ£Ñé²»·ûÊ±Ö±½ÓÍË³ö
              }
              l_u16RegAddr = ((uint16)buf[2] << 8) | buf[3]; 
           }
        } else if(buf[2] == 2)//ÒÇ±í·µ»Ø
        {
            crc = GetCRC16(buf, len-2);  //¼ÆËãCRCĞ£ÑéÖµ
            crch = crc >> 8;
            crcl = crc & 0xFF;
            if ((buf[len-2]!=crch) || (buf[len-1]!=crcl))
            {
                return;   //ÈçCRCĞ£Ñé²»·ûÊ±Ö±½ÓÍË³ö
            }
            if(l_u16RegAddr == 0)     //¶ÁÈ¡ÎÂ¶È
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealTemper =  (float)l_u16TempData/10.0;  
            }
            if(l_u16RegAddr == 1) //¶ÁÈÜÑõÖµ
            {
               l_u16TempData = ((uint16)buf[7] << 8) | buf[8];
               g_stMoni.fRealDOValue =  (float)l_u16TempData/100.0;
            } 
        }
    }
}
/* ´®¿ÚÇı¶¯º¯Êı£¬¼à²âÊı¾İÖ¡µÄ½ÓÊÕ£¬µ÷¶È¹¦ÄÜº¯Êı£¬ĞèÔÚÖ÷Ñ­»·ÖĞµ÷ÓÃ */
void  MYUART_485Driver(void)
{
    unsigned char len;
    unsigned char buf[64];
 
    if (g_u8485FrameFlag) //ÓĞÃüÁîµ½´ïÊ±£¬¶ÁÈ¡´¦Àí¸ÃÃüÁî
    {
        g_u8485FrameFlag = 0;
        len = MYUART_485Rec(buf, sizeof(buf)-2); //½«½ÓÊÕµ½µÄÃüÁî¶ÁÈ¡µ½»º³åÇøÖĞ
        UartAction(buf, len);  //´«µİÊı¾İÖ¡£¬µ÷ÓÃ¶¯×÷Ö´ĞĞº¯Êı
    }
}

void  MYUART_485RxMoni(void) {
    static unsigned char cntbkp = 0;
    static unsigned char idletmr = 0;
 
    if (g_u8RxdNum > 0)  //½ÓÊÕ¼ÆÊıÆ÷´óÓÚÁãÊ±£¬¼à¿Ø×ÜÏß¿ÕÏĞÊ±¼ä
    {
        if (cntbkp != g_u8RxdNum)  //½ÓÊÕ¼ÆÊıÆ÷¸Ä±ä£¬¼´¸Õ½ÓÊÕµ½Êı¾İÊ±£¬ÇåÁã¿ÕÏĞ¼ÆÊ±
        {
            cntbkp = g_u8RxdNum;
            idletmr = 0;
        }
        else                     //½ÓÊÕ¼ÆÊıÆ÷Î´¸Ä±ä£¬¼´×ÜÏß¿ÕÏĞÊ±£¬ÀÛ»ı¿ÕÏĞÊ±¼ä
        {
            if (idletmr < 30)  //¿ÕÏĞ¼ÆÊ±Ğ¡ÓÚ30msÊ±£¬³ÖĞøÀÛ¼Ó
            {
                idletmr++;
                if (idletmr >= 30)  //¿ÕÏĞÊ±¼ä´ïµ½30msÊ±£¬¼´ÅĞ¶¨ÎªÒ»Ö¡½ÓÊÕÍê±Ï
                {
                    g_u8485FrameFlag = 1;  //ÉèÖÃÖ¡½ÓÊÕÍê³É±êÖ¾
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
º¯ÊıÃû³Æ£ºTERMIO_PutChar
º¯Êı¹¦ÄÜ£ºPutCharº¯Êı printfµÄµ×²ãÎÄ¼ş
Èë¿Ú²ÎÊı£ºchr
³ö¿Ú²ÎÊı£ºÎŞ
Ëµ    Ã÷£ºÎŞ
*******************************************************/
void TERMIO_PutChar(uint8 chr) //´òÓ¡ printf
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
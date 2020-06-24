#ifndef _MYUART_H
#define _MYUART_H

#define UART_RX_FAIL    0x2005
#define UART_RX_SUCCESS 0x2006
#define ADDR_EEP_PUMPEN 0x1401

#define UART_DATA_SIZE  20
#define CMD_RESET_SYSTEM         155

void TERMIO_PutChar(uint8 chr);
void  MYUART_485RxMoni(void);
uint8 MYUART_485Rec(unsigned char *buf, unsigned char len);
void  MYUART_485Send(unsigned char *buf, unsigned char len);
void  MYUART_485Driver(void);
void SaveSetValue(void);
void SystemInit(void);
#endif
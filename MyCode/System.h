#ifndef _SYSTEM_H
#define _SYSTEM_H

#define STATE_MANUA    0
#define STATE_AUTO     1

#define null        0
#define YES         1
#define NO          0

#define NOERROR     1
#define ERROR       0

#define OPEN        1
#define OFF         0

typedef struct
{
	uint16 u16ErrorState;	
	uint16 u16ErrorMessage;
	uint16 u16SvState;
	uint8  u8SystemState;
	uint8  u8MState;
	uint8  u8DelayEnd; 
	uint8  u8FunctionMul;
	uint8  u8ParentSysState;
	uint8  u8ParentState;	 
}stSystemState;

#define EEP_ADDR_DOLIMITL    0x1420
#define EEP_ADDR_DOLIMITH    0x1422
#define EEP_ADDR_TEMPLIMITH  0x1424
#define EEP_ADDR_RELAY_CTRL  0x1426
//写地址
#define MANUA_CONTROL           10
      #define CMD_RELAY_ON      1
      #define CMD_RELAY_OFF     2
#define SET_FACTOR           11        //参数设置
#define RELAY_CONTROL_WAY    12        //继电器手自动切换
#define REAL_VALUE_W         13        //实时值，溶氧、温度

//读地址
#define RELAY_STATE          1         //继电器状态
#define RELAY_WAY_STATE      2         //手动自动状态
#endif
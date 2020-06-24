#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef unsigned char  uint8;        // 无符号8位整型变量
typedef signed   char  int8;         // 有符号8位整型变量
typedef unsigned short uint16;       // 无符号16位整型变量
typedef signed   short int16;        // 有符号16位整型变量
typedef unsigned long  uint32;       // 无符号32位整型变量
typedef signed   long  int32;        // 有符号32位整型变量

typedef union {
    uint8  CharType[2];
    uint16 ShortType;  
}unCharToShort;

typedef union {
    uint8  CharType[4];
    uint32 LongType;  
}unCharToLong;
typedef union {
    uint16 ShortType[2];
    float FloatType;
}unShortToFloat;

typedef struct{
    uint16 u16DOLimitH;     //溶氧值上限
    uint16 u16DOLimitL;     //溶氧值下限
    uint16 u16TempLimitH;   //温度上限
    uint16 u16TempLimitL;   //温度上限
    uint16 u16RelayCtrlFlag;//继电器手自动控制标志   0:手动 1:自动
}stFactor; 
typedef struct{
    float  fRealDOValue;   //实时溶氧值
    float  fRealTemper;    //实时温度值
    uint16 u16RelayState;   //继电器开关状态
    uint16 u16ReadTempFlag;
    uint16 u16ReadDoFlag;
}stMoni;
#endif
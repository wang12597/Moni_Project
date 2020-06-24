#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef unsigned char  uint8;        // �޷���8λ���ͱ���
typedef signed   char  int8;         // �з���8λ���ͱ���
typedef unsigned short uint16;       // �޷���16λ���ͱ���
typedef signed   short int16;        // �з���16λ���ͱ���
typedef unsigned long  uint32;       // �޷���32λ���ͱ���
typedef signed   long  int32;        // �з���32λ���ͱ���

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
    uint16 u16DOLimitH;     //����ֵ����
    uint16 u16DOLimitL;     //����ֵ����
    uint16 u16TempLimitH;   //�¶�����
    uint16 u16TempLimitL;   //�¶�����
    uint16 u16RelayCtrlFlag;//�̵������Զ����Ʊ�־   0:�ֶ� 1:�Զ�
}stFactor; 
typedef struct{
    float  fRealDOValue;   //ʵʱ����ֵ
    float  fRealTemper;    //ʵʱ�¶�ֵ
    uint16 u16RelayState;   //�̵�������״̬
    uint16 u16ReadTempFlag;
    uint16 u16ReadDoFlag;
}stMoni;
#endif
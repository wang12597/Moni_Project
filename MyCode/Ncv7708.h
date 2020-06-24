#ifndef _NCV7708_H
#define _NCV7708_H
#define SRR  0x0001
#define SV11  0x0002
#define SV12  0x0004
#define SV10  0x0008
#define SV9  0x0010

#define SV2  0x0800//0x0020
#define SV1  0x1000//0x0040
#define SV3  0x0200//0x0080

#define SV4  0x0400//0x0100
#define SV6  0x0080//0x0200
#define SV5  0x0100//0x0400
#define SV7  0x0020//0x0800
#define SV8  0x0040//0x1000
#define OCD  0x2000
#define ULD  0x4000
#define OVLO 0x8000

#define RELAY SV1
#define SVALL SV1|SV2|SV3|SV4|SV5|SV6|SV7|SV8|SV9
#define SVCHECK OCD|ULD|OVLO|SRR

void NCV7708_Enable(void);
void NCV7708_Disable(void);

void SetValve(uint16 u16ValveOn, uint16 u16ValveOff);
uint16 NCV7708_Write16Bits(uint16 u16Value);
void ValveTest(void);
#endif
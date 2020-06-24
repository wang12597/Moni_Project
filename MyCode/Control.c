#include "includes.h" 
stMoni g_stMoni;  
extern volatile stFactor g_stFactor;
void RelayCtrl(uint16 MechCmd)
{
   switch(MechCmd)
   {
       case CMD_RELAY_ON:
           if(g_stFactor.u16RelayCtrlFlag == STATE_MANUA)
           {
              //�򿪼̵�������¼״̬
              SetValve(RELAY,0);
              LED_PutVal(0);
           }
       break;
       case CMD_RELAY_OFF:
           if(g_stFactor.u16RelayCtrlFlag == STATE_MANUA)
           {
              //�رռ̵�������¼״̬
              SetValve(0,RELAY);
              LED_PutVal(1);
           }
       break;
       default:
       break;
   }
}
void RealStateMoni(void)
{
  if(g_stFactor.u16RelayCtrlFlag == STATE_AUTO)
  {
     if(g_stMoni.fRealTemper > g_stFactor.u16TempLimitH)
     {
        //�رռ̵�������¼״̬ 
        if(g_stMoni.u16RelayState == OPEN) 
        {
          SetValve(0,RELAY);  
        }
     }
     else
     {
        
        if(g_stMoni.fRealDOValue < g_stFactor.u16DOLimitL)
        {
           //�򿪼̵�������¼״̬
           if(g_stMoni.u16RelayState == OFF)
           {
              SetValve(RELAY,0);
           }
        }
        else if(g_stMoni.fRealDOValue > g_stFactor.u16DOLimitH)
        {
           //�رռ̵�������¼״̬
           if(g_stMoni.u16RelayState == OPEN)
           {
              SetValve(0,RELAY);  
            }
        }
        else
        {
           if(g_stMoni.u16RelayState == OPEN)
           {
              SetValve(0,RELAY);  
            }
        }
     }
  }  
}
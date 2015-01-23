#ifndef COMMS_H__
#define COMMS_H__

enum MASK
{
  FRONT = 0xF0,
  BACK  = 0x0F

};

enum HEADER
{
  CARDS    =0x50,   //80
  BETLIMITS=0X60,   //96
  MONEY    =0X70,   //112
  BET_AMT  =0X80,   //128
  NAME     =0X90    //144
  
};

#endif

#ifndef COMMS_H__
#define COMMS_H__



typedef struct data
{
  int      cardRecieved=0;
  uint8_t  card_buff[2];
  uint8_t  cards[4];
  
  uint8_t  money_buff[2];
  uint16_t money;
  
  uint8_t  limit_buff[4];
  uint16_t limit_L;
  uint16_t limit_H;
  
  uint8_t  wMoney_buff[2];
  uint16_t wMoney;
 
  bool roundState=false;
  bool gameStart=false;

}data;

namespace DEALER_CALLS
{
  enum CALLS
  {
    SET_CARDS    =1,
    SET_NAME     =2,
    SET_MONEY    =3,
    SET_LIMIT    =4,
    ROUND_STATE  =5,    
    INITIATE_BET =6,
    WIN_MONEY    =7
  };
    
}
namespace BET
{
  enum TYPE
  {
    FOLD = 65534
  };
}

namespace PLAYER_SENDS
{
  enum SENDS
  {
    NAME  =1,
    BET   =2,
    FOLD  =3    
  };
}


namespace DATA
{
  enum STATE
  {
    RECIEVED=1,// 0b00000001
    NONE=0,
    
    NAME=15,
    BET=2,
    BOOL=1
  };  
}

enum MASK
{
  HIGH_NIBBLE   = 0xF0,
  LOW_NIBBLE    = 0x0F,
  
  BYTE_MASK  =0xFF
};

enum HEADER
{ 
  //headers that calls player classes  
  CARDS           =0x01,  
  NAME            =0x02,   
  MONEY           =0x03,   
  LIMITS          =0x04, 
  ROUND_STATE     =0x05, 
  REQUEST_BET     =0x06,
  RECIV_WINNINGS  =0X07,

  
  //USE TO PACK PLAYER DATA
  BET_AMT     =0x08 
  
};





#define U16_TO_BYTE_L(U16)      ( U16     & BYTE_MASK)
#define U16_TO_BYTE_H(U16) ((U16>>8) & BYTE_MASK)

#define BYTE_TO_U16(byte1,byte2)((((uint16_t)byte1)<<8)|byte2)
#endif

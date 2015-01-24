/// @brief comms.h
/// @author Eddy chen
/// @version 2.0
/// @date 21/01/2015

#ifndef COMMS_H__
#define COMMS_H__


///@brief a structure that stores data that will be drawn by the player class 
typedef struct data
{
  int   cardRecieved=0;
  byte  card_buff[2];
  byte  cards[4];
  
  byte  money_buff[2];
  uint16_t money;
  
  byte  limit_buff[4];
  uint16_t limit_L;
  uint16_t limit_H;
  
  byte  wMoney_buff[2];
  uint16_t wMoney;
 


}data;


///@brief a namespace that is used to return dealer_calls according to the data recieved
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
    WIN_MONEY    =7,
    RESET_CARDS  =8,
    RESET_PLAYER =9
  };
    
}

///@brief a bet enum setup by the player side that is shared by comms and player
namespace BET
{
  enum TYPE
  {
    NAME = 1,
    BET  = 2,
    FOLD = 65534 // 0xFFFFt
  };
}

///@brief a enum setup to indicate the player_actions
namespace PLAYER_SENDS
{
  enum SENDS
  {
    NAME  =1,
    BET   =2,
    FOLD  =3    
  };
}

///@brief a enum to indicate the different packet sizes for a data type
namespace DATA
{
  enum SIZE
  {
    RECIEVED=1,// 0b00000001
    NONE=0,
    
    BOOL=1,//MAYBE REMOVED
    NAME=15,
    BET=2,
    FOLD=2
  };  
}

///@brief a mask to extract high and low nibble
enum MASK
{
  HIGH_NIBBLE   = 0xF0,
  LOW_NIBBLE    = 0x0F,
  
  BYTE_MASK  =0xFF
};

///@brief a header  enum to define the different header different content that is sent in the header
enum HEADER
{ 
  //headers that calls player classes  
  CARDS           =0x10,  
  NAME            =0x20,   
  MONEY           =0x30,  
  LIMITS          =0x40, 
  ROUND_STATE     =0x50, 
  REQUEST_BET     =0x60,
  RECIV_WINNINGS  =0X70,

  
  //USE TO PACK PLAYER DATA
  BET_AMT     =0x80 
  
};




///@brief macros to convert U16 to bytes
#define U16_TO_BYTE_L(U16) ( U16     & BYTE_MASK)
#define U16_TO_BYTE_H(U16) ((U16>>8) & BYTE_MASK)

///@brief A macro to convert bytes U16
#define BYTE_TO_U16(byte1,byte2)((((uint16_t)byte1)<<8)|byte2)
#endif

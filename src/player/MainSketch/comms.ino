#include "comms.h"
#include "card.h"

//local use
uint8_t convertAscii_to_byte(uint8_t &_packets)
{   
    uint8_t buff[_packets];
    uint8_t value=0;
    while(Serial.available()<=0);
    Serial.readBytes(buff,_packets);
    for (int i=0;i<_packets;i++)
    {  
       buff[i]=buff[i]-48;
           
    }
     for (int i=0;i<(_packets-1);i++)
    {  
       buff[i]=buff[i]<<4;
            
    }
       
   
     for (int i=0;i<_packets;i++)
    {
       
       value=value|buff[i];       
           
    }
    return value;
}


uint8_t getData(data &_coms)
{
  uint8_t header,packets,content=0;
  uint8_t header_size=2; //used for taking in from serial monitor for reading bytes in  
  
  header=convertAscii_to_byte(header_size);//CHANGE THE TO READBYTES(PACKET)
 
   
   
   content=(header & HIGH_NIBBLE)>>4;
   packets=(header & LOW_NIBBLE);
    

 //CHECKS FOR THE INCOMING DATA SENT FROM DEALER


  //used for detecting card data
   
  

  switch(content)
  {
   
     
     case CARDS:
          Serial.write(DATA::RECIEVED);
         
          Serial.print("Cards");
          
          while(Serial.available()<=0);
          Serial.readBytes(coms.card_buff,packets);  //CHANGE THE TO READBYTES(PACKET)
          if (coms.cardRecieved==0)
          {
            coms.cards[0]   = RANKOF(coms.card_buff[0]);
            coms.cards[1]   = SUITOF(coms.card_buff[0]);
            coms.cardRecieved+=1;
          }
          else
          {
            coms.cards[2]   = RANKOF(coms.card_buff[1]);
            coms.cards[3]   = SUITOF(coms.card_buff[1]);
          }
          
          if (coms.cardRecieved==1)
          {
            coms.cardRecieved=0;
          }
         
          return DEALER_CALLS::SET_CARDS;         
          break;
     
     case NAME:
          Serial.print("INPUT NAME");
          return DEALER_CALLS::SET_NAME; 
          break;
     
     case MONEY:
          Serial.write(DATA::RECIEVED);
          
          Serial.print("MONEY");
          
          while(Serial.available()<=0);
          Serial.readBytes(coms.card_buff,packets);  //CHANGE THE TO READBYTES(PACKET)
         
          coms.money  = BYTE_TO_U16(coms.money_buff[0],coms.money_buff[1]);
          
          return DEALER_CALLS::SET_MONEY; 
          break;
     
     case LIMITS:
          Serial.print("LIMITS");
          
          Serial.write(DATA::RECIEVED);
          while(Serial.available()<=0);
          
          Serial.readBytes(coms.limit_buff,packets);  //CHANGE THE TO READBYTES(PACKET)
         
          coms.limit_L  = BYTE_TO_U16(coms.limit_buff[0],coms.limit_buff[1]);
          coms.limit_H  = BYTE_TO_U16(coms.limit_buff[2],coms.limit_buff[3]);
          break;
     
     case REQUEST_BET:
          Serial.print("REQUEST_BET");
          return DEALER_CALLS::INITIATE_BET;          
          break;
     
     case RECIV_WINNINGS:
          Serial.print("RECIEVE_BET");
          
          while(Serial.available()<=0);
          Serial.readBytes(coms.wMoney_buff,packets);  //CHANGE THE TO READBYTES(PACKET)
         
          coms.wMoney  = BYTE_TO_U16(coms.wMoney_buff[0],coms.wMoney_buff[1]);
          
          
          return DEALER_CALLS::WIN_MONEY;          
          break;
     
     default:
     
     Serial.print("NOT_VALID");
     return DATA::NONE;
     Serial.write(DATA::NONE);     
     break; 
  }
  
}

// decoupling code
bool sendName(char _name[15])
{
            while(!RecieveConfirmation())
            {
              sendHeader(PLAYER_SENDS::NAME);
            }
            
            for (int i=0;i<DATA::NAME;i++)
            {
              Serial.print(_name[i]); 
            }
              
            return true;    
            
}

bool sendBet(uint16_t _bet)
{
          uint8_t bytes[2];
//           while(!RecieveConfirmation())
//          {
//           sendHeader(PLAYER_SENDS::BET);
//          }
          bytes[0]=U16_TO_BYTE_H(_bet);
          bytes[1]=U16_TO_BYTE_L(_bet);
         
          for (int i=0;i<DATA::BET;i++)
          {
           Serial.write(bytes[i]);
          }
          return true;   
            
}


bool sendFold(uint16_t _bet)
{         
          uint8_t bytes[2];
           while(!RecieveConfirmation())
          {
           sendHeader(PLAYER_SENDS::FOLD);
          }
          bytes[0]=U16_TO_BYTE_H(_bet);
          bytes[1]=U16_TO_BYTE_L(_bet);
         
          for (int i=0;i<DATA::BET;i++)
          {
           Serial.write(bytes[i]);
          }
          return true;   
            
}



void sendHeader(uint8_t _datatype)
{
  uint8_t header=0;
  switch(_datatype)
     {
      case PLAYER_SENDS::NAME:     //HEADER FOR SENDING BET_AMT 
           header=NAME<<4|DATA::NAME;
           Serial.write(header);
           break;
      
      case PLAYER_SENDS::BET:    //HEADER FOR SENDING BET_AMT 
           header=BET_AMT<<4|DATA::BET;
           Serial.write(header);
           break;
      
      case PLAYER_SENDS::FOLD:      //HEADER FOR SENDING NAME
           header=BET_AMT<<4|DATA::FOLD;
           Serial.write(header);
           break;    
      
           default:
           break;
     }
  
}

bool RecieveConfirmation()
{ 
  bool success=0;
  while(Serial.available()>0)
  {
     success=Serial.read();   
  }
  return success;
}  

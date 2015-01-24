/// @brief comms.ino
/// @author Eddy chen
/// @version 2.0
/// @date 21/01/2015

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

///@brief getData, A functions that listens and returns Data recieved to the Player class
///@param [in] &_coms: Passes in a reference of the coms class
///@param [returns] uint8_t: A value that is represented in enum DEALERCALLS
uint8_t getData(data &_coms)
{
 
  //initialize variable to store header information
  //The header is one byte and contains packets and content information
  //EG: 0001 0010  [contents][packets] = [HEADER::CARDS][2]
  uint8_t header,packets,content=0;
  uint8_t header_size=2; 
  
  //read a byte from serial
  header=convertAscii_to_byte(header_size);//CHANGE THE TO READBYTES(PACKET)
 
   
  //breaking up the header 
  content=(header & HIGH_NIBBLE);
  packets=(header & LOW_NIBBLE);
    
  //switch driven by headers
  //cases are represented using header classes
  switch(content)
  {
   
     
     case CARDS:
          {
            //writes confirmation when releavant header is detected
            Serial.write(DATA::RECIEVED);
            
            //for testing purposes
            Serial.print("Cards");
            
            //puts the arduino into a state to listen for data
            while(Serial.available()<=0);
            //read the number of packets and store it in coms card_buffer
            Serial.readBytes(coms.card_buff,packets); 
            
            //checks if the recived card is the first card or second card
            if (coms.cardRecieved==0)
            {
              coms.cards[0]   = RANKOF(coms.card_buff[0]);
              coms.cards[1]   = SUITOF(coms.card_buff[0]);
              coms.cardRecieved+=1;
            }
            else
            {
              coms.cards[2]   = RANKOF(coms.card_buff[0]);
              coms.cards[3]   = SUITOF(coms.card_buff[0]);
            }
            
            //if the second card has been filled, it will replace the first card when it recieves a new card 
            if (coms.cardRecieved==1)
            {
              coms.cardRecieved=0;
            }
            
            //Notify the player class that cards have been recieved
            return DEALER_CALLS::SET_CARDS;         
            break;
          }
     
     case NAME:
          {
            //for testing purposes
            Serial.print("INPUT NAME");
            //notify player that dealer want to set name
            return DEALER_CALLS::SET_NAME; 
            break;
          }
     case MONEY:
          {
          //writes confirmation when releavant header is detected
          Serial.write(DATA::RECIEVED);
          //for testing purposes
          Serial.print("MONEY");
          
          //puts the arduino into a state to listen for data
          while(Serial.available()<=0);
          
          //read the number of packets and store it in coms money_buffer
          Serial.readBytes(coms.money_buff,packets);  
          
          //store money to coms structure by converting a byte to uint16
          coms.money  = BYTE_TO_U16(coms.money_buff[0],coms.money_buff[1]);
          
          //notify player that dealer money recieved
          return DEALER_CALLS::SET_MONEY; 
          break;
          }
     case LIMITS:
          {
          //for testing purposes
          Serial.print("LIMITS");
          
          //writes confirmation when releavant header is detected
          Serial.write(DATA::RECIEVED);
          
          //puts the arduino into a state to listen for data
          while(Serial.available()<=0);
          
          //read the number according to the packets indicated in the header
          Serial.readBytes(coms.limit_buff,packets);  
          
          //store limit data to local coms struct 
          coms.limit_H  = BYTE_TO_U16(coms.limit_buff[0],coms.limit_buff[1]);
          coms.limit_L  = BYTE_TO_U16(coms.limit_buff[2],coms.limit_buff[3]);
          break;
          }
     case REQUEST_BET:
          
          //for testing purposes
          Serial.print("REQUEST_BET");
          
          Serial.write(DATA::RECIEVED);
          //notify dealer to set bet
          return DEALER_CALLS::INITIATE_BET;          
          break;
     
     case RECIV_WINNINGS:
          //for testing purposes
          Serial.print("RECIEVE_BET");
          
          //puts the arduino into a state to listen for data
          while(Serial.available()<=0);
          
          //read the number according to the packets indicated in the header
          Serial.readBytes(coms.wMoney_buff,packets);  //CHANGE THE TO READBYTES(PACKET)
          
          //storing the winnings to the coms 
          coms.wMoney  = BYTE_TO_U16(coms.wMoney_buff[0],coms.wMoney_buff[1]);
          
          //notifying the dealer class that winnings have been recieved
          return DEALER_CALLS::WIN_MONEY;          
          break;
     
     default:
     
     Serial.print("NOT_VALID");
     //write to serial data is not valid
     Serial.write(DATA::NONE); 
     return DATA::NONE;
         
     break; 
  }
  
}

///@brief sendName() a function to send player name to the dealer
///@param[_in] char array[15] takes in a name 15 bytes long
///@param returns bool to say send success
void sendName(char _name[15])
{   
            
           //when no confirmation for valid header it will keep sending the header
            
            while(!RecieveConfirmation())
            {
                //send data over the size of the packets defined in the DATA enum
               sendHeader(PLAYER_SENDS::NAME);
            }
            
            for (int i=0;i<DATA::NAME;i++)
            {
                Serial.write(_name[i]); 
            }
                
            
            
          
            
              
            
}

///@brief sendBet() a function to send player bet value
///@param[_in] uint16_t takes in a 2byte number
///@param returns bool to say send success
bool sendBet(uint16_t _bet)
{         
          // check to see if bet is fold. if so call fold function.
          // so we only use the send bet function.
          if( _bet == BET::FOLD )
          {
            bool sent = sendFold();
            return sent;
          }
          else
          {
            //initialize the a local buffer to store a uint16 which will be broken into a byte and sent over the serial
            uint8_t bytes[2];
            //when no confirmation for valid header it will keep sending the header
            do
            {
             sendHeader(PLAYER_SENDS::BET);
            }while (!RecieveConfirmation());
            //breaks up to bytes
            bytes[0]=U16_TO_BYTE_H(_bet);
            bytes[1]=U16_TO_BYTE_L(_bet);
            
            //sends data
            for (int i=0;i<DATA::BET;i++)
            {
             Serial.write(bytes[i]);
            }
            return true;   
          }
            
}

///@brief sendFold() a function to send player fold state
///@param[_in] uint16_t takes in a 2byte number
///@param returns bool to say send success
bool sendFold()
{         

      
       
          //initialize the a local buffer to store a uint16 which will be broken into a byte and sent over the serial
          uint8_t bytes[2];
          //when no confirmation is recieved from the dealer it will keep sending the header
          do
          {
           sendHeader(PLAYER_SENDS::FOLD);
          }while(!RecieveConfirmation());
          
          //breaks up to bytes
          bytes[0]=U16_TO_BYTE_H(BET::FOLD);
          bytes[1]=U16_TO_BYTE_L(BET::FOLD);
          
          //sends data
          for (int i=0;i<DATA::BET;i++)
          {
           Serial.write(bytes[i]);
          }
          return true;
          
            
}


///@brief sendHeader() a function to send header
///@param[_in] uint8_t takes enums from PLAYER_SENDS and switchs to process the header and sent it to delear coms
void sendHeader(uint8_t _datatype)
{
  uint8_t header=0;
  switch(_datatype)
     {
      case PLAYER_SENDS::NAME:   //PACKING HEADER FOR SENDING BET_AMT 
           {
             header=NAME|DATA::NAME;
             Serial.write(header);
             break;
           }
      case PLAYER_SENDS::BET:    //HEADER FOR SENDING BET_AMT 
           {
             header=BET_AMT|DATA::BET;
             Serial.write(header);
             break;
           }
      case PLAYER_SENDS::FOLD:      //HEADER FOR SENDING NAME
           {
             header=BET_AMT|DATA::FOLD;
             Serial.write(header);
             break;    
           }
           default:
           break;
     }
  
}

///@brief RecieveConfirmation() a function to check confirmation from dealer that the appropriate header has been recieved
bool RecieveConfirmation()
{ 
  //success is set to false unless serial reads a confirmation
  bool success=false;
  if (Serial.available()>0)
  {
    success=Serial.read()-48;   
  }
  return success;
}  



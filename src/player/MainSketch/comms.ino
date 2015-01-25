/// @brief comms.ino
/// @author Eddy chen
/// @version 2.0
/// @date 21/01/2015

#include "comms.h"
#include "card.h"

/* for testing purposes with serial terminal turns each Ascii read into to proper byte
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
*/

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
  if(Serial.available()>0)
  {
  //read a byte from serial
  //header=convertAscii_to_byte(header_size);//CHANGE THE TO READBYTES(PACKET)
  header=Serial.read();
   
  //breaking up the header 
  content=(header & HIGH_NIBBLE);
  packets=(header & LOW_NIBBLE);
    
  //switch driven by headers
  //cases are represented using header classes
  switch(content)
  {
   
     
     case CARDS:  //when a card header is received it notifies players to set cards
          {
            
            //This will only take in one card at a time, coms.card[rank][suit]will be change when a new card is recieved
            if(Serial.available()<0);
         
            //read the number of packets and store it in coms card_buffer
            coms.card=Serial.read();
            
            
             
             coms.cards[0]   = RANKOF(coms.card);
            
               
  
             coms.cards[1]   = SUITOF(coms.card);
            
                 //Notify the player class that cards have been recieved
            return DEALER_CALLS::SET_CARDS;         
            break;    
            
       
          }
     
     case NAME:  // when a name is recieved dealer goes into a state to setname
          {
              
            //notify player that dealer want to set name
            return DEALER_CALLS::SET_NAME; 
            break;
          }
     case RESET_CARDS: // when a reset card header is recieved
         {
              
          //notify player that dealer want to set name
          return DEALER_CALLS::RESET_CARDS; 
          break;
          }
    case ROUND_STATE: // when round state header is recieved notify player to reset
         {
      
            while(Serial.available()<=0);
        
            //read the number of packets and store it in coms money_buffer
            Serial.readBytes(coms.money_buff,packets);  
            
            //store money to coms structure by converting a byte to uint16
            coms.money  = BYTE_TO_U16(coms.money_buff[0],coms.money_buff[1]);
            
            return DEALER_CALLS::RESET_PLAYER; 
            break;
          }
     case MONEY: // when money is recieved
          {
            //writes confirmation when releavant header is detected
            
                      
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
     
     case RECIV_WINNINGS: //when winnings is recieved
         {
          
            //puts the arduino into a state to listen for data
            while(Serial.available()<=0);
           
            //read the number according to the packets indicated in the header
            Serial.readBytes(coms.wMoney_buff,2);  //CHANGE THE TO READBYTES(PACKET)
            
            //storing the winnings to the coms 
            coms.wMoney  = BYTE_TO_U16(coms.wMoney_buff[0],coms.wMoney_buff[1]);
            
            //notifying the dealer class that winnings have been recieved
            return DEALER_CALLS::WIN_MONEY;          
            break;
          }
     
     case LIMITS:  // when limits is called it will notify the player to initiate bet
          {
          
            //puts the arduino into a state to listen for data
            while(Serial.available()<=0);
            
            //read the number according to the packets indicated in the header
            Serial.readBytes(coms.limit_buff,4);  
            
            //store limit data to local coms struct 
             coms.limit_H  = BYTE_TO_U16(coms.limit_buff[2],coms.limit_buff[3]) ;
             coms.limit_L  = BYTE_TO_U16(coms.limit_buff[0],coms.limit_buff[1]);
            
            return DEALER_CALLS::INITIATE_BET;
            break;
           }

     
     default:        
     break; 
  }
 }
}

///@brief sendName() a function to send player name to the dealer
///@param[_in] char array[15] takes in a name 15 bytes long
///@param returns bool to say send success
void sendName(char _name[15])
{   
                                     
   //send data over the size of the packets defined in the DATA enum
           
           sendHeader(PLAYER_SENDS::NAME);
         
            
            for (int i=0;i<DATA::NAME;i++)
            {
                Serial.write(_name[i]); 
            }
                                                   
              
            
}

///@brief sendBet() a function to send player bet value
///@param[_in] uint16_t takes in a 2byte number
///@param returns bool to say send success
void sendBet(uint16_t _bet)
{         
            
            uint8_t bytes[2];
            if (_bet==BET::FOLD)
            {
                Serial.write(0xFFFF); //sends folds
            }
            else
            {  
              sendHeader(PLAYER_SENDS::BET);
  
            
              //}while (!RecieveConfirmation());
              //breaks up to bytes
              bytes[0]=U16_TO_BYTE_H(_bet);
              bytes[1]=U16_TO_BYTE_L(_bet);
              Serial.write(bytes[0]);
              Serial.write(bytes[1]);
              //Serial.flush();
              //sends data
            }
            //return true;   
          //}
            
}

/////@brief sendFold() a function to send player fold state
/////@param[_in] uint16_t takes in a 2byte number
/////@param returns bool to say send success
//bool sendFold()
//{         
//
//      
//       
//          //initialize the a local buffer to store a uint16 which will be broken into a byte and sent over the serial
//          uint8_t bytes[2];
//          //when no confirmation is recieved from the dealer it will keep sending the header
//     
//          //breaks up to bytes
//       
//           Serial.write(bytes[i]);
//          }
//          return true;
//          
//            
//}


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
             Serial.flush();
             break;
           }
      case PLAYER_SENDS::BET:    //HEADER FOR SENDING BET_AMT 
           {
             //header=BET_AMT|DATA::BET;
             header=0x82;
             Serial.write(header);
             Serial.flush();
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

/*was thinking to implement a function that checks if the right header is recieved and continues to send the package*/
///@brief RecieveConfirmation() a function to check confirmation from dealer that the appropriate header has been recieved
bool RecieveConfirmation()
{ 
  //success is set to false unless serial reads a confirmation
  bool success=false;
  if (Serial.available()>0)
  {
    success=Serial.read();   
  }
  return success;
}  



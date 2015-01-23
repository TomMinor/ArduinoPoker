/**Front mask and Back mask 
   represents [Front][0000] [0000][Back]
  
   Simply it extracts info from either the front nibble or back nibble of a byte
**/
#include "comms.h"
//write a function for getting header and prepare serial to recieve data


bool getHeader(uint8_t _card[4])
{
 // initialize local variables to to break packet into head and numBytes
   if(Serial.available()>0)
   {
         uint8_t packetHead ,head ,numBytes,byteCounter=0;  
         Serial.write("Header Recieved \n");
         
         lcd.clear();
         lcd.write("Header processing");
         
         packetHead= Serial.parseInt();
         head      = packetHead & FRONT;
         numBytes  = packetHead & BACK;
         check_header(head);
         
         Serial.write("Packets :");
         Serial.print(numBytes,DEC);
         Serial.write("\n");  
        // a buffer to store the payload or data
        char data[numBytes];
        memset(data, 0, numBytes);
         
     while(byteCounter<numBytes)
     {
       
           if(Serial.available()>0)
           {
             
             lcd.clear();
             lcd.write("Drop Payload ");
             
             data[byteCounter]=Serial.parseInt();
             
             getCard(data[byteCounter],_card,numBytes,byteCounter);
            
             Serial.write("Recieved packet ");
             Serial.print(byteCounter,DEC);
             Serial.write("\t");
             Serial.print(data[byteCounter],DEC);
             Serial.write("\n");
             
             
             byteCounter+=1;
           }
           
       
       
    }
    byteCounter=0;
    Serial.write(data,numBytes);
    }
    else
    {
       return 0; 
    } 
}




bool getCard(uint8_t _data,uint8_t _card[4],uint8_t _byteSize,uint8_t byteCounter)
{
  //card structure 1000 0001 [SPADE] [TWO] [suit][value]
  
  int i=0;
  if(byteCounter==0)
  {
    
   _card[i]   = RANKOF(_data);
   _card[i+1] = SUITOF(_data);
  }
  else
  {
    i=2;
   _card[i]   = RANKOF(_data);
   _card[i+1] = SUITOF(_data);
  }

}
 

void check_header(uint8_t _header)
{
    switch(_header)
     {
        case CARDS:
        Serial.write("Cards incoming\n");
        break;
      
        case BETLIMITS:
        Serial.write("BETLIMITS incoming\n");
        break;
        
        case MONEY:
        Serial.write("MONEY incoming\n");
        break;
        
        case BET_AMT:
        Serial.write("MONEY incoming\n");
        break;
        
        case NAME:
        Serial.write("MONEY incoming\n");
        break;
               
        default:
        break;
     }

}


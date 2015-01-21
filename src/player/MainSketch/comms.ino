/**Front mask and Back mask 
   represents [Front][0000] [0000][Back]
  
   Simply it extracts info from either the front nibble or back nibble of a byte
**/
#define FRONT_MASK        (0xF0)
#define BACK_MASK         (0x0F)



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
     Serial.write(packetHead);
     head      = packetHead & FRONT_MASK;
     numBytes  = packetHead & BACK_MASK;
     
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
         getCard(data[byteCounter],_card,numBytes);
        
         Serial.write("Recieved packet ");
         Serial.print(byteCounter,DEC);
         Serial.write("\t");
         Serial.print(data[byteCounter],DEC);
         Serial.write("\t");
         Serial.print(data[byteCounter],BIN);
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
int getData()
{
 
}

bool getCard(uint8_t _data,uint8_t _card[4],uint8_t _byteSize)
{
  //card structure 1000 0001 [SPADE] [TWO] [suit][value]
   
  for (int i=0;i<=_byteSize;i+=2)
  {
   _card[i]   = _data & BACK_MASK;
   _card[i+1] = _data & FRONT_MASK;
  }
   
 
}



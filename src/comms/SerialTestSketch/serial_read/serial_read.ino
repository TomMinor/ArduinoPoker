#include "Arduino.h"
byte _packets=2;
byte buff[128];
void setup() 
{
  
  
  Serial.begin(9600);

}

void loop() 
{
  while(Serial.available()<=0);
  Serial.print(1,BIN);
  Serial.print("\n");
  Serial.readBytes(buff,_packets);

}

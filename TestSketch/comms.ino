int getCommand()
{
  //int a=0;
  Serial.begin(9600);
  int a=0;
  if (Serial.available()>0)
  {
    a =Serial.read()-'0';
  }
  
  return a;
 
}

bool getData()
{
}

bool sendData()
{
}


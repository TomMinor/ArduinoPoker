#ifndef PLAYER_H__
#define PLAYER_H__

#include "input.h"
#include <LiquidCrystal.h>
#include <Arduino.h>



class player

{
private:

    uint16_t m_money;
    uint8_t m_numCards;
    char m_playerName[15];
    //PlayingCard m_cards[];
    
    //eddy variables
    char character   =0;
    uint16_t uInteger=0;
    

  public:

    player(uint16_t _money, uint8_t _cardNum);
    ~player();

    uint16_t placeBet(uint16_t _max, uint16_t _min);
    void receiveMoney(uint16_t _money);
    void receiveCard();
    void setName();
    char* getName();
    void resetPlayer(uint16_t _money, uint16_t _cardNum);
    void resetCards();
    uint16_t getMoney() { return m_money; }
    
    
    //Eddy's stuff
    
    template< typename _A ,typename _B > String CompareType( _A a, _B b,char dataType[] )
    {
         if (dataType=="bool")
        {
          return "folded";  
        }
    }
    
    template< typename _A > String CompareType( _A a, _A b ,char dataType[])
    {
       
        
          return "betted";
         
    }
    
    
    template<class TYPE> bool sendData(TYPE data, uint8_t byteSize, char datatype[])
   
    {
       Serial.print("Action");
       Serial.print("\t");
       Serial.print(CompareType(data,uInteger,datatype));
       Serial.print("\t");
       Serial.print(data);
       Serial.print("\n");
    }


};

#endif

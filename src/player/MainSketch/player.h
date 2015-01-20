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
    char[16] m_playerName[];
    //PlayingCard m_cards[];


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
    


};

#endif

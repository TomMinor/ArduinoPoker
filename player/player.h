#ifndef PLAYER_H__
#define PLAYER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include <arduino.h>

class player
{
private:

    unsigned int m_money;
    int m_numCards;
    char m_playerName[];
    int m_currentHandNum;

  public:

    player(unsigned int _money, int _cardNum);
    ~player();

    unsigned int getMoney();

    unsigned int placeBet(unsigned int _max, unsigned int _min);
    void receiveCard(){};
    void setName(){};
    unsigned int getMoney() { return m_money; }

};

#endif

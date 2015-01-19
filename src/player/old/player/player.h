#ifndef PLAYER_H__
#define PLAYER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


class player
{
private:

    unsigned int m_money;
    int m_numCards;
    char m_playerName[];
    //PlayingCard m_cards[];

  public:

    player(unsigned int _money, int _cardNum);
    ~player();

    void placeBet(unsigned int _max, unsigned int _min);
    void receiveMoney(unsigned int _money);
    void receiveCard();
    void setName();
    void resetPlayer(unsigned int _money, unsigned int _cardNum);
    void resetCards();
    unsigned int getMoney() { return m_money; }

};

#endif

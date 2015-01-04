#ifndef PLAYER_H__
#define PLAYER_H__

#include <stdint.h>

class player
{
private:

    uint16_t m_money;
    int m_numCards;
    char m_playerName[];
    int m_currentHandNum;

  public:
    player();
    ~player();

    void placeBet();
    void recieveCard();







};

#endif

#ifndef _CARD__H_
#define _CARD__H_

enum SUIT {spade, club, heart, diamond};

typedef struct CARDS
{
    int value;
    SUIT suit;
}card;


#endif

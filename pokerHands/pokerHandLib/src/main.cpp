#include <iostream>
#include "pokerHands.h"

int main()
{
    card _public[5];

    int numPlayers=4;
    card players[numPlayers*2];

    hands::winner(numPlayers,players,_public);

    return 0;

}

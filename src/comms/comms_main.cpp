#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#include "dealer/playingcard.h"
#include "dealer/player.h"
#include "comms/dealerIO.h"
#include "comms/SerialPort.h"

/* This is just a test main() for comms, the real stuff happens in dealerLib which merges everything together. */
int main()
{
    const char* port = "/dev/ttyACM0";

    Comms::sendMoney(port, 2050);

    if(!Comms::sendCard(port, PlayingCard(Rank::KING, Suit::HEART)))
    {
        std::cout << "1st error\n";
    }

    if(!Comms::sendCard(port, PlayingCard(Rank::JACK, Suit::SPADE)))
    {
        std::cout << "2nd error\n";
    }

//    std::string data;
//    Comms::receiveName(port, data);
//    std::cout << data << "\n";


    //Comms::sendResetCards(port);

    //Comms::sendResetPlayer(port);

    //Comms::sendWin(port, 5000);
    uint16_t bet;
    Comms::receiveBet(port, bet, 1000,1050);
    std::cout << "Bet is " << bet << std::endl;

    if( bet == 0xFFFF )
    {
      std::cout << "Fold\n";
    }

    //while(true)
    //{
      //Comms::receiveBet(port, bet, 1000, 1600);
    //}

    //std::cout << bet << "\n";

    return 0;
}

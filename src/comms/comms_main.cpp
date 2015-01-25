#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#include "comms/SerialPort.h"
#include "comms/PacketTypes.h"

#include "dealer/playingcard.h"
#include "dealer/player.h"
#include "comms/dealerIO.h"



int main()
{
    const char* port = "/dev/ttyACM0";


//    Comms::sendMoney(port, 2000);

//    if(!Comms::sendCard(port, PlayingCard(Rank::KING, Suit::HEART)))
//    {
//        std::cout << "1st error\n";
//    }

//    if(!Comms::sendCard(port, PlayingCard(Rank::JACK, Suit::SPADE)))
//    {
//        std::cout << "2nd error\n";
//    }

    std::string data;
    Comms::receiveName(port, data);
    std::cout << data << "\n";


    //Comms::sendResetCards(port);

    //Comms::sendResetPlayer(port);

    uint16_t bet;
//    std::cout << "Waiting for bet" << std::endl;
    //while(true)
    //{
      //Comms::receiveBet(port, bet, 1000, 1600);
    //}

    //std::cout << bet << "\n";

    return 0;
}

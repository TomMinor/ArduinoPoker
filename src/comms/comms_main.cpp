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
    const char* port = "/dev/ttyACM1";

    //sendMoney(p0, 5395);
    if(!Comms::sendCard(port, PlayingCard(Rank::NINE, Suit::CLUB)))
    {
        std::cout << "1st error\n";
    }

    if(!Comms::sendCard(port, PlayingCard(Rank::ACE, Suit::SPADE)))
    {
        std::cout << "2nd error\n";
    }

    //sendBetLimits(p0, 1000, 5000);

    return 0;
}

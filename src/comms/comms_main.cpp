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
    player p0;

    //sendMoney(p0, 5395);
    Comms::sendCard(p0, PlayingCard(Rank::NINE, Suit::CLUB));
    Comms::sendCard(p0, PlayingCard(Rank::ACE, Suit::SPADE));

    //sendBetLimits(p0, 1000, 5000);

    return 0;
}

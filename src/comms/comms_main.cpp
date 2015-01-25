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
//    try
//    {

//        Comms::SerialPort packet("/dev/ttyACM4");
//        Comms::BytePayload data;

//        data.push_back( 0x0E | 0x00 );

//        packet.SendData(data);
//    }
//    catch(boost::system::system_error& e)
//    {
//        std::cout << "Error " << e.what() << std::endl;
//        return false;
//    }

    player p0;
    //sendCard(p0, PlayingCard(Rank::EIGHT, Suit::HEART));
    sendMoney(p0, 2000);
    //sendBetLimits(p0, 1000, 5000);



    return 0;
}

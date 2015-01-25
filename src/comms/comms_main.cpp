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
    Comms::sendCard(p0, PlayingCard(Rank::EIGHT, Suit::HEART));

    return 0;
}



//int main()
//{
//    Comms::PlayerDevices players = Comms::SerialPort::DetectSerialDevices();

//    for( auto i : players )
//    {
//        std::string portname = i.second;

//        Comms::BytePayload data;
//        data.push_back('H');
//        data.push_back('e');
//        data.push_back('l');
//        data.push_back('l');
//        data.push_back('o');

//        Comms::SerialPort test(portname);
//        test.SendData(data);
//    }
//}

#include "comms/dealerIO.h"
#include "comms/SerialPort.h"
#include "comms/PacketTypes.h"

bool sendBetLimits(player _player, unsigned int _min, unsigned int _max)
{

}

bool sendMoney(player _player, unsigned int _amount)
{
//    try
//    {
//        Comms::SerialPort packet("/dev/ttyACM0");
//        Comms::BytePayload data;
//        data.push_back( Comms::P_CARDS );
//        data.push_back( _card.getValue());

//        packet.SendData(data);
//    }
//    catch(boost::system::system_error& e)
//    {
//        std::cout << "Error " << e.what() << std::endl;
//        return false;
//    }

//    return true;
}

bool sendCard(player _player, PlayingCard _card)
{
    try
    {
        Comms::SerialPort packet("/dev/ttyACM0");
        Comms::BytePayload data;
        data.push_back( Comms::P_CARDS );
        data.push_back( _card.getValue());

        packet.SendData(data);
    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Error " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool receiveBet(player _player, unsigned int _timeout)
{

}

bool receiveName(player _player, unsigned int _timeout)
{

}

bool waitForResponse()
{

}

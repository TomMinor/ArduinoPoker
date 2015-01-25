#include "comms/dealerIO.h"
#include "comms/SerialPort.h"
#include "comms/PacketTypes.h"

//@todo More error checking

bool setPlayer(player _player, const std::vector<PlayingCard>& _cards, uint16_t _money)
{
    for( auto card : _cards )
    {
        sendCard(_player, card);
    }

    sendMoney(_player, _money);
}

bool sendBetLimits(player _player, uint16_t _min, uint16_t _max)
{
    try
    {
        Comms::SerialPort packet("/dev/ttyACM0");
        Comms::BytePayload data;

        //@todo Make this a macro
        /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
        uint8_t right = (uint8_t)_min;
        uint8_t left = (uint8_t)(_min >> 8);

        data.push_back( Comms::P_LIMITS );
        data.push_back( right );
        data.push_back( left );

        right = (uint8_t)_max;
        left = (uint8_t)(_max >> 8);

        data.push_back( right );
        data.push_back( left );

        packet.SendData(data);
    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Error " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool sendMoney(player _player, uint16_t _amount)
{
    try
    {

        Comms::SerialPort packet("/dev/ttyACM1");
        Comms::BytePayload data;

        //@todo Make this a macro
        /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
        uint8_t right = (uint8_t)_amount;
        uint8_t left = (uint8_t)(_amount >> 8);

        data.push_back( Comms::P_MONEY | 0x02 );
        data.push_back( left );
        data.push_back( right );

        packet.SendData(data);
    }
    catch(boost::system::system_error& e)
    {
        std::cout <<
                     "Error " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool sendCard(player _player, PlayingCard _card)
{
    try
    {
        Comms::SerialPort packet("/dev/ttyACM3");
        Comms::BytePayload data;

        /* Header Byte ( Type ) */
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

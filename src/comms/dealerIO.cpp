#include "comms/dealerIO.h"
#include "comms/SerialPort.h"
#include "comms/PacketTypes.h"

//@todo More error checking

namespace Comms
{

bool setPlayer(const std::string& _port, const std::vector<PlayingCard>& _cards, uint16_t _money)
{
    for( auto card : _cards )
    {
        if(!sendCard(_port, card))
        {
            return false;
        }
    }

    if(!sendMoney(_port, _money))
    {
        return false;
    }

    return true;
}

//bool sendBetLimits(const std::string& _port, uint16_t _min, uint16_t _max)
//{
//    try
//    {


//        Comms::SerialPort packet(_port);
//        Comms::BytePayload data;

//        //@todo Make this a macro
//        /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
//        uint8_t right = (uint8_t)_min;
//        uint8_t left = (uint8_t)(_min >> 8);

//        data.push_back( Comms::P_LIMITS | 0x04 );
//        data.push_back( right );
//        data.push_back( left );

//        right = (uint8_t)_max;
//        left = (uint8_t)(_max >> 8);

//        data.push_back( right );
//        data.push_back( left );

//        packet.SendData(data);
//    }
//    catch(boost::system::system_error& e)
//    {
//        std::cout << "Error " << e.what() << std::endl;
//        return false;
//    }

//    return true;
//}

bool sendMoney(const std::string& _port, uint16_t _amount)
{
    try
    {
        SerialPort packet(_port);
        BytePayload data;

        //@todo Make this a macro
        /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
        uint8_t right = (uint8_t)_amount;
        uint8_t left = (uint8_t)(_amount >> 8);

        data.push_back( P_MONEY | 0x02 );
        data.push_back( left );
        data.push_back( right );

        packet.SendData(data);
    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Error " << e.what() << std::endl;
        return false;
    }

    return true;
}



bool sendCard(const std::string& _port, PlayingCard _card)
{
    try
    {
        SerialPort packet(_port);
        BytePayload data;

        /* Header Byte ( Type ) */
        data.push_back( P_CARDS | 1 );

        /* Payload */
        data.push_back( _card.getValue() );

        //@todo Subclass boost exceptions?
        packet.SendData(data);
    }
    catch(boost::system::system_error& e)
    {
        std::cout << "Send Card Error : " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool sendWin(const std::string& _port, uint16_t _money)
{
  try
  {
      SerialPort packet(_port);
      BytePayload data;

      //@todo Make this a macro
      /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
      uint8_t right = (uint8_t)_money;
      uint8_t left = (uint8_t)(_money >> 8);

      /* Header Byte ( Type ) */
      data.push_back( P_RECIEVEWINNINGS | 2 );

      /* Payload */
      data.push_back( left );
      data.push_back( right );

      //@todo Subclass boost exceptions?
      packet.SendData(data);
  }
  catch(boost::system::system_error& e)
  {
      std::cout << "Send Win Error : " << e.what() << std::endl;
      return false;
  }

  return true;
}

bool sendResetPlayer(const std::string& _port)
{
  try
  {
      SerialPort packet(_port);
      BytePayload data;

      /* Header Byte ( Type ) */
      data.push_back( P_RESETPLAYER | 0 );

      packet.SendData(data);
  }
  catch(boost::system::system_error& e)
  {
      std::cout << "Reset Player Error : " << e.what() << std::endl;
      return false;
  }

  return true;
}

bool sendResetCards(const std::string& _port)
{
  try
  {
      SerialPort packet(_port);
      BytePayload data;

      /* Header Byte ( Type ) */
      data.push_back( P_RESETCARD | 0 );

      //@todo Subclass boost exceptions?
      packet.SendData(data);
  }
  catch(boost::system::system_error& e)
  {
      std::cout << "Reset Cards Error : " << e.what() << std::endl;
      return false;
  }

  return true;
}

bool receiveBet(const std::string& _port, uint16_t& _data, uint16_t _min, uint16_t _max, unsigned int _timeout)
{
  try
  {
    Comms::SerialPort packet(_port);
    Comms::BytePayload data;

    //@todo Make this a macro
    /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
    uint8_t right = (uint8_t)_min;
    uint8_t left = (uint8_t)(_min >> 8);

    data.push_back( Comms::P_LIMITS | 0x04 );
    data.push_back( right );
    data.push_back( left );

    right = (uint8_t)_max;
    left = (uint8_t)(_max >> 8);

    data.push_back( right );
    data.push_back( left );

    packet.SendData(data);

    BytePayload payload;
    packet.RecieveData(payload);

    printf("Payload Size : %d\n", payload.size());

    if(payload.size() != 2)
    {
      throw boost::system::system_error(boost::asio::error::fault, "Expected 2 bytes");
    }

    //@todo Check the header is correct

    /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
    _data = BYTE_TO_U16(payload[1], payload[0]);

    printf("Final Value : 0x%X : %d\n", _data, _data );
  }
  catch(boost::system::system_error& e)
  {
    std::cout << "Recieve Bet Error : " << e.what() << std::endl;
    return false;
  }

  return true;
}

bool receiveName(const std::string& _port, std::string &_data, unsigned int _timeout)
{
  try
  {
    Comms::SerialPort packet(_port);
    Comms::BytePayload data;

    data.push_back( Comms::P_NAME | 0x0);

    packet.SendData(data);

    BytePayload payload;
    packet.RecieveData(payload);

    printf("Payload Size : %d\n", payload.size());

    if(payload.size() < 15)
    {
      throw boost::system::system_error(boost::asio::error::fault, "Expected 15 bytes");
    }

    for(auto byte : payload)
    {
      _data += (char)byte;
    }
  }
  catch(boost::system::system_error& e)
  {
    std::cout << "Recieve Bet Error : " << e.what() << std::endl;
    return false;
  }

  return true;
}

}

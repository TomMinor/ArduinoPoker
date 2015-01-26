#include "comms/dealerIO.h"
#include "comms/SerialPort.h"

//@todo More indepth error checks

namespace Comms
{

///
/// \brief The PacketType enum values store all the information needed for each packet type,
/// the left nibble stores the type and the right nibble stores the payload size.
/// They can just be sent directly along the serial port and the Player should be capable of
/// understanding what data they contain.
///
enum PacketHeader
{                   /*  Type | Payload (Number of bytes to send/expect) */
  P_CARDS           = 0x10 | 0x01,
  P_NAME            = 0x20 | 0x0F,
  P_MONEY           = 0x30 | 0x02,
  P_LIMITS          = 0x40 | 0x04,
  P_RESETPLAYER     = 0x50 | 0x00,
  P_REQUESTBET      = 0x60 | 0x01,
  P_RECIEVEWINNINGS = 0x70 | 0x02,
  P_BETAMOUNT       = 0x80 | 0x01,
  P_RESETCARD       = 0x90 | 0x00,
};

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

        data.push_back( P_MONEY );
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
        data.push_back( P_CARDS );

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

      /* Header Byte ( Type ) */
      uint8_t right = (uint8_t)_money;
      uint8_t left = (uint8_t)(_money >> 8);

      data.push_back( P_RECIEVEWINNINGS );
      data.push_back( left );
      data.push_back( right );

      /* Payload */
//      data.push_back( left );
//      data.push_back( right );

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
      data.push_back( P_RESETPLAYER );

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
      data.push_back( P_RESETCARD );

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
    uint8_t low = (uint8_t)_min;
    uint8_t high = (uint8_t)(_min >> 8);

    data.push_back( Comms::P_LIMITS );
    data.push_back( high );
    data.push_back( low );

    high = (uint8_t)_max;
    low = (uint8_t)(_max >> 8);

    data.push_back( high );
    data.push_back( low );

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
    _data = BYTE_TO_U16(payload[0], payload[1]);

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

    data.push_back( Comms::P_NAME );

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

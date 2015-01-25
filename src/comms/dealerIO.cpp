#include "comms/dealerIO.h"
#include "comms/SerialPort.h"
#include "comms/PacketTypes.h"

//@todo More error checking

namespace Comms
{

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
          SerialPort packet("/dev/ttyACM0");
          BytePayload data;

          //@todo Make this a macro
          /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
          uint8_t right = (uint8_t)_min;
          uint8_t left = (uint8_t)(_min >> 8);

          data.push_back( P_LIMITS );
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

          SerialPort packet("/dev/ttyACM1");
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
          SerialPort packet("/dev/ttyACM1");
          BytePayload data;

          /* Header Byte ( Type ) */
          data.push_back( P_CARDS | 1 );

          data.push_back( _card.getValue() );

          printf("Card value : %X\n", _card.getValue());

          packet.SendData(data);
      }
      catch(boost::system::system_error& e)
      {
          std::cout << "Error " << e.what() << std::endl;
          return false;
      }

      return true;
  }

  bool receiveBet(player _player, uint16_t& _data, unsigned int _timeout)
  {
      try
      {
          SerialPort packet("/dev/ttyACM1");
          BytePayload payload;

          packet.RecieveData(payload);

          if(payload.size() != 2)
          {
              //@todo Make this an exception
              return false;
          }

          //@todo Check the header is correct

          //@todo Make this a macro
          /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
          uint8_t right = (uint8_t)payload[0];
          uint8_t left = (uint8_t)(payload[1] << 8);

          _data = right | left;
      }
      catch(boost::system::system_error& e)
      {
          std::cout << "Error " << e.what() << std::endl;
          return false;
      }

      return true;
  }

  bool receiveName(player _player, std::string &_data, unsigned int _timeout)
  {
      try
      {
          SerialPort packet("/dev/ttyACM1");
          BytePayload payload;

          packet.RecieveData(payload);

          if(payload.size() != 2)
          {
              //@todo Make this an exception
              return false;
          }

          //@todo Check the header is correct

          //@todo Make this a macro
          /* Split into 2 bytes for transfer (player will reconstruct the int from these 2 bytes) */
          uint8_t right = (uint8_t)payload[0];
          uint8_t left = (uint8_t)(payload[1] << 8);

          _data = right | left;
      }
      catch(boost::system::system_error& e)
      {
          std::cout << "Error " << e.what() << std::endl;
          return false;
      }

      return true;
  }

    bool waitForResponse()
    {

    }
}



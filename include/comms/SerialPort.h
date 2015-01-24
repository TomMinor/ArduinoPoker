    #ifndef SERIALPORT_H
#define SERIALPORT_H

#include <map>
#include <string>
#include <stdint.h>
#include <vector>
#include <iostream>

// Introduces a dependency but makes the serial connections cross platform and the code easier.
#include <boost/asio.hpp>

#include "PacketErrors.h"


namespace Comms
{

typedef std::map<unsigned int, std::string> PlayerDevices;
typedef std::vector<uint8_t> BytePayload;

///
/// \brief The SerialPort class
///
class SerialPort
{
public:
    SerialPort(const std::string& _portPath);

    PacketError SendData(const std::vector<uint8_t> _payload);
    PacketError RecieveData(std::vector<uint8_t> _payload);

//    bool sendBetLimits(player _player, unsigned int _min, unsigned int _max);
//    bool sendMoney(player _player, unsigned int _amount);
//    bool sendCard(player _player, PlayingCard _card);
//    bool sendHand(player _player, cardStack _cards);

//    bool recieveBet(player _player, unsigned int &_bet, unsigned int _timeout = 4);
//    bool recieveName(player _player, std::string &_name, unsigned int _timeout = 4);


    ///
    /// \brief DetectSerialDevices Scans /dev for connected serial devices
    /// \return std::map that maps player ID to the device filepath
    ///
    static PlayerDevices DetectSerialDevices();

private:
    ///
    /// \brief m_portpath
    ///
    std::string m_portpath;

    ///
    /// \brief m_dataBuffer
    ///
    char m_dataBuffer[256];

    boost::asio::io_service io;
    boost::asio::serial_port m_serial;
};

}

#endif // SERIALPORT_H

#include "comms/SerialPort.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib>

#include <iostream>

namespace Comms
{

SerialPort::SerialPort(const std::string &_portPath)
   : m_portpath(_portPath), io(), m_serial(io, m_portpath)
{
    using namespace boost::asio;

    // These settings should match up with those of the Arduino
    m_serial.set_option( serial_port_base::character_size(8) );
    m_serial.set_option( serial_port_base::flow_control(serial_port_base::flow_control::none));
    m_serial.set_option( serial_port_base::stop_bits(serial_port_base::stop_bits::one) );
    m_serial.set_option( serial_port_base::parity(serial_port_base::parity::none) );
    m_serial.set_option( serial_port_base::baud_rate(9600) );
}

PlayerDevices SerialPort::DetectSerialDevices()
{
    DIR *dir = opendir("/dev");
    struct dirent *dp;
    /* Map player ID to serial device path*/
    PlayerDevices SerialDevices;

    // Read every subdirectory in /dev
    while((dp=readdir(dir)) != NULL)
    {
        static const std::string pattern = "ttyACM";
        static const unsigned int patternLength = pattern.length();
        std::string subdirectory = dp->d_name;

        /* Check if the subdirectory matches the "ttyACM*" pattern */
        if(subdirectory.find(pattern.c_str(), 0, patternLength) != std::string::npos)
        {
            int id = atoi( subdirectory.erase(0, patternLength).c_str() );
            SerialDevices[id] = std::string("/dev/") + std::string(dp->d_name);
        }
    }

    closedir(dir);

    return SerialDevices;
}

void SerialPort::SendData(const std::vector<uint8_t> _payload)
{
    // Ignore the first byte in the payload, it is the header
    const uint8_t payloadSize = _payload.size() - 1;

    /* If we recieve no data then treat it as a successful send */
    if(payloadSize < 0)
    {
        return;
    }

    size_t sentBytes = 0;

    /* Send header (assume the first byte in the payload is the header)
     * The header contains the type of data and the amount of bytes being sent as the payload
     */
    sentBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data(), 1) );

    // Assume we couldn't connect if we can't send any bytes
    if(sentBytes < 1)
    {
      throw boost::system::system_error(boost::asio::error::timed_out, "Packet timeout");
    }

    // Removed the 'verification' byte, should add a checksum at the end instead
/*    static char serialBuffer[15] = {0};
    sentBytes = boost::asio::read( m_serial, boost::asio::buffer( &serialBuffer, 1) );
    if(serialBuffer[0] == 0)
    {
      throw boost::system::system_error(boost::asio::error::fault, "Device was not ready");
    }
*/

    /* Send payload bytes */
    sentBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data() + 1, payloadSize  ) );

    /* If we didn't send enough bytes then the data is corrupt  */
    if(sentBytes < payloadSize)
    {
      throw boost::system::system_error(boost::asio::error::fault, "Corrupt packet");
    }

    /* @todo Add checksum */
}

void SerialPort::RecieveData(std::vector<uint8_t> &_payload)
{
  size_t recievedBytes = 0;

  static char serialBuffer[18] = {0}; //Enough space for the maximum amount of bytes we can send (15), + ~25% space just to be safe

  // Read
  recievedBytes = boost::asio::read( m_serial, boost::asio::buffer( &serialBuffer, 1) );

  // Assume we couldn't connect if we can't send any bytes
  if(recievedBytes  < 1)
  {
    throw boost::system::system_error(boost::asio::error::timed_out, "Packet timeout");
  }
  /* Disabled the confirmation byte, plan to add a checksum */
//  else
//  {
//    uint8_t confirmation = 1;
//    /* Send confirmation */
//    recievedBytes  = boost::asio::write( m_serial, boost::asio::buffer(&confirmation, 1) );
//  }

  const uint8_t header = serialBuffer[0];
  const uint8_t payloadSize = (header & 0x0F); // Right nibble stores the payload size, extract it

  // Read the payload
  recievedBytes  = boost::asio::read( m_serial, boost::asio::buffer( &serialBuffer, payloadSize));

  // Fill up the payload array.
  for(unsigned int i=0; i < recievedBytes; i++)
  {
    _payload.push_back(serialBuffer[i]);
  }

  // We didn't get enough packets.
  if(recievedBytes < payloadSize)
  {
    throw boost::system::system_error(boost::asio::error::fault, "Corrupt packet");
  }
}

}


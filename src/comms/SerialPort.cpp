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
   : io(), m_portpath(_portPath), m_serial(io, m_portpath)
{
    using namespace boost::asio;

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


/*
 * - Send header
 * - Wait for response
 *   + If failed, E_TIMEOUT
 * - Send payload
 * - Wait for checksum
 *   + If failed, E_TIMEOUT
 * - Compare checksum
 *   + If failed, E_CORRUPT
 */

PacketError SerialPort::SendData(const std::vector<uint8_t> _payload)
{
    const uint8_t payloadSize = _payload.size() - 1;

    /* If we recieve no data then treat it as a successful send */
//    if(payloadSize < 0)
//    {
//        return E_SUCCESS;
//    }

    size_t sentBytes = 0;

    /* Send header (assume the first byte in the payload is the header)
     * The header contains the type of data and the amount of bytes being sent as the payload
     */
    sentBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data(), 1) );

    // Assume we couldn't connect if we can't send any bytes
//    if(sentBytes < 1)
//    {
//        return E_TIMEOUT;
//    }

    //@todo Timeout

    static char serialBuffer[15] = {0};
    sentBytes = boost::asio::read( m_serial, boost::asio::buffer( &serialBuffer, 1) );

    /* Send payload bytes */
    sentBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data() + 1, payloadSize  ) );

    /* If we didn't send enough bytes then the data is corrupt  */
//    if(sentBytes < _payload.size()  )
//    {
//        return E_CORRUPT;
//    }

    /* @todo Add checksum */

    return E_SUCCESS;
}

PacketError SerialPort::RecieveData(std::vector<uint8_t> _payload)
{
    /* Send payload */
    size_t numOfBytes;

    if(numOfBytes < _payload.size())
    {
        return E_CORRUPT;
    }

    std::cout << numOfBytes << '\n';

    /* @todo Add checksum */

    return E_SUCCESS;
}

}

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
    /* Send payload */
    size_t numOfBytes;
    // Send header
    numOfBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data(), 1) );

//    if(numOfBytes == 1)
//    {
//        return E_CORRUPT;
//    }

        //@todo Timeout
        static char serialBuffer[15] = {0};
    numOfBytes = boost::asio::read( m_serial, boost::asio::buffer( &serialBuffer, 1) );

    numOfBytes = boost::asio::write( m_serial, boost::asio::buffer( _payload.data() + 1, _payload.size() - 1  ) );
//    if(numOfBytes < _payload.size())
//    {
//        return E_CORRUPT;
//    }

//    std::cout << "Sent : " << numOfBytes << '\n';

//    numOfBytes = boost::asio::read( m_serial, boost::asio::buffer( &buffer, _payload.size()) );

//    std::cout << "Recieved : " ;
//    for(int i=0; i < _payload.size(); i++)
//    {
//        std::cout << (int)buffer[i] << " ";
//    }
//    std::cout << ", " << numOfBytes << '\n';

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
    /* Read up to 128 bytes */
//    int numOfBytes = read(fd, m_dataBuffer, 128);

//    /* print how many bytes read */
//    printf("%i bytes got read...\n", numOfBytes);

//    /* print what's in the buffer */
//    printf("Buffer contains...\n%s\n", m_dataBuffer)  ;

    return E_SUCCESS;
}

}

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


SerialConnection::SerialConnection(const std::string &_path)
{
    /* Open the file descriptor in non-blocking mode */
    std::string path = std::string("/dev/") + _path;
    int fd;
    if( (fd = open(path.c_str(), O_RDWR | O_NOCTTY)) == -1)
    {
        fprintf(stderr, "Cannot open %s\n", path.c_str());
        m_fd = fd;
        return;
    }

    /* Set up the control structure */
    struct termios toptions;

    /* Get currently set options for the tty */
    tcgetattr(fd, &toptions);

    /* Set custom options */

    /* 9600 baud */
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);

    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ( ~PARENB | ~CSTOPB | ~CSIZE );
    toptions.c_cflag |= CS8;

    /* no hardware flow control */
    toptions.c_cflag &= ~CRTSCTS;

    /* enable receiver, ignore status lines */
    toptions.c_cflag |= CREAD | CLOCAL;

    /* disable input/output flow control, disable restart chars */
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

    /* disable canonical input, disable echo,
         * disable visually erase chars,
         * disable terminal-generated signals */
    toptions.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /* disable output processing */
    toptions.c_oflag &= ~OPOST;

    /* wait for 24 characters to come in before read returns */
    toptions.c_cc[VMIN] = 12;

    /* no minimum time to wait before read returns */
    toptions.c_cc[VTIME] = 0;

    /* commit the options */
    tcsetattr(fd, TCSANOW, &toptions);

    /* Wait for the Arduino to reset */
    // usleep(1000 * 1000);

    /* Flush anything already in the serial buffer */
    tcflush(fd, TCIFLUSH);

    m_fd = fd;
}

SerialConnection::~SerialConnection()
{
    if(isOpen())
    {
        close(m_fd);
    }
}


SerialPort::SerialPort(const std::string &_portPath)
    : m_portpath(_portPath)
{
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
            SerialDevices[id] = std::string(dp->d_name);
        }
    }

    closedir(dir);

    return SerialDevices;
}


PacketError SerialPort::SendData(const std::vector<uint8_t> _payload)
{
    SerialConnection device(m_portpath);

    if(!device.isOpen())
    {
        return E_DISCONNECTED;
    }

    /* Send payload */
    size_t numOfBytes;
    numOfBytes = write(device.getFileDescriptor(), _payload.data(), _payload.size());

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

PacketError SerialPort::RecieveData(std::vector<uint8_t> _payload)
{
    SerialConnection device(m_portpath);

    if(!device.isOpen())
    {
        return E_DISCONNECTED;
    }

    /* Send payload */
    size_t numOfBytes = read(device.getFileDescriptor(), m_dataBuffer, 128);
//    if(numOfBytes < _payload.size())
//    {
//        return E_CORRUPT;
//    }

    std::cout << numOfBytes << '\n';

    /* @todo Add checksum */

    /* Read up to 128 bytes */
//    int numOfBytes = read(fd, m_dataBuffer, 128);

//    /* print how many bytes read */
//    printf("%i bytes got read...\n", numOfBytes);

//    /* print what's in the buffer */
    printf("Buffer contains...\n%s\n", m_dataBuffer)  ;

    return E_SUCCESS;
}

}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#include "comms/SerialPort.h"

int main()
{
    Comms::PlayerDevices players = Comms::SerialPort::DetectSerialDevices();
    if(players.size() > 0)
    {
        std::string portname = players.begin()->second;

        Comms::BytePayload data;
        data.push_back(0);
        data.push_back(1);
        data.push_back(2);
        Comms::SerialPort test(portname);
        test.SendData(data);
    }
}

///* My Arduino is on /dev/ttyACM0 */
//const char *portname = "/dev/ttyACM0";
//char buf[256];

//int main()
//{
//    int fd;

//    /* Open the file descriptor in non-blocking mode */
//    fd = open(portname, O_RDWR | O_NOCTTY);

//    /* Set up the control structure */
//    struct termios toptions;

//    /* Get currently set options for the tty */
//    tcgetattr(fd, &toptions);

//    /* Set custom options */
//    /* 9600 baud */
//    cfsetispeed(&toptions, B9600);
//    cfsetospeed(&toptions, B9600);

//    /* 8 bits, no parity, no stop bits */
//    toptions.c_cflag &= ~PARENB;
//    toptions.c_cflag &= ~CSTOPB;
//    toptions.c_cflag &= ~CSIZE;
//    toptions.c_cflag |= CS8;

//    /* no hardware flow control */
//    toptions.c_cflag &= ~CRTSCTS;

//    /* enable receiver, ignore status lines */
//    toptions.c_cflag |= CREAD | CLOCAL;

//    /* disable input/output flow control, disable restart chars */
//    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

//    /* disable canonical input, disable echo,
//     * disable visually erase chars,
//     * disable terminal-generated signals */
//    toptions.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

//    /* disable output processing */
//    toptions.c_oflag &= ~OPOST;

//    /* wait for 24 characters to come in before read returns */
//    toptions.c_cc[VMIN] = 12;

//    /* no minimum time to wait before read returns */
//    toptions.c_cc[VTIME] = 0;

//    /* commit the options */
//    tcsetattr(fd, TCSANOW, &toptions);

//    /* Wait for the Arduino to reset */
////    usleep(1000*1000);

//    /* Flush anything already in the serial buffer */
//    tcflush(fd, TCIFLUSH);

//    /* read up to 128 bytes from the fd */
//    int n = read(fd, buf, 128);

//    /* print how many bytes read */
//    printf("%i bytes got read...\n", n);

//    /* print what's in the buffer */
//    printf("Buffer contains...\n%s\n", buf);

//    return 0;
//}

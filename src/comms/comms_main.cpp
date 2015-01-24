#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

#include "comms/SerialPort.h"

// Introduces a dependency but makes the serial connections cross platform and the code easier.
#include <boost/asio.hpp>
using namespace::boost::asio;
#include <iostream>

const char* PORT="/dev/ttyACM0";

int main()
{
  // what baud rate do we communicate at
  serial_port_base::baud_rate BAUD(9600);
  // how big is each "packet" of data (default is 8 bits)
  serial_port_base::character_size PACKETSIZE( 8 );

  // what flow control is used (default is none)
  serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );

  // what parity is used (default is none)
  serial_port_base::parity PARITY( serial_port_base::parity::none );

  // how many stop bits are used (default is one)
  serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

  io_service io;

  serial_port port(io, PORT);

  port.set_option( BAUD );
  port.set_option( PACKETSIZE );
  port.set_option( FLOW );
  port.set_option( PARITY );
  port.set_option( STOP );

  unsigned char command[1] = {0};

  char input;
  std::cin >> input;

  while(input >= 0)
  {
    command[0] = input;

    write( port, buffer( command, 1 ) );

    std::cin >> input;
  }

  return 0;
}

//int main()
//{
//    Comms::PlayerDevices players = Comms::SerialPort::DetectSerialDevices();
//    if(players.size() > 0)
//    {
//        std::string portname = players.begin()->second;

//        Comms::BytePayload data;
//        data.push_back(0);
//        data.push_back(1);
//        data.push_back(2);

//        Comms::SerialPort test(portname);
//        test.SendData(data);
//    }
//}

/// \file SerialPort.h
/// \brief encapsulates writing/reading data to/from an Arduino over the serial port
/// \author Tom Minor
/// \version 1.0
/// \date 26/1/15 Submitted for assignment deadline
///
/// \todo
/// Update at least SerialPort::RecieveData to be asynchronous/non-blocking.
/// Adding a timeout would also be good.
///

#ifndef SERIALPORT_H
#define SERIALPORT_H

/* Introduces a dependency but makes the serial connections cross platform. */
#include <boost/asio.hpp>

#include "dealerIO.h"

namespace Comms
{

///
/// \brief BytePayload represents a byte sequence.
///
typedef std::vector<uint8_t> BytePayload;

///
/// \brief The SerialPort class encapsulates sending and recieving data from a player.
/// It assumes the protocol is to open a transmission by sending a header byte containing
/// both the type (left nibble) and the size of the byte payload (right nibble), any bytes
/// sent after the header are considered the payload.
///
class SerialPort
{
public:

  ///
  /// \brief SerialPort ctor initializes the serial port.
  /// \param _portPath is the path to the device we want to talk to.
  ///
  SerialPort(const std::string& _portPath);

  ///
  /// \brief SendData sends a header followed by an arbritary payload.
  /// \param _payload is a sequence of byte data to be sent over the serial connection.
  ///
  void SendData(const std::vector<uint8_t> _payload);

  ///
  /// \brief RecieveData
  /// \param _payload
  ///
  void RecieveData(std::vector<uint8_t> &_payload);

  ///
  /// \brief DetectSerialDevices Scans /dev for connected serial devices
  /// \return std::map that maps player ID to the device filepath
  ///
  static PlayerDevices DetectSerialDevices();

private:
  ///
  /// \brief m_portpath is the path to the serial device, e.g. "/dev/ttyACM0"
  ///
  std::string m_portpath;

  ///
  /// \brief io is used by m_serial.
  ///
  boost::asio::io_service io;

  ///
  /// \brief m_serial is a Boost serial port object, used to write/read data. It is initialized in the constructor.
  ///
  boost::asio::serial_port m_serial;
};

}

#endif // SERIALPORT_H

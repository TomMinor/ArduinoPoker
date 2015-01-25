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
#include "dealerIO.h"

namespace Comms
{

///
/// \brief BytePayload
///
typedef std::vector<uint8_t> BytePayload;

///
/// \brief The SerialPort class
///
class SerialPort
{
public:

  ///
  /// \brief SerialPort
  /// \param _portPath
  ///
  SerialPort(const std::string& _portPath);

  ///
  /// \brief SendData
  /// \param _payload
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
  /// \brief m_portpath
  ///
  std::string m_portpath;

  ///
  /// \brief io
  ///
  boost::asio::io_service io;

  ///
  /// \brief m_serial
  ///
  boost::asio::serial_port m_serial;
};

}

#endif // SERIALPORT_H

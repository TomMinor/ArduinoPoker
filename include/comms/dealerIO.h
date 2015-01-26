///     \file dealerIO.h
/// \brief An interface for the Dealer team to communicate with the Arduino players,
/// provides utility functions for all the data that needs to be sent/recieved.
/// \author Tom Minor
/// \version 1.0
/// \date 26/1/15 Submitted for assignment deadline
///
/// \todo
/// Error checking could be tightened up in some areas.
///

#ifndef DEALERIO_H
#define DEALERIO_H

#include <stdlib.h>
#include <stdint.h>
#include <map>
#include <string>

#include "dealer/player.h"

namespace Comms
{

///
/// \brief PlayerDevices Maps a player ID onto it's device path string.
///
typedef std::map<unsigned int, std::string> PlayerDevices;

///
/// \brief setPlayer Initialises the player connected to _port with the data from _cards and _money.
/// \param _port is the serial device path.
/// \param _cards stores all the cards to send to the player.
/// \param _money is the value that will be sent to the player.
/// \return  true if successfully sent, else false.
///
bool setPlayer(const std::string& _port, const std::vector<PlayingCard>& _cards, uint16_t _money);

///
/// \brief sendMoney Sets the money of the player on _port.
/// \param _port is the serial device path.
/// \param _amount is the amount that will be added to the player's money.
/// \return  true if successfully sent, else false.
///
bool sendMoney(const std::string& _port, uint16_t _amount);

///
/// \brief sendCard Sends a card to the player on _port.
/// \param _port is the serial device path.
/// \param _card is the card that will be sent to the player.
/// \return true if successfully sent, else false.
///
bool sendCard(const std::string& _port, PlayingCard _card);

///
/// \brief sendWin Tells the player on _port that they've win and sends a money reward.
/// \param _port is the serial device path.
/// \param _money is the money reward that will be sent to the player.
/// \return true if successfully sent, else false.
///
bool sendWin(const std::string& _port, uint16_t _money);

///
/// \brief sendResetPlayer Resets the player on _port.
/// \param _port is the serial device path.
/// \return true if successfully sent, else false.
///
bool sendResetPlayer(const std::string& _port);

///
/// \brief sendResetCards Resets the cards of the player on _port.
/// \param _port is the serial device path.
/// \return true if successfully sent, else false.
///
bool sendResetCards(const std::string& _port);

///
/// \brief receiveBet Asks the player on _port to input a bet and blocks until the result is recieved.
/// \param _port is the serial device path.
/// \param _data will be populated with a value if recieve was successful.
/// \param _min is the minimum bet limit that will be sent to the player.
/// \param _max is the maximum bet limit that will be sent to the player.
/// \param _timeout is unused.
/// \return true if successfully sent, else false.
///
bool receiveBet(const std::string& _port, uint16_t &_data, uint16_t _min, uint16_t  _max, unsigned int _timeout = 4);

///
/// \brief receiveName Asks the player on _port to input a name (max 15 bytes long) and blocks until the result is recieved.
/// \param _port is the serial device path.
/// \param _data is the name string that will be populated with values when the player sends the requested data
/// \param _timeout is unused.
/// \return true if successfully sent, else false.
///
bool receiveName(const std::string& _port, std::string &_data, unsigned int _timeout = 4);

}

#endif // DEALERIO_H

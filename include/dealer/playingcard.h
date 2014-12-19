#ifndef __DEALER_PLAYINGCARD_H_
#define __DEALER_PLAYINGCARD_H_

#include <string>
#include <stdint.h>

#include "../card.h"

/*!
 * \brief card_t Represents a card with a single byte
 */
typedef uint8_t card_t;

/*!
 * \brief RankLookup A lookup for table for the rank's string representation
 */
extern const std::string RankLookup[12];

/*!
 * \brief SuitLookup  A lookup for table for the suit's string representation
 */
extern const std::string SuitLookup[4];

/*!
 * \brief The PlayingCard class encapsulates the single byte card representation defined in "card.h".
 * It overloads various operators for ease of playing card comparison and provides string lookup tables for
 * string representations of the card.
 */
class PlayingCard
{
public:
  /*!
   * \brief PlayingCard
   * \param _rank
   * \param _suit
   */
  PlayingCard(Rank::Value _rank, Suit::Value _suit);

  /*!
   * \brief IsRank
   * \param _rank
   * \return True if _rank equals the playing card's rank
   */
  bool inline IsRank(Rank::Value _rank) const;

  /*!
   * \brief IsSuit
   * \param _suit
   * \return True if _rank equals the playing card's suit
   */
  bool inline IsSuit(Suit::Value _suit) const;

  /*!
   * \brief RankString
   * \return The string representation of the playing card's rank.
   */
  std::string inline RankString() const;

  /*!
   * \brief SuitString
   * \return The string representation of the playing card's suit.
   */
  std::string inline SuitString() const;

  /*!
   * \brief operator <<
   * \param _stream
   * \param _card
   * \return
   */
  friend std::ostream& operator<<(std::ostream& _stream, const PlayingCard& _card);

private:
  /*!
   * \brief m_value Stores the suit and rank of the playing card in a single byte.
   */
  card_t m_value;
};

#endif

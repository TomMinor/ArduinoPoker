#include <assert.h>

#include "dealer/playingcard.h"

const std::string RankLookup[] = {
  "Ace",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "Jack",
  "Queen",
  "King"
};

const std::string SuitLookup[] = {
  "Diamond",
  "Heart",
  "Club",
  "Spade"
};

PlayingCard::PlayingCard(Rank::Value _rank, Suit::Value _suit)
{
  m_value = _rank | _suit;
}

int PlayingCard::getSuit() const
{
  if( ISDIAMOND(m_value))    { return 0; }
  else if( ISHEART(m_value)) { return 1; }
  else if( ISCLUB(m_value))  { return 2; }
  else if( ISSPADE(m_value)) { return 3; }

  assert( !"Invalid suit" );
}

bool PlayingCard::operator==(const PlayingCard& _card)
{
  bool sameRank = (RANKOF(m_value) == RANKOF(_card.m_value));
  bool sameSuit = (getSuit() == _card.getSuit());

  return sameRank && sameSuit;
}

bool PlayingCard::operator!=(const PlayingCard& _card)
{
  return !(*this == _card);
}

std::ostream& operator<<(std::ostream& _stream, const PlayingCard& _card)
{
  _stream << _card.RankString() << std::string(" of ") << _card.SuitString() << std::string("'s");
  return _stream;
}

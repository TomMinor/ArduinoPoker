#include <assert.h>
#include <iostream>

#include "dealer/playingcard.h"

const std::string RankLookup[] = {
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
  "King",
  "Ace"
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


// Gotta fix these

bool PlayingCard::IsRank(Rank::Value _rank) const
{
    return RANKOF(m_value) == _rank;
}

// Gotta fix these
bool PlayingCard::IsSuit(Suit::Value _suit) const
{
  if(m_value & _suit)
    return true;

  else
    return false;
}

std::string PlayingCard::RankString() const
{
  // We subtract 1 to match the array index starting at 0
  return RankLookup[ RANKOF(m_value)-1 ];
}

std::string PlayingCard::SuitString() const
{
  return SuitLookup[getSuitID()];
}

int PlayingCard::getSuitID() const
{
  if( ISDIAMOND(m_value))    { return 0; }
  else if( ISHEART(m_value)) { return 1; }
  else if( ISCLUB(m_value))  { return 2; }
  else if( ISSPADE(m_value)) { return 3; }
  else if( SUITOF(m_value) & ( 0x30|0x50|0x60|0x70)){std::cout<<"-----------\nwrong suit!!!\n--------\n";}

  assert( !"Invalid suit" );
}

int PlayingCard::getRank()const
{
  return RANKOF(m_value);
}
int PlayingCard::getSuit()const
{
  return SUITOF(m_value);
}


bool PlayingCard::operator==(const PlayingCard& _card)
{
  bool sameRank = (RANKOF(m_value) == RANKOF(_card.m_value));
  bool sameSuit = (getSuitID() == _card.getSuitID());

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

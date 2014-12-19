#include <assert.h>

#include "dealer/card.h"

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

bool PlayingCard::IsRank(Rank::Value _rank) const
{
  return RANKOF(_rank);
}

bool PlayingCard::IsSuit(Suit::Value _suit) const
{
  return RANKOF(_suit);
}

std::string PlayingCard::RankString() const
{
  return RankLookup[ RANKOF(m_value)-1 ];
}

std::string PlayingCard::SuitString() const
{
    if( ISDIAMOND(m_value))    { return SuitLookup[0]; }
    else if( ISCLUB(m_value))  { return SuitLookup[1]; }
    else if( ISSPADE(m_value)) { return SuitLookup[2]; }
    else if( ISHEART(m_value)) { return SuitLookup[3]; }

    assert( !"Invalid suit" );
}

std::ostream& operator<<(std::ostream& _stream, const PlayingCard& _card)
{
  _stream << _card.RankString() << std::string(" of ") << _card.SuitString() << std::string("'s");
  return _stream;
}

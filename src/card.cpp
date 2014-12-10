#include "include/card.h"

#define FLIPSPEED 0.2
#define CARDWIDTH 56

Card::Card(SDL_Renderer *_ren,
           SDL_Texture *_tex,
           SDL_Rect _srcRect,
           SDL_Rect _destRect,
           Orientation _orient,
           Rank _rank,
           Suit _suit) :
            Element(_ren,_tex,_srcRect,_destRect,_orient),
            m_isFlipped(false),
            m_flippedAmount(-1.0f),
            m_rank(_rank),
            m_suit(_suit)
{
}

void Card::update()
{
    if((!m_isFlipped && m_flippedAmount <= -1.0f) || (m_isFlipped && m_flippedAmount >= 1.0f))
    {
        //no need to continue
        Element::update();
        return;
    }

    float amount = m_flippedAmount + (m_isFlipped ? FLIPSPEED : -FLIPSPEED);
    m_flippedAmount = std::max(-1.0f, std::min(amount, 1.0f));

    if (m_flippedAmount > 0.0f)
    {
        //change to the flipped part of the sheet
        m_srcRect.x = 0;
        m_srcRect.y = m_srcRect.h*4;
    }
    else
    {
        m_srcRect.x = CARDWIDTH*static_cast<int>(m_rank);
        m_srcRect.y = m_srcRect.h*static_cast<int>(m_suit);
    }

    float xScale = (float)fabs(sin(m_flippedAmount*M_PI*0.5f));
    std::cout<<"flippedAmount: "<<m_flippedAmount<<" xscale: "<<xScale<<"\n";
    m_destRect.w = static_cast<int>(CARDWIDTH * xScale);
    m_xOffset = CARDWIDTH/2 - static_cast<int>(CARDWIDTH * xScale * 0.5);

    Element::update();
}

void Card::draw()
{
    m_destRect.x += m_xOffset;
    Element::draw();
    m_destRect.x -= m_xOffset;
}

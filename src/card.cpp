#include "include/card.h"

#define FLIPSPEED 0.2
#define CARDWIDTH 56

Card::Card(SDL_Renderer *_ren,
           SDL_Texture *_tex,
<<<<<<< HEAD
           const SDL_Rect &_srcRect,
           const SDL_Rect &_destRect,
           const Orientation &_orient,
           const CardType &_type) :
            Element(_ren,_tex,_srcRect,_destRect,_orient),
            m_isFlipped(false),
            m_flippedAmount(-1.0f),
            m_rank(_type.rank),
            m_suit(_type.suit),
            m_xOffset(0),
            m_shouldBurn(false),
            m_burned(false),
            m_burnLevel(0)
=======
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
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
{
}

void Card::update()
{
<<<<<<< HEAD
    if(m_shouldBurn)
    {
        if(m_isFlipped && m_flippedAmount >= 1.0f)//if fully flipped
        {
            m_xOffset=0;
            if(m_burnLevel < 24)
            {
                m_burnLevel++;
                m_srcRect.x=(m_burnLevel/2)*56;
            }
            else
            {
                m_burned=true;
            }
            return;
        }
        else
        {
            setFlipped(true);
            continueFlip();
        }
    }

    else if((!m_isFlipped && m_flippedAmount <= -1.0f) || (m_isFlipped && m_flippedAmount >= 1.0f))
    // if it's fully flipped or fully upright
=======
    if((!m_isFlipped && m_flippedAmount <= -1.0f) || (m_isFlipped && m_flippedAmount >= 1.0f))
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
    {
        //no need to continue
        Element::update();
        return;
    }

<<<<<<< HEAD
    else
    {
        continueFlip();
    }

    Element::update();
}

void Card::continueFlip()
{
=======
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
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
<<<<<<< HEAD
    //std::cout<<"flippedAmount: "<<m_flippedAmount<<" xscale: "<<xScale<<"\n";
    m_destRect.w = static_cast<int>(CARDWIDTH * xScale);
    m_xOffset = CARDWIDTH/2 - static_cast<int>(CARDWIDTH * xScale * 0.5);
=======
    std::cout<<"flippedAmount: "<<m_flippedAmount<<" xscale: "<<xScale<<"\n";
    m_destRect.w = static_cast<int>(CARDWIDTH * xScale);
    m_xOffset = CARDWIDTH/2 - static_cast<int>(CARDWIDTH * xScale * 0.5);

    Element::update();
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
}

void Card::draw()
{
<<<<<<< HEAD
    if(!m_burned)
    {
        m_destRect.x += m_xOffset;
        Element::draw();
        m_destRect.x -= m_xOffset;
    }
=======
    m_destRect.x += m_xOffset;
    Element::draw();
    m_destRect.x -= m_xOffset;
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
}

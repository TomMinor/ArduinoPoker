#include "include/card.h"
//ignore this line, just adding so git will actually notice the fucking changes

#define FLIPSPEED 0.2
#define CARDWIDTH 56

Card::Card(SDL_Renderer *_ren,
           SDL_Texture *_tex,
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
{
}

void Card::update()
{
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
    {
        //no need to continue
        Element::update();
        return;
    }

    else
    {
        continueFlip();
    }

    Element::update();
}

void Card::continueFlip()
{
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
    //std::cout<<"flippedAmount: "<<m_flippedAmount<<" xscale: "<<xScale<<"\n";
    m_destRect.w = static_cast<int>(CARDWIDTH * xScale);
    m_xOffset = CARDWIDTH/2 - static_cast<int>(CARDWIDTH * xScale * 0.5);
}

void Card::draw()
{
    if(!m_burned)
    {
        m_destRect.x += m_xOffset;
        Element::draw();
        m_destRect.x -= m_xOffset;
    }
}

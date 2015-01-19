#include "include/gui_card.h"

#define FLIPSPEED 0.2
#define CARDWIDTH 56

#define FullyFlipped    ( m_isFlipped && m_flippedAmount >= 1.0f )
#define FullyUnflipped  (!m_isFlipped && m_flippedAmount <= -1.0f)

GUI_Card::GUI_Card(SDL_Renderer *_ren,
           SDL_Texture *_tex,
           const SDL_Rect &_srcRect,
           const SDL_Rect &_destRect,
           const GUI_Orientation &_orient,
           const SDL_Point &_origin,
           const PlayingCard &_card) :
            GUI_Element(_ren,_tex,_srcRect,_destRect,_orient,_origin),
            m_isFlipped(false),
            m_flippedAmount(-1.0f),
            m_cardType(_card),
            m_shouldBurn(false),
            m_burnLevel(0)
{
}

void GUI_Card::update()
{
    //Check 1: should the card burn?
    if(m_shouldBurn)
    {
        if(!FullyFlipped)
        {
            setFlipped(true);
            m_xOffset = continueFlip();
            //return;
        }
        else
        {
            if(m_burnLevel < 24)
            {
                ++m_burnLevel;
                m_srcRect.x=(m_burnLevel/2)*56;
            }
            else
            {
                m_shouldKillNow=true;
            }
            return;
        }
    }
    //Check 2: is the card midway between flips?
    else if(!FullyFlipped || !FullyUnflipped)
    {
        m_xOffset = continueFlip();
    }

    GUI_Element::update();

    m_destRect.x = m_origin.x + m_xOffset;
}

int GUI_Card::continueFlip()
{
    float amount = m_flippedAmount + (m_isFlipped ? FLIPSPEED : -FLIPSPEED);
    m_flippedAmount = std::max(-1.0f, std::min(amount, 1.0f));//clamp

    if (m_flippedAmount > 0.0f)
    {
        //change to the flipped part of the sheet
        m_srcRect.x = 0;
        m_srcRect.y = m_srcRect.h*4;
    }
    else
    {
        m_srcRect.x = (m_cardType.getRank()%13)*CARDWIDTH;
        m_srcRect.y = m_cardType.getSuit()*m_srcRect.h;
    }

    float xScale = (float)fabs(sin(m_flippedAmount*M_PI*0.5f));
    //std::cout<<"flippedAmount: "<<m_flippedAmount<<" xscale: "<<xScale<<"\n";
    m_destRect.w = static_cast<int>(CARDWIDTH * xScale);

    return -m_destRect.w / 2;
}

void GUI_Card::setFlipped(const bool &_isFlipped, const bool &_instantly)
{
    m_isFlipped = _isFlipped;
    if (!_instantly)
    {
        return;
    }

    m_flippedAmount = _isFlipped ? 1.0f : -1.0f;
    continueFlip();
}

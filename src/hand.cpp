#include "include/hand.h"

Hand::Hand(const std::vector<Card*> &_cards, const Orientation &_orient) :
    m_cards(_cards),
    m_orient(_orient)
{
    if (_cards.empty())
    {
        std::cerr<<"Attempting to create empty hand!\n";
    }
    SDL_Point origin = {0,0};
    m_origin = origin;
    setPos(origin);
}

void Hand::setFlipped(const bool &_isFlipped)
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->setFlipped(_isFlipped);
    }
}

void Hand::kill()
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->kill();
    }
}

void Hand::setPos(const SDL_Point &_p)
{
    m_origin = _p;
    SDL_Point current = _p;
    unsigned int gap = (m_orient == BOTTOM || m_orient == TOP) ? m_cards[0]->getWidth() : m_cards[0]->getHeight();

    if (m_orient == BOTTOM || m_orient == TOP)
    {
        current.x -= gap * m_cards.size() / 2;
    }
    else
    {
        current.y -= gap * m_cards.size() / 2;
    }

    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->setPos(current);
        if (m_orient == BOTTOM || m_orient == TOP)
        {
            current.x += gap;
        }
        else
        {
            current.y += gap;
        }
    }
}

void Hand::moveTo(const SDL_Point &_p)
{
    std::cout<<"moving hand to: ("<<_p.x<<", "<<_p.y<<")\n";
    m_origin = _p;
    SDL_Point current = _p;

    if (m_orient == BOTTOM || m_orient == TOP)
    {
        current.x -= getWidth() / 2;
        std::cout<<"incrementing x by: "<<-getWidth() / 2<<"\n";
    }
    else
    {
        current.y += getHeight() / 2;
        std::cout<<"incrementing y by: "<<(int)(getHeight() / 2)<<"\n";
    }

    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->moveTo(current);
        std::cout<<"moving a card to: ("<<current.x<<", "<<current.y<<")\n";
        if (m_orient == BOTTOM || m_orient == TOP)
        {
            current.x += (m_orient == BOTTOM) ? (*it)->getWidth() : -(*it)->getWidth();
        }
        else
        {
            current.y += (m_orient == RIGHT) ? (*it)->getHeight() : -(*it)->getHeight();
        }
    }
}

void Hand::burn()
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->burn();
    }
}

unsigned int Hand::getHeight()
{
    if (m_orient == BOTTOM || m_orient == TOP)
    {
//        return m_cards[0]->getHeight();
        return 76;
    }
    else
    {
//        unsigned int total = 0;
//        for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
//        {
//            total += (*it)->getHeight();
//        }
//        return total;
        return m_cards.size() * 56;
    }
}

unsigned int Hand::getWidth()
{
    if (m_orient == LEFT || m_orient == RIGHT)
    {
//        return m_cards[0]->getWidth();
        return 76;
    }
    else
    {
//        unsigned int total = 0;
//        for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
//        {
//            total += (*it)->getWidth();
//        }
//        return total;
        return m_cards.size() * 56;
    }
}

SDL_Point Hand::aligned(const Orientation &_orient)
{
    SDL_Point temp = m_origin;
    int width, height;
    SDL_RenderGetLogicalSize(m_cards[0]->getRenderer(),&width,&height);

    switch (_orient)
    {
        case BOTTOM : temp.y = height - getHeight()/2; break;
        case RIGHT : temp.x = width - getWidth()/2; break;
        case TOP : temp.y = getHeight()/2; break;
        case LEFT : temp.x = getWidth()/2;
    }
    return temp;
}

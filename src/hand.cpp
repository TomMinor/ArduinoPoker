#include "include/hand.h"
//ignore this line, just adding so git will actually notice the fucking changes

Hand::Hand(const SDL_Point &_origin, const std::vector<Card*> &_cards, const Orientation &_orient) :
    m_cards(_cards),
    m_orient(_orient)
{
    SDL_Point current = _origin;
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->setPos(current);
        if (m_orient == BOTTOM || m_orient == TOP)
        {
            current.x += m_orient == BOTTOM ? (*it)->getWidth() : -(*it)->getWidth();
        }
        else
        {
            current.y += m_orient == RIGHT ? (*it)->getHeight() : -(*it)->getHeight();
        }
    }
}

void Hand::setFlipped(const bool &_isFlipped)
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->setFlipped(_isFlipped);
    }
}

void Hand::moveTo(const SDL_Point &_p)
{
    SDL_Point current = _p;
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->moveTo(current);
        if (m_orient == BOTTOM || m_orient == TOP)
        {
            current.x += m_orient == BOTTOM ? (*it)->getWidth() : -(*it)->getWidth();
        }
        else
        {
            current.y += m_orient == RIGHT ? (*it)->getHeight() : -(*it)->getHeight();
        }
    }
}

void Hand::update()
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->update();
    }
}

void Hand::burn()
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->burn();
    }
}

void Hand::draw()
{
    for (std::vector<Card*>::iterator it = m_cards.begin(); it!=m_cards.end(); ++it)
    {
        (*it)->draw();
    }
}

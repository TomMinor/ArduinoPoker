#include "include/gui_listmenu.h"

GUI_ListMenu::GUI_ListMenu(GUI_LabelFormat _format, std::vector<std::string> _strings, SDL_Point _origin) :
    m_currentSelected(0),
    m_origin(_origin)
    //m_marker(Label(_format,std::string(">"),m_origin))
{
    SDL_Point currentPoint;
    currentPoint.x = m_origin.x; //+ m_marker.getWidth();
    currentPoint.y = m_origin.y;

    /*for (std::vector<std::string>::iterator it = _strings.begin(); it != _strings.end(); ++it)
    {
        m_items.push_back(Label(_format,(*it),currentPoint));
        currentPoint.y += m_marker.getHeight();
    }*/
}

void GUI_ListMenu::draw()
{
    //m_marker.draw();

    for (std::vector<GUI_Label>::iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        (*it).draw();
    }
}

void GUI_ListMenu::moveSelection(bool _isUp)
{
    int inc = _isUp ? -1 : +1;
    m_currentSelected = (m_currentSelected + inc)%m_items.size();
    SDL_Point pos = m_origin;
    //pos.y += m_currentSelected*m_marker.getHeight();
    //m_marker.setPos(pos);
}

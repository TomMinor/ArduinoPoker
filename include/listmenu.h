#ifndef LISTMENU_H
#define LISTMENU_H

#include <vector>
#include <string>
#include "label.h"
#include "elementmaker.h"

class ListMenu
{
public:
    ListMenu(LabelFormat _format, std::vector<std::string> _strings, SDL_Point _origin);
    void draw();
    void moveSelection(bool _isUp);
private:
    unsigned int m_currentSelected;
    SDL_Point m_origin;
    std::vector<Label> m_items;
    //Label m_marker;
};

#endif // LISTMENU_H

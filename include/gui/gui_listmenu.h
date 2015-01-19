#ifndef LISTMENU_H
#define LISTMENU_H

#include <vector>
#include <string>
#include "gui_label.h"
#include "gui_elementmaker.h"

class GUI_ListMenu
{
public:
    GUI_ListMenu(GUI_LabelFormat _format, std::vector<std::string> _strings, SDL_Point _origin);
    void draw();
    void moveSelection(bool _isUp);
private:
    unsigned int m_currentSelected;
    SDL_Point m_origin;
    std::vector<GUI_Label> m_items;
    //Label m_marker;
};

#endif // LISTMENU_H

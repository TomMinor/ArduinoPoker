#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "gui_element.h"

namespace GUI
{

//stuff that should be the same for most labels
typedef struct
{
    SDL_Renderer *ren;
    TTF_Font *font;
    SDL_Color colour;
} LabelFormat;

class Label : public Element
{
public:
    Label(SDL_Renderer *_ren,
          SDL_Texture *_tex,
          const SDL_Rect &_rect,
          const Orientation &_orient,
          const SDL_Point &_origin,
          const int &_lifetime);
};

}

#endif // LABEL_H

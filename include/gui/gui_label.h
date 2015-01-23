#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "gui_element.h"

namespace GUI
{

/// \brief This struct contains variables for SDL that will be the same for all labels, which we therefore won't want to send to the constructor individually every time.
typedef struct
{
    SDL_Renderer *ren;
    TTF_Font *font;
    SDL_Color colour;
} LabelFormat;

/// \brief A simple line of text constructed using SDL's TTF library that can be moved around as with other visual elements.
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

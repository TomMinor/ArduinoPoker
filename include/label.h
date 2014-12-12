#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "element.h"

//stuff that should be the same for most labels
typedef struct
{
    SDL_Renderer *ren;
    TTF_Font *font;
    SDL_Color colour;
<<<<<<< HEAD
=======
    unsigned int scale;
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
} LabelFormat;

class Label : public Element
{
public:
    Label(SDL_Renderer *_ren,
          SDL_Texture *_tex,
<<<<<<< HEAD
          const SDL_Rect &_rect,
          const Orientation &_orient);
=======
          SDL_Rect _rect,
          Orientation _orient);
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
};

#endif // LABEL_H

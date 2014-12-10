#ifndef TESTELEMENT_H
#define TESTELEMENT_H

#include "element.h"

class TestElement : public Element
{
public:
    TestElement(SDL_Renderer *_ren,
                SDL_Texture *_tex,
                SDL_Rect _srcRect,
                SDL_Rect _destRect,
                Orientation _orient);
};

#endif // TESTELEMENT_H

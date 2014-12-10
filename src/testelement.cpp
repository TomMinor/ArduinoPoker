#include "include/testelement.h"

TestElement::TestElement(SDL_Renderer *_ren,
                         SDL_Texture *_tex,
                         SDL_Rect _srcRect,
                         SDL_Rect _destRect,
                         Orientation _orient) :
                        Element(_ren,_tex,_srcRect,_destRect,_orient)
{
}

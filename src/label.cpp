#include "include/label.h"

Label::Label(SDL_Renderer *_ren,
             SDL_Texture *_tex,
             const SDL_Rect &_rect,
             const Orientation &_orient) : Element(_ren,_tex,_rect,_rect,_orient)

{
}

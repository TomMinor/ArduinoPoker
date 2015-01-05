#include "include/label.h"

Label::Label(SDL_Renderer *_ren,
             SDL_Texture *_tex,
             const SDL_Rect &_rect,
             const Orientation &_orient,
             const SDL_Point &_origin) : Element(_ren,_tex,_rect,_rect,_orient,_origin)

{
}

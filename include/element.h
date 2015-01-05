#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL.h>
#include <math.h>

typedef enum
{
    BOTTOM,
    RIGHT,
    TOP,
    LEFT
} Orientation;

class Element
{
public:
    Element(SDL_Renderer *_ren,
            SDL_Texture *_tex,
            const SDL_Rect &_srcRect,
            const SDL_Rect &_destRect,
            const Orientation &_orient);
    virtual ~Element() {}
    void setPos(const SDL_Point &_p);//move to this point instantly
    void moveTo(const SDL_Point &_p);//move to this point with cosine interpolation
    virtual void update();
    virtual void draw() const;
    int getHeight() const;
    int getWidth() const;

protected:
    //stuff SDL needs to know
    SDL_Renderer *m_ren;
    SDL_Texture *m_texture;
    SDL_Rect m_srcRect;
    SDL_Rect m_destRect;
    Orientation m_orientation;

    //movement stuff
    SDL_Point m_pointPrev;
    SDL_Point m_pointDest;
    float m_progressAmount;
};

#endif // ELEMENT_H

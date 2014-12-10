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
            SDL_Rect _srcRect,
            SDL_Rect _destRect,
            Orientation _orient);
    void setPos(SDL_Point _p);//move to this point instantly
    void moveTo(SDL_Point _p);//move to this point with cosine interpolation
    virtual void update();
    virtual void draw() const;
    inline int getHeight() const { return m_destRect.h; }
    inline int getWidth()  const { return m_destRect.w; }

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

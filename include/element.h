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
<<<<<<< HEAD
            const SDL_Rect &_srcRect,
            const SDL_Rect &_destRect,
            const Orientation &_orient);
    void setPos(const SDL_Point &_p);//move to this point instantly
    void moveTo(const SDL_Point &_p);//move to this point with cosine interpolation
    virtual void update();
    virtual void draw() const;
    int getHeight() const;
    int getWidth() const;
=======
            SDL_Rect _srcRect,
            SDL_Rect _destRect,
            Orientation _orient);
    void setPos(SDL_Point _p);//move to this point instantly
    void moveTo(SDL_Point _p);//move to this point with cosine interpolation
    virtual void update();
    virtual void draw() const;
    inline int getHeight() const { return m_destRect.h; }
    inline int getWidth()  const { return m_destRect.w; }
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26

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

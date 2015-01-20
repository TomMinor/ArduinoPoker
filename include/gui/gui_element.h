#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL.h>
#include <math.h>

namespace GUI
{

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
            const Orientation &_orient,
            const SDL_Point &_origin,
            const int &_lifetime = 0);
    virtual ~Element();
    void setPos(const SDL_Point &_p);//move to this point instantly
    inline SDL_Point getPos() {return m_origin;}
    void moveTo(const SDL_Point &_p);//move to this point with cosine interpolation
    virtual void update();
    inline void updateRect() {m_destRect.x = m_origin.x - m_destRect.w/2; m_destRect.y = m_origin.y - m_destRect.h/2;}
    void draw() const;
    inline void kill() {m_isImmortal = false; m_shouldKillSoon = true;}
    inline void killNow() {m_shouldKillNow = true;}
    inline bool shouldKillNow() const {return m_shouldKillNow;}
    unsigned int getHeight() const;//the height the element takes up on screen, taking rotation into account
    unsigned int getWidth() const;//the width the element takes up on screen, taking rotation into account
    SDL_Point aligned(const Orientation &_orient);//returns the point the element should move to to align with the specified edge of the screen
    SDL_Point aligned();//pass with no arguments to return the screen centre
    inline SDL_Renderer* getRenderer() {return m_ren;}
    void printRect();

protected:
    //stuff SDL needs to know
    SDL_Renderer *m_ren;
    SDL_Texture *m_texture;
    SDL_Rect m_srcRect;
    SDL_Rect m_destRect;
    Orientation m_orientation;

    //movement stuff
    SDL_Point m_origin;
    SDL_Point m_pointPrev;
    SDL_Point m_pointDest;
    float m_progressAmount;

    bool m_shouldKillSoon;//if true then the object will set shouldKillNow to true when it finishes moving and life runs out
    bool m_shouldKillNow;//if true then the object will be deleted on the next update() of the DealerGUI
    bool m_isImmortal;//if true then the object will never set shouldKillNow to true
    int m_life;//how many cycles the element should last while stationary; set to 0 for it to last infinitely
};

}

#endif // ELEMENT_H

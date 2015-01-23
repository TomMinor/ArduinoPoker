#ifndef ELEMENT_H
#define ELEMENT_H

#include <SDL.h>
#include <math.h>

namespace GUI
{

/// \brief Since the game is meant to be played with the monitor laying flat as a "poker table" with the players sitting around it, this enum is used to specify which
/// side of the "table" a given visual element should be facing.
typedef enum
{
    BOTTOM,
    RIGHT,
    TOP,
    LEFT
} Orientation;

/// \brief The base class for any visual elements on the screen.
///
/// It and any derived classes include functions to move the element to a point on the screen (optionally aligned with an edge of the screen) instantly or with cosine
/// interpolation. The lifetime of the element (after which it will be destroyed automatically) can be set in the constructor.
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
    void moveTo(const SDL_Point &_p);//move to this point with cosine interpolation
    inline void kill() {m_isImmortal = false; m_shouldKillSoon = true;}
    inline void killNow() {m_shouldKillNow = true;}
    void align(const Orientation &_orient, const bool &_instantly = false);
    void centre(const bool &_instantly = false);
    SDL_Point aligned(const Orientation &_orient);//returns the point the element should move to to align with the specified edge of the screen
    SDL_Point getCentre();

    //the following functions probably won't need to be called outside of the GUI class
    inline bool shouldKillNow() const {return m_shouldKillNow;}
    unsigned int getHeight() const;//the height the element takes up on screen, taking rotation into account
    unsigned int getWidth() const;//the width the element takes up on screen, taking rotation into account
    inline SDL_Point getPos() {return m_origin;}
    inline SDL_Renderer* getRenderer() {return m_ren;}
    void printRect();
    virtual void update();
    inline void updateRect() {m_destRect.x = m_origin.x - m_destRect.w/2; m_destRect.y = m_origin.y - m_destRect.h/2;}
    void draw() const;

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

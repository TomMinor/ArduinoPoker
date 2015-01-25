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
    /// \brief The basic element constructor. This probably won't need to be changed much since it is only called automatically by the ElementMaker class.
    /// \param _ren A pointer to the SDL rendering context.
    /// \param _tex A pointer to the SDL texture to use.
    /// \param _srcRect An SDL rectangle that covers the part of the texture to use.
    /// \param _destRect An SDL rectangle that specifies the part of the screen to draw the previous rectangle to.
    /// \param _orientation An enum specifying which edge of the screen this element should face.
    /// \param _origin An SDL point specifying the exact location this card should be created. Making sure this is in the centre of _destRect is handled by the ElementMaker
    /// class.
    /// \param _lifetime How many update() calls this element should last until it is destroyed. Passing 0 makes this lifetime indefinite.
    /// \return A drawable object.
    Element(SDL_Renderer *_ren,
            SDL_Texture *_tex,
            const SDL_Rect &_srcRect,
            const SDL_Rect &_destRect,
            const Orientation &_orient,
            const SDL_Point &_origin,
            const int &_lifetime = 0);

    virtual ~Element();

    /// \brief Moves the element to the specified location instantly.
    /// \param _p The SDL point to move the element to.
    /// \param _updateRect True if you want to update the element's SDL rectangle along with the unrendered origin, which you will 99% of the time.
    void setPos(const SDL_Point &_p, const bool &_updateRect = true);//move to this point instantly

    /// \brief Sets this element's "target" location which it will move closer to with cosine interpolation every time update() is called.
    /// \param _p The point to move to.
    void moveTo(const SDL_Point &_p);//move to this point with cosine interpolation

    /// \brief Marks this element for removal (so DealerGUI can remove it from its element array) as soon as it gets to its target location.
    inline void kill() {m_isImmortal = false; m_shouldKillSoon = true;}

    /// \brief Marks this element for removal (so DealerGUI can remove it from its element array) immediately.
    inline void killNow() {m_shouldKillNow = true;}

    /// \brief Moves this element to the specified edge of the screen.
    /// \param _orient The edge to move the element to.
    /// \param _instantly True to move instantly, false to interpolate the position on each update.
    void align(const Orientation &_orient, const bool &_instantly = false, const bool &_updateRect = true);

    /// \brief Moves this element to the centre of the screen.
    /// \param _instantly True to move instantly, false to interpolate the position on each update.
    void centre(const bool &_instantly = false, const bool &_updateRect = true);

    /// \brief Returns the point this element would move to to line up with the specified edge of the screen.
    /// \param _orient The edge of the screen this element would move to.
    SDL_Point aligned(const Orientation &_orient);//returns the point the element should move to to align with the specified edge of the screen

    /// \brief Returns the centre of the screen..
    SDL_Point getCentre();

    //the following functions probably won't need to be called outside of the GUI class

    /// \brief Returns whether this element should be destroyed now - DealerGUI uses this to tell whether to remove the element from its array and deallocate the memory.
    inline bool shouldKillNow() const {return m_shouldKillNow;}

    /// \brief Returns the screenwise "height" of this element i.e. the number of pixels it takes up in the SCREEN's y direction, not its own.
    unsigned int getHeight() const;//the height the element takes up on screen, taking rotation into account

    /// \brief Returns the screenwise "width" of this element i.e. the number of pixels it takes up in the SCREEN's x direction, not its own.
    unsigned int getWidth() const;//the width the element takes up on screen, taking rotation into account

    /// \brief Returns the position of this element's origin (which its SDL rectangle should be centered around).
    inline SDL_Point getPos() {return m_origin;}

    /// \brief Returns a pointer to the SDL rendering context this element is using (not sure why I needed this but oh well).
    inline SDL_Renderer* getRenderer() {return m_ren;}

    /// \brief Prints the bounds of this element's SDL rectangle - for debug purposes.
    void printRect();

    /// \brief Moves the element closer to its target point, and if that's done decreases the element's lifetime or marks it for removal.
    virtual void update();

    /// \brief Updates the elephant's SDL rectangle to move with its origin.
    inline void updateRect() {m_destRect.x = m_origin.x - m_destRect.w/2; m_destRect.y = m_origin.y - m_destRect.h/2;}

    /// \brief Draw's the element to the screen in its current state. Should probably always be called directly after update() unless you're doing something fancy with
    /// different update and draw frequencies.
    void draw() const;

protected:
    //stuff SDL needs to know
    /// \brief A pointer to the SDL rendering context.
    SDL_Renderer *m_ren;

    /// \brief A pointer to the SDL texture this element uses.
    SDL_Texture *m_texture;

    /// \brief An SDL rectangle covering the part of the texture to use.
    SDL_Rect m_srcRect;

    /// \brief An SDL rectangle covering the part of the screen to draw this element to.
    SDL_Rect m_destRect;

    /// \brief Which edge of the screen this element should face.
    Orientation m_orientation;

    //movement stuff
    /// \brief The "centre of mass" of this element on which movement/position calculations are performed.
    SDL_Point m_origin;

    /// \brief The point this element was at when moveTo() was last called.
    SDL_Point m_pointPrev;

    /// \brief The point this element is moving to i.e. the argument used in the last call to moveTo().
    SDL_Point m_pointDest;

    /// \brief A value between 0 and 1 representing how far this element has travelled between the previous position and the destination position. Used in cosine
    /// interpolation calculations.
    float m_progressAmount;

    /// \brief If true, the element will set shouldKillNow to true as soon as it finishes moving and life runs out.
    bool m_shouldKillSoon;

    /// \brief If true, the element will be deleted on the next update() of the DealerGUI.
    bool m_shouldKillNow;

    /// \brief If true, the element will never decrement life and thus have an indefinite lifetime.
    bool m_isImmortal;

    /// \brief How many update() cycles the element should last while stationary before shouldKillNow is set to true.
    int m_life;
};

}

#endif // ELEMENT_H

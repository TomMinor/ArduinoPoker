#include "include/gui/gui_elementmaker.h"

GUI::ElementMaker::ElementMaker(const GUI::CardInfo *_cardInfo, const GUI::LabelFormat *_labelFormat) : m_cardInfo(_cardInfo), m_labelFormat(_labelFormat)
{
}

GUI::Element* GUI::ElementMaker::makeElement(SDL_Texture *_tex, const GUI::Orientation &_orient)
{
    SDL_Rect rect;
    rect.x=0,
    rect.y=0;
    SDL_QueryTexture(_tex, NULL, NULL, &rect.w, &rect.h);

    SDL_Point origin = {0,0};

    return new GUI::Element(m_cardInfo->ren,_tex,rect,rect,_orient,origin);
}

GUI::Element* GUI::ElementMaker::makeElement(SDL_Texture *_tex, const SDL_Rect &_srcRect, const SDL_Rect &_destRect, const GUI::Orientation &_orient)
{
    SDL_Point origin = {0,0};

    return new GUI::Element(m_cardInfo->ren,_tex,_srcRect,_destRect,_orient,origin);
}

GUI::Element* GUI::ElementMaker::makeElement(Element *_inputElement)
{
    GUI::Element *temp = new GUI::Element(*_inputElement);
    return temp;
}

GUI::Card* GUI::ElementMaker::makeCard(const PlayingCard &_type, const GUI::Orientation &_orient)
{
    //std::cout<<"Returned rank: "<<_type.getRank()<<" suit: "<<_type.getSuit()<<"\n";
    //std::cout<<"Modified rank: "<<(_type.getRank()-1)%13<<" suit: "<<_type.getSuit()%4<<"\n";
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.h = m_cardInfo->cardHeight;
    srcRect.w = m_cardInfo->cardWidth;
//    srcRect.x = ((_type.getRank()-1)%13)*(m_cardInfo->cardWidth);
//    srcRect.y = (_type.getSuit()%4)*(m_cardInfo->cardHeight);

    srcRect.x = (_type.getRank()%13)*(m_cardInfo->cardWidth);
    srcRect.y = _type.getSuit()*(m_cardInfo->cardHeight);

    destRect.h = m_cardInfo->cardHeight;
    destRect.w = m_cardInfo->cardWidth;
    destRect.x = -m_cardInfo->cardWidth/2;
    destRect.y = -m_cardInfo->cardHeight/2;

    SDL_Point origin = {0,0};

    return new GUI::Card(m_cardInfo->ren,m_cardInfo->texture,srcRect,destRect,_orient,origin,_type);
}

GUI::Label *GUI::ElementMaker::makeLabel(const std::string &_inputString, const GUI::Orientation &_orient, const int &_lifetime)
{
    //write text to surface
    SDL_Surface *temp;
    temp = TTF_RenderText_Solid(m_labelFormat->font,_inputString.c_str(),m_labelFormat->colour);
    if (!temp)
    {
       std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << "\n";
       TTF_Quit();
       SDL_Quit();
       exit(1);
    }

    std::cout << std::hex << std::uppercase << &m_labelFormat->ren << " adress of renderer\n";

    //make texture from surface
    SDL_Texture *tex = NULL;
    tex = SDL_CreateTextureFromSurface(m_labelFormat->ren, temp);
    if (!tex)
    {
        std::cerr << "SDL_CreateTextureFromSurface() Failed: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_FreeSurface(temp);

    //make the bounding box from that texture
    SDL_Rect rect;
    rect.x=0,
    rect.y=0;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    //std::cout<<"Rectangle: W="<<rect.w<<", H="<<rect.h<<", X="<<rect.x<<", Y="<<rect.y<<"\n";

    SDL_Point origin = {0,0};

    return new GUI::Label(m_labelFormat->ren,tex,rect,_orient,origin,_lifetime);
}

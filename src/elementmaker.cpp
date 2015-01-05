#include "include/elementmaker.h"

ElementMaker::ElementMaker(const CardInfo *_cardInfo, const LabelFormat *_labelFormat) : m_cardInfo(_cardInfo), m_labelFormat(_labelFormat)
{
}

Card* ElementMaker::makeCard(const CardType &_type, const Orientation &_orient)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.h = m_cardInfo->cardHeight;
    srcRect.w = m_cardInfo->cardWidth;
    srcRect.x = static_cast<int>(_type.rank)*(m_cardInfo->cardWidth);
    srcRect.y = static_cast<int>(_type.suit)*(m_cardInfo->cardHeight);

    destRect.h = m_cardInfo->cardHeight;
    destRect.w = m_cardInfo->cardWidth;
    destRect.x = -m_cardInfo->cardWidth/2;
    destRect.y = -m_cardInfo->cardHeight/2;

    SDL_Point origin = {0,0};

    return new Card(m_cardInfo->ren,m_cardInfo->texture,srcRect,destRect,_orient,origin,_type);
}

Label *ElementMaker::makeLabel(const std::string &_inputString, const Orientation &_orient)
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

    //make texture from surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(m_labelFormat->ren, temp);
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

    return new Label(m_labelFormat->ren,tex,rect,_orient,origin);
}

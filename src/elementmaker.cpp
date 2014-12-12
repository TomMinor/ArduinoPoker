#include "include/elementmaker.h"

<<<<<<< HEAD
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
    destRect.x = 0;
    destRect.y = 0;
    return new Card(m_cardInfo->ren,m_cardInfo->texture,srcRect,destRect,_orient,_type);
}

Label *ElementMaker::makeLabel(const std::string &_inputString, const Orientation &_orient)
{
    //write text to surface
    SDL_Surface *temp;
    temp = TTF_RenderText_Solid(m_labelFormat->font,_inputString.c_str(),m_labelFormat->colour);
=======
ElementMaker::ElementMaker()
{
}

Card ElementMaker::makeCard(CardInfo _info, Rank _rank, Suit _suit, Orientation _orient)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.h = _info.cardHeight;
    srcRect.w = _info.cardWidth;
    srcRect.x = static_cast<int>(_rank)*(_info.cardWidth);
    srcRect.y = static_cast<int>(_suit)*(_info.cardHeight);

    destRect.h = _info.cardHeight*_info.scale;
    destRect.w = _info.cardWidth*_info.scale;
    destRect.x = 0;
    destRect.y = 0;
    return Card(_info.ren,_info.texture,srcRect,destRect,_orient,_rank,_suit);
}

Label ElementMaker::makeLabel(LabelFormat _format, std::string _inputString, Orientation _orient)
{
    //write text to surface
    SDL_Surface *temp;
    temp = TTF_RenderText_Solid(_format.font,_inputString.c_str(),_format.colour);
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
    if (!temp)
    {
       std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << "\n";
       TTF_Quit();
       SDL_Quit();
       exit(1);
    }

    //make texture from surface
<<<<<<< HEAD
    SDL_Texture *tex = SDL_CreateTextureFromSurface(m_labelFormat->ren, temp);
=======
    SDL_Texture *tex = SDL_CreateTextureFromSurface(_format.ren, temp);
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
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
    std::cout<<"Rectangle: W="<<rect.w<<", H="<<rect.h<<", X="<<rect.x<<", Y="<<rect.y<<"\n";

<<<<<<< HEAD
    return new Label(m_labelFormat->ren,tex,rect,_orient);
=======
    return Label(_format.ren,tex,rect,_orient);
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
}

#include "include/elementmaker.h"

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
    if (!temp)
    {
       std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << "\n";
       TTF_Quit();
       SDL_Quit();
       exit(1);
    }

    //make texture from surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(_format.ren, temp);
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

    return Label(_format.ren,tex,rect,_orient);
}

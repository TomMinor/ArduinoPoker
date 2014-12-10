/* a basic window in SDL use the command line
g++ -Wall -g  PutPixel.cpp -o PutPixel `sdl-config --cflags --libs`

or

clang++ -Wall -g PutPixel.cpp -o PutPixel `sdl-config --cflags --libs`

to compile the program
*/

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "label.h"
#include "card.h"
#include "listmenu.h"
#include "testelement.h"
//-----------------------------------------------------------------------------
/// @brief the width of the window
//-----------------------------------------------------------------------------
const int WINDOW_WIDTH = 320;
//-----------------------------------------------------------------------------
/// @brief the height of the window
//-----------------------------------------------------------------------------
const int WINDOW_HEIGHT = 256;

//the global texture scale for lovely pixelation
const int PIXEL_SCALE = 4;

//-----------------------------------------------------------------------------
/// @brief simple SDL clear screen function
/// @param [in] _screen a pointer to the SDL screen structure
/// @param [in] _r the red component for the clear colour 0-255
/// @param [in] _g the green component for the clear colour 0-255
/// @param [in] _b the blue component for the clear colour 0-255
//-----------------------------------------------------------------------------
void clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b);

//-----------------------------------------------------------------------------
/// @brief function to quit SDL with error message
/// @param[in] _msg the error message to send
//-----------------------------------------------------------------------------
void SDLErrorExit(const std::string &_msg);

int main()
{
	//-----------------------------------------------------------------------------
	// First thing we need to do is initialise SDL in this case we are
	// setting up just the video subsystem if we need audio or timer etc
	// we would | (or) the flags together see http://www.libsdl.org/intro.en/usinginit.html
	// we check the return value and if not 0 it is an error
	//-----------------------------------------------------------------------------
	if (SDL_Init( SDL_INIT_VIDEO ) !=0)
	{
		SDLErrorExit("error initialising SDL");
	}
	//-----------------------------------------------------------------------------
	// next we create a window and make sure it works
	//-----------------------------------------------------------------------------
    SDL_Window *win = 0;
    win = SDL_CreateWindow("Poker GUI", 100, 100, WINDOW_WIDTH*PIXEL_SCALE, WINDOW_HEIGHT*PIXEL_SCALE, SDL_WINDOW_SHOWN);
	if (win == 0)
	{
			SDLErrorExit("Error creating Window");
	}
	//-----------------------------------------------------------------------------
	// now we associate a renderer with the window
	//-----------------------------------------------------------------------------
	SDL_Renderer *renderer = 0;
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer)
	{
		SDLErrorExit("error creating renderer");
	}
    SDL_RenderSetScale(renderer,PIXEL_SCALE,PIXEL_SCALE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	
//============================================================================================================
	
	// Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init() Failed: " << TTF_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }
   
    // Load a font
    TTF_Font *font;
    font = TTF_OpenFont("fonts/ATARI400800_original.TTF", 8);
    if (!font)
    {
        std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    //initialise SDL_image library
    //int imgFlags = IMG_INIT_PNG;
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    // Load the playing card sheet
    SDL_Surface *temp;
    temp = IMG_Load("images/sheet.png");
    if (!temp)
    {
        std::cerr << "IMG_Load() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    //convert it to a texture
    SDL_Texture *cardTexture=SDL_CreateTextureFromSurface(renderer,temp);
    if (!cardTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface() Failed: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    SDL_FreeSurface(temp);

    //set the standard formatting for most of our labels
    LabelFormat standardFormat;
    const static SDL_Color text_color = {255,255,255,255};
    standardFormat.colour = text_color;
    standardFormat.font = font;
    standardFormat.ren = renderer;
    standardFormat.scale = 1;

    //set info for our cards
    CardInfo cardstyle;
    cardstyle.cardHeight = 76;
    cardstyle.cardWidth = 56;
    cardstyle.ren = renderer;
    cardstyle.scale = 1;
    cardstyle.texture = cardTexture;

    clearScreen(renderer,2,180,2);

    ElementMaker maker;

    Card testCard = maker.makeCard(cardstyle,ACE,SPADES,BOTTOM);

    SDL_Point topleft = {0,0};
    SDL_Point topright = {WINDOW_WIDTH-testCard.getWidth(),0};
    SDL_Point bottomleft = {0,WINDOW_HEIGHT-testCard.getHeight()};
    SDL_Point bottomright = {WINDOW_WIDTH-testCard.getWidth(),WINDOW_HEIGHT-testCard.getHeight()};

    Label testLabel = maker.makeLabel(standardFormat,std::string("Player 1"),BOTTOM);
    testLabel.setPos(topleft);

    Uint32 pixelFormat;
    SDL_QueryTexture(cardTexture,&pixelFormat,NULL,NULL,NULL);

    SDL_Texture* RTtest = SDL_CreateTexture(renderer,pixelFormat,SDL_TEXTUREACCESS_TARGET,WINDOW_WIDTH,WINDOW_HEIGHT);

//============================================================================================================
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit=false;
	// now we loop until the quit flag is set to true
	while(!quit)
	{
        SDL_SetRenderTarget(renderer, RTtest);

        clearScreen(renderer,2,180,2);

        testLabel.update();
        testLabel.draw();
        testCard.update();
        testCard.draw();

        SDL_SetRenderTarget(renderer, NULL);

        SDL_RenderCopy(renderer,RTtest,NULL,NULL);

		// finally we need to tell SDL to update the screen
		SDL_RenderPresent(renderer);

		// process SDL events, in this case we are looking for keys
		while ( SDL_PollEvent(&event) )
		{
			switch (event.type)
			{
				// this is the window x being clicked.
				case SDL_QUIT : quit = true; break;

				// now we look for a keydown event
				case SDL_KEYDOWN:
				{
					switch( event.key.keysym.sym )
					{
						// if it's the escape key quit
						case SDLK_ESCAPE :  quit = true; break;
                        case SDLK_UP : testCard.moveTo(topleft); break;
                        case SDLK_RIGHT : testCard.moveTo(topright); break;
                        case SDLK_DOWN : testCard.moveTo(bottomright); break;
                        case SDLK_LEFT : testCard.moveTo(bottomleft); break;
                        case SDLK_p : testCard.setFlipped(true); break;
                        case SDLK_l : testCard.setFlipped(false); break;
                        default : break;
					}
				}

				default : break;
			}
		}

        SDL_Delay(32);
	} // end processing loop

	// finally when we are done we need to tidy up SDL by calling SDL_Quit
	// sometime this is added as the atexit function to make it happen
	// automatically
	SDL_Quit();

	return EXIT_SUCCESS;
}


//-----------------------------------------------------------------------------
void clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b	)
{
	SDL_SetRenderDrawColor(_ren, _r,_g,_b,255);
	SDL_RenderClear(_ren);
}




//-----------------------------------------------------------------------------
void SDLErrorExit(const std::string &_msg)
{
  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <iostream>
//fuckshitfjkadl;fjkadl
 
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;
 
#if defined (DARWIN) || defined (WIN32)
  int SDL_main(int argc, char **argv)
#else
  int main(int argc, char **argv)
#endif
{
 if (SDL_Init( SDL_INIT_VIDEO ) !=0)
 {
  std::cerr <<"error initialising SDL exiting\n";
  exit(EXIT_FAILURE);
 }
 SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0,SDL_HWSURFACE | SDL_DOUBLEBUF );
 if( screen == NULL)
 {
  std::cerr<<"error setting SDL Video Mode\n";
  exit(EXIT_FAILURE);
 }		
 SDL_WM_SetCaption( "A Simple SDL Window", 0 );
 
	// Initialize SDL_ttf library
   if (TTF_Init() != 0)
   {
      std::cerr << "TTF_Init() Failed: " << TTF_GetError() << "\n";
      SDL_Quit();
      exit(1);
   }
   
   // Load a font
   TTF_Font *font;
   std::cout<<"Trying to open font\n";
   font = TTF_OpenFont("FreeSans.ttf", 32);
   if (font == NULL)
   {
      std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << "\n";
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
   else
   {
		std::cout<<"OpenFont() successful, apparently?\n";
	}

   // Write text to surface
   SDL_Surface *text;
   SDL_Color text_color = {255, 255, 255};
   std::cout<<"Trying to do surface thing\n";
   text = TTF_RenderText_Solid(font,
   "A journey of a thousand miles begins with a single step.",
   text_color);

   if (text == NULL)
   {
      std::cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << "\n";
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
 
	//load image
	SDL_Surface* image;
	image = SDL_LoadBMP("gptutorials.bmp");
	if (image == NULL)
	{
		 std::cerr << "SDL_LoadBMP() Failed: " << SDL_GetError() << "\n";
		 exit(1);
	}
	
// Apply the image to the screen
/*SDL_Rect dest;
dest.x=256;
dest.y=0;
dest.w=32;
dest.h=32;
if (SDL_BlitSurface(image, NULL, screen, &dest) != 0)
{
 std::cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << "\n";
 exit(1);
}*/

//Update the screen
SDL_Flip(screen);
 
 SDL_Event event;
 bool quit=false;
 
	// Image motion variables
	float x = 0.1f, y = 0.1f;
	float xVel = 50.0f, yVel = 40.0f;

	// Timing variables
	Uint32 old_time, current_time;
	float ftime;

	// Need to initialize this here for event loop to work
	current_time = SDL_GetTicks();
 
 while(!quit)
 {
  while ( SDL_PollEvent(&event) )
  {
   switch (event.type)
   {
    case SDL_QUIT : quit = true; break;
 
    case SDL_KEYDOWN:
    {
     switch( event.key.keysym.sym )
     {
      case SDLK_ESCAPE :  quit = true; break;
      default : break;
     }
    }
 
    default : break;
   }
  }
  
  // Update the timing information
  old_time = current_time;
  current_time = SDL_GetTicks();
  ftime = (current_time - old_time) / 1000.0f;
   
   // Update the image position
   x += (xVel * ftime);
   y += (yVel * ftime);

   // Check boundaries
   if (x <= 0.0f)
      xVel *= -1.0f;
   if (x >= (screen->w - image->w))
      xVel *= -1.0f;
   if (y <= 0.0f)
      yVel *= -1.0f;
   if (y >= (screen->h - image->h))
      yVel *= -1.0f;

   // Clear the screen
   if (SDL_FillRect(screen, NULL, SDL_MapRGB( screen->format, 0,0,0)) != 0)
   {
      std::cerr << "SDL_FillRect() Failed: " << SDL_GetError() << "\n";
      break;
   }

   SDL_Rect dest;
   dest.x = static_cast<int>(x);
   dest.y = static_cast<int>(y);

   // Apply the logo to the screen
   if (SDL_BlitSurface(image, NULL, screen, &dest) != 0)
   {
      std::cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << "\n";
      break;
   }
   
   /*// Apply the text to the screen
   if (SDL_BlitSurface(text, NULL, screen, NULL) != 0)
   {
      std::cerr << "SDL_BlitSurface() Failed: " << SDL_GetError() << "\n";
      break;
   }*/

   //Update the screen
   SDL_Flip(screen);
  
 } // end processing loop
 
 SDL_Quit();
 
 return EXIT_SUCCESS;
}

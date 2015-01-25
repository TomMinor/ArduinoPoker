#include <iostream>
#include "dealer/dealerLib.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "dealer/pokerHands.h"
#include <SDL/SDL.h>
#include <SDL2/SDL.h>



Uint32 updateComms(Uint32 interval, void *parm)
{
  static bool lock = false;

  if(!lock)
  {
      lock = true;

      dealerLib* myTable = reinterpret_cast<dealerLib*>(parm);

      //myTable->update();

//      myTable->dealHands();
//      myTable->bet();

//      myTable->dealFlop();
//      myTable->bet();
//      myTable->dealRiverTurn();
//      myTable->bet();
//      myTable->dealRiverTurn();
//      myTable->bet();

      printf("HNNGGH!");
      SDL_Delay(1000);
      lock= false;
  }

  return interval;
}

int main()
{

  //  std::srand( unsigned ( std::time(0) ) );
    SDL_Event event;

    dealerLib table;
    table.init();

    int running = 1;
    int last_time = 0;
    int cur_time = 0;
    int diff_time = 0;
    int accumulator = 0;

    setbuf(stdout, NULL);

    SDL_TimerID timer_id;

    //timer_id = SDL_AddTimer(10, updateComms, &table);

    while(running)
    {

        // Handle events here
        while(SDL_PollEvent(&event))
        {
            // Handle keystrokes here
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    running = false;
                }
            }
        }

        usleep(10 * 5000);

        table.dealHands();
        table.bet();
        table.dealFlop();

        last_time = cur_time;
        table.update();

    }

    return EXIT_SUCCESS;
}


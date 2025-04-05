#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.h"
#include "defs.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    scollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
      background.scoll(5);
      graphics.render(background);

      graphics.presentScene();
        SDL_Delay(25);
        SDL_RenderClear(graphics.renderer);
    }

    graphics.quit();
    return 0;
}

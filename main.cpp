#include "graphics.h"
#include "defs.h"
#include "game.h"
#include "obstacle.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(200);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    scollingBackground background;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    dc_khunglong mouse;
    mouse.x=graphics.dinoRect.x;
    mouse.y=graphics.dinoRect.y;

    Obstacle obstacle;
    bool quit = false;
    SDL_Event e;
    while( !quit&&!mouse.gameOver(mouse) ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
      background.scoll(5);
      graphics.render(background);
      graphics.prepareScene(graphics.loadTexture(ANH_NHAN_VAT),&graphics.dinoRect);

      const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
      if (currentKeyStates[SDL_SCANCODE_W]||currentKeyStates[SDL_SCANCODE_UP]||currentKeyStates[SDL_SCANCODE_SPACE]) mouse.dc_len();
      SDL_RenderClear(graphics.renderer);
      mouse.render(mouse,graphics,background);
      mouse.move();


      obstacle.spawnObstacle(graphics);
      obstacle.updateObstacles(graphics);
      obstacle.renderObstacles(graphics);

      graphics.presentScene();
        SDL_Delay(20);
    }


    graphics.quit();
    return 0;
}

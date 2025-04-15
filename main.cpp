#include "graphics.h"
#include "defs.h"
#include "game.h"
#include "obstacle.h"

using namespace std;


int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* backgroundtex=graphics.loadTexture(BACKGROUND_IMG);
    SDL_Texture* dinoTex=graphics.loadTexture(ANH_NHAN_VAT);

    scollingBackground background;
    background.setTexture(backgroundtex);

    dc_khunglong mouse;
    mouse.x=graphics.dinoRect.x;
    mouse.y=graphics.dinoRect.y;


    bool quit = false;
    SDL_Event e;

    const int FPS=60;
    const int frameDelay=1000/FPS;
    Uint32 frameStart;
    int frametime;

    while( !quit&&!mouse.gameOver(mouse) ) {

            frameStart=SDL_GetTicks();
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }


      const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
      if (currentKeyStates[SDL_SCANCODE_W]||currentKeyStates[SDL_SCANCODE_UP]||currentKeyStates[SDL_SCANCODE_SPACE]){
        mouse.dc_len();

      }
      background.scoll(distancebgr1);
      updateObstacles(graphics);
      mouse.move();
      spawnObstacle(graphics);

      xlvc(mouse);

      SDL_RenderClear(graphics.renderer);
      graphics.render(background);
      mouse.render(mouse,graphics,background);
      renderObstacles(graphics);
      graphics.presentScene();

      frametime=SDL_GetTicks()-frameStart;
      if(frameDelay>frametime){
        SDL_Delay(frameDelay-frametime);
      }
    }
    clearObstacles();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "Bạn thua rồi :)", graphics.window);
    SDL_DestroyTexture(dinoTex);
    SDL_DestroyTexture(backgroundtex);
    graphics.quit();
    return 0;
}

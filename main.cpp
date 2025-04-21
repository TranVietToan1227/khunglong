#include "graphics.h"
#include "defs.h"
#include "game.h"
#include "obstacle.h"

bool showMenu(Graphics& graphics) {
    SDL_Texture* menuTexture = graphics.loadTexture("Start.png");
    if (menuTexture == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Loi", "Không load được ảnh menu!", graphics.window);
        return false;
    }

    SDL_Event event;
    bool running = true;
    bool startGame = false;

    SDL_Rect menuRect={0,0,800,600};

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= 250 && x <= 500 && y >= 300 && y <= 400) {
                    startGame = true;
                    running = false;
                }
            }
        }

        SDL_RenderClear(graphics.renderer);
        SDL_RenderCopy(graphics.renderer, menuTexture, NULL, &menuRect);
        SDL_RenderPresent(graphics.renderer);
    }

    SDL_DestroyTexture(menuTexture);
    return startGame;
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    if (!showMenu(graphics)) {
        graphics.quit();
        return 0;
    }

    SDL_Texture* backgroundtex=graphics.loadTexture(BACKGROUND_IMG);


    scollingBackground background;
    background.setTexture(backgroundtex);

    dc_khunglong mouse;
    mouse.x=graphics.dinoRect.x;
    mouse.y=graphics.dinoRect.y;

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);


    bool quit = false;
    SDL_Event e;

    const int FPS=60;
    const int frameDelay=1000/FPS;
    Uint32 frameStart;
    int frametime;
    Uint32 lastBirdTick=0;

    while( !quit&&!mouse.gameOver(mouse) ) {

            frameStart=SDL_GetTicks();
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }


      const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
      if (currentKeyStates[SDL_SCANCODE_W]||currentKeyStates[SDL_SCANCODE_UP]||currentKeyStates[SDL_SCANCODE_SPACE]){
        mouse.dc_len();

      }
      background.scoll(5);
      updateObstacles(graphics);
      mouse.move();
      spawnObstacle(graphics);

      xlvc(mouse,graphics);

      if(frameStart-lastBirdTick>100){
      bird.tick();

      lastBirdTick=frameStart;
      }
      SDL_RenderClear(graphics.renderer);
      graphics.render(background);
      mouse.render(mouse,graphics);
      renderObstacles(graphics);
      bird.renderSprite(150, 100 ,graphics);
      graphics.presentScene();



      frametime=SDL_GetTicks()-frameStart;
      if(frameDelay>frametime){
        SDL_Delay(frameDelay-frametime);
      }
    }
    clearObstacles();
    SDL_DestroyTexture(backgroundtex);
    SDL_DestroyTexture(birdTexture);
    graphics.quit();
    return 0;
}

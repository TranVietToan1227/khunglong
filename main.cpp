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

bool showGameOverMenu(Graphics& graphics, int score,int highScore) {
    SDL_Texture* gameOverTexture = graphics.loadTexture("GameOver.png");
    if (gameOverTexture == nullptr) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Loi", "Không load được ảnh GameOver!", graphics.window);
        return false;
    }

    SDL_Event event;
    bool running = true;
    bool restartGame = false;

    SDL_Rect gameOverRect = { 0, 0, 800, 600 };


    graphics.renderText("Score: " + std::to_string(score), 300, 200, {255, 0, 0});

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= 250 && x <= 500 && y >= 300 && y <= 400) {  // Nút Restart
                    restartGame = true;
                    running = false;
                }
            }
        }

        SDL_RenderClear(graphics.renderer);
        SDL_RenderCopy(graphics.renderer, gameOverTexture, NULL, &gameOverRect);
        graphics.renderText("Score: " + std::to_string(score), 300, 200, {255, 0, 0});
        graphics.renderText("High Score: " + std::to_string(highScore), 300, 250, {255, 255, 0});

        SDL_RenderPresent(graphics.renderer);
    }

    SDL_DestroyTexture(gameOverTexture);
    return restartGame;
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    if (!graphics.loadFont("font.ttf", 24)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Lỗi", "Không thể load font!", graphics.window);
        graphics.quit();
        return -1;
    }
    int score=0;
    int hightscore=0;

     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Lỗi", Mix_GetError(), graphics.window);
        graphics.quit();
        return -1;
    }

    Mix_Music *gMusic = graphics.loadMusic("nhacnen.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("space.wav");
    Mix_Chunk *gCollision = graphics.loadSound("vacham.wav");

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

    mouse.reset();
    clearObstacles();
    background.setTexture(backgroundtex);
    lastBirdTick = 0;

    while( !quit&&!mouse.gameOver(mouse) ) {

            frameStart=SDL_GetTicks();
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }


      const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
      if (currentKeyStates[SDL_SCANCODE_W]||currentKeyStates[SDL_SCANCODE_UP]||currentKeyStates[SDL_SCANCODE_SPACE]){
        graphics.play(gJump);
        mouse.dc_len();

      }

      score++;
       bool gameOver = false;


      background.scoll(5);
      updateObstacles(graphics);
      mouse.move();
      spawnObstacle(graphics);

      if (xlvc(mouse, graphics, gCollision,score,hightscore)) {

    score = 0;
    mouse.reset();
    clearObstacles();
    background.setTexture(backgroundtex);
    lastBirdTick = 0;
    continue; // quay lại đầu vòng lặp
} else if (e.type == SDL_QUIT) {
    quit = true;
}

      if(frameStart-lastBirdTick>100){
      bird.tick();

      lastBirdTick=frameStart;
      }
      SDL_RenderClear(graphics.renderer);
      graphics.render(background);
      mouse.render(mouse,graphics);
      renderObstacles(graphics);
      bird.renderSprite(150, 100 ,graphics);
      graphics.renderText("Score: " + std::to_string(score), 600, 20, {255, 255, 255});


      graphics.presentScene();



      frametime=SDL_GetTicks()-frameStart;
      if(frameDelay>frametime){
        SDL_Delay(frameDelay-frametime);
      }

    }


    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);
    if (gCollision != nullptr) Mix_FreeChunk(gCollision);
    clearObstacles();
    SDL_DestroyTexture(backgroundtex);
    SDL_DestroyTexture(birdTexture);
    graphics.quit();
    return 0;
}

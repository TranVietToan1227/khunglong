#include "obstacle.h"

std::vector<Obstacle> obstacles;

    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 2500;

    void spawnObstacle(Graphics& graphics){//sinh vật cản mới

        Uint32 currentTime=SDL_GetTicks();
          if(currentTime>lastSpawnTime+spawnInterval){
                Obstacle obs;
            int type=rand()%3;
            const char* textures[]={VATCAN1,VATCAN2,VATCAN3};
            obs.texture=IMG_LoadTexture(graphics.renderer,textures[type]);
            obs.rect={700,420,100,100};
            obstacles.push_back(obs);
            lastSpawnTime=currentTime;
            spawnInterval=2500+rand()%1000;

          }

    }

    void updateObstacles(Graphics& graphics){//cập nhật vị trí, xóa ảnh cũ, spawn mới
        for(auto& obs:obstacles){
            obs.rect.x-=7;
        }

        obstacles.erase(remove_if(obstacles.begin(),obstacles.end(),[](Obstacle& o){
                                  if( o.rect.x+o.rect.w<0){
                                    if(o.texture!=nullptr){
                                    SDL_DestroyTexture(o.texture);
                                    o.texture=nullptr;
                                  }
                                  return true;
                            }
                            return false;
                    }),obstacles.end());
    }

    void renderObstacles(Graphics& graphics) {
        for (const auto& obs : obstacles) {
            SDL_RenderCopy(graphics.renderer, obs.texture, nullptr, &obs.rect);
        }
    }
        bool inside(int x, int y,const SDL_Rect &r) {
            return x >= r.x && x <= r.x+r.w && y >= r.y && y <= r.y+r.h;
            }


        bool xlvc(dc_khunglong& va_cham,Graphics& graphics, Mix_Chunk* collisionSound,int score, int& highScore){
            for(const auto& obs: obstacles){
             if(inside(va_cham.x,va_cham.y,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y,obs.rect)
                || inside(va_cham.x,va_cham.y+PLAYER_HEIGHT,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y+PLAYER_HEIGHT,obs.rect)){

                    Mix_PlayChannel(-1, collisionSound, 0);

                    SDL_Texture* gameoverTexture= graphics.loadTexture("gameover.png");
                    if(!gameoverTexture){
                        SDL_Log("Khong the load anh Gameover: ",SDL_GetError());
                        exit(1);
                    }
                   SDL_Rect gameoverRect={0,0,800,600};
                   if (score > highScore) {
                highScore = score;
            }
                   SDL_RenderClear(graphics.renderer);
                   SDL_RenderCopy(graphics.renderer,gameoverTexture,nullptr,&gameoverRect);
                      // Vẽ text Score và HighScore
            graphics.renderText("Your Score: " + std::to_string(score), 280, 130, {255, 0, 0});
            graphics.renderText("High Score: " + std::to_string(highScore), 280, 180, {255, 0, 0});
            graphics.renderText("Click on the gameover area to play again", 170, 500, {255, 255, 255});

                   SDL_RenderPresent(graphics.renderer);

                   clearObstacles();

                   SDL_Event e;
            bool waitQuit = true;
            bool restartGame = false;
            while (waitQuit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        SDL_DestroyTexture(gameoverTexture);
                        SDL_Quit();
                        exit(0);
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        int x = e.button.x;
                        int y = e.button.y;

                        // Kiểm tra vị trí nút Restart
                        if (x >= 250 && x <= 500 && y >= 300 && y <= 400) {
                            restartGame = true;
                            waitQuit = false;
                        }
                    }
                }
                SDL_Delay(10);
            }

            // Giải phóng
            SDL_DestroyTexture(gameoverTexture);

                   return restartGame;
                }
             }
             return false;
          }

    void clearObstacles() {
    for (auto& obs : obstacles) {
        if (obs.texture) {
            SDL_DestroyTexture(obs.texture);
            obs.texture = nullptr;
        }
    }
    obstacles.clear();
}



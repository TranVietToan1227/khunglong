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


        void xlvc(dc_khunglong& va_cham,Graphics& graphics){
            for(const auto& obs: obstacles){
             if(inside(va_cham.x,va_cham.y,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y,obs.rect)
                || inside(va_cham.x,va_cham.y+PLAYER_HEIGHT,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y+PLAYER_HEIGHT,obs.rect)){
                    SDL_Texture* gameoverTexture= graphics.loadTexture("gameover.png");
                    if(!gameoverTexture){
                        SDL_Log("Khong the load anh Gameover: ",SDL_GetError());
                        exit(1);
                    }
                   SDL_Rect gameoverRect={0,0,800,600};
                   SDL_RenderClear(graphics.renderer);
                   SDL_RenderCopy(graphics.renderer,gameoverTexture,nullptr,&gameoverRect);
                   SDL_RenderPresent(graphics.renderer);

                   SDL_Delay(2000);
                   SDL_Event e;

                   clearObstacles();

                   if (graphics.renderer) {
                SDL_DestroyRenderer(graphics.renderer);
                graphics.renderer = nullptr;
            }

                     if (graphics.window) {
                SDL_DestroyWindow(graphics.window);
                graphics.window = nullptr;
            }
                    IMG_Quit();
                    SDL_Quit();

                    exit(0);
                }
             }
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



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
            obs.rect={730,450,70,70};
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


        void xlvc(dc_khunglong& va_cham){
            for(const auto& obs: obstacles){
             if(inside(va_cham.x,va_cham.y,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y,obs.rect)
                || inside(va_cham.x,va_cham.y+PLAYER_HEIGHT,obs.rect)
                || inside(va_cham.x+PLAYER_WIDTH,va_cham.y+PLAYER_HEIGHT,obs.rect)){
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



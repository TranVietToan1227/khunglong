#include "obstacle.h"

std::vector<Obstacle> obstacles;

void Obstacle::spawnObstacle(Graphics& graphics){//sinh vật cản mới
        Obstacle obs;
        Uint32 currentTime=SDL_GetTicks();
          if(currentTime>lastSpawnTime+spawnInterval){
            int type=rand()%3;
            const char* textures[]={VATCAN1,VATCAN2,VATCAN3};
            obs.texture=IMG_LoadTexture(graphics.renderer,textures[type]);
            obs.rect={730,450,70,70};
            lastSpawnTime=currentTime;
            spawnInterval=2500+rand()%1000;
          }
          obstacles.push_back(obs);
    }
    void Obstacle::updateObstacles(Graphics& graphics){//cập nhật vị trí, xóa ảnh cũ, spawn mới
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
    void Obstacle::renderObstacles(Graphics& graphics) {
    for (const auto& obs : obstacles) {
        SDL_RenderCopy(graphics.renderer, obs.texture, nullptr, &obs.rect);
    }
  }
    void Obstacle:: xlvc(Graphics& graphics){
        for(const auto& obs: obstacles){
            if(SDL_HasIntersection(&graphics.dinoRect,&obs.rect)){
                exit(0);
               }
        }

    }

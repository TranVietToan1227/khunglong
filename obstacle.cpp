#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game.h"
#include "obstacle.h"

void Obstacle::spawnObstacle(Graphics& graphics){//sinh vật cản mới
        Obstacle obs;
          int type=rand()%3;
          if(type==0){
            obs.texture=IMG_LoadTexture(graphics.renderer,VATCAN1);
            obs.rect={450,450,70,70};
          }
          else if(type==1){
            obs.texture=IMG_LoadTexture(graphics.renderer,VATCAN2);
            obs.rect={450,450,70,70};
          }
          else if(type==2){
            obs.texture=IMG_LoadTexture(graphics.renderer,VATCAN3);
            obs.rect={450,450,70,70};
          }
          obstacles.push_back(obs);
    }
    void Obstacle::updateObstacles(Graphics& graphics){//cập nhật vị trí, xóa ảnh cũ, spawn mới
        for(auto& obs:obstacles){
            obs.rect.x-=5;
        }

        obstacles.erase(remove_if(obstacles.begin(),obstacles.end(),[](Obstacle& o){return o.rect.x+o.rect.w<0}),obstacles.end());

        Uint32 currentTime = SDL_GetTicks();
        if(currentTime>lastSpawnTime+spawnInterval){
            spawnObstacle(graphics);
            lastSpawnTime=currentTime;
            spawnInterval=1500+rand()%1000;
        }
    }
    void Obstacle::renderObstacles(Graphics& graphics) {
    for (const auto& obs : obstacles) {
        SDL_RenderCopy(graphics.renderer, obs.texture, nullptr, &obs.rect);
    }
  }

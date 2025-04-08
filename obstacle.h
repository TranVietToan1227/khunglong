#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "graphics.h"
#include "game.h"
#include "defs.h"
#define VATCAN1 "suongrong1"
#define VATCAN2 "suongrong2"
#define VATCAN3 "suongrong3"
struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;

    vector<Obstacle> obstacle;
    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 2000;

   SDL_Texture* cactusTexture1 = IMG_LoadTexture(renderer,VATCAN1);
    SDL_Texture* cactusTexture2 = IMG_LoadTexture(renderer,VATCAN2);
    SDL_Texture* cactusTexture3 = IMG_LoadTexture(renderer,VATCAN3);

    void spawnObstacle(){

    }
};


#endif

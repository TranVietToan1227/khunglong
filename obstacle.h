#ifndef _OBSTACLE_H
#define _OBSTACLE_H
#include<SDL.h>
#include<SDL2/SDL_image.h>
#include "defs.h"
#include "game.h"
#include <bits/stdc++.h>

#define VATCAN1 "suongrong1.png"
#define VATCAN2 "suongrong2.png"
#define VATCAN3 "suongrong3.png"

 struct Graphics;

struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;

    vector<Obstacle> obstacles;
    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 2000;
    void spawnObstacle(Graphics& graphics);//sinh vật cản mới
    void updateObstacles(Graphics& graphics);//cập nhật vị trí, xóa ảnh cũ, spawn mới
    void renderObstacles(Graphics& graphics);
};


#endif

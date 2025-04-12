#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "defs.h"
#include "game.h"
#include "graphics.h"

#include <vector>


#define VATCAN1 "suongrong1.png"
#define VATCAN2 "suongrong2.png"
#define VATCAN3 "suongrong3.png"

 struct Graphics;

struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;




    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 5000;
    void spawnObstacle(Graphics& graphics);//sinh vật cản mới
    void updateObstacles(Graphics& graphics);//cập nhật vị trí, xóa ảnh cũ
    bool ktspam(Graphics& graphics);
    void renderObstacles(Graphics& graphics);// vẽ vật cản
};

extern std::vector<Obstacle> obstacles;

#endif

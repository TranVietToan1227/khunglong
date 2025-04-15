#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "defs.h"
#include "game.h"
#include "graphics.h"

#include <vector>


#define VATCAN1 "suongrong1.png"
#define VATCAN2 "suongrong2.png"
#define VATCAN3 "suongrong3.png"



struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;
};


    void spawnObstacle(Graphics& graphics);//sinh vật cản mới
    void updateObstacles(Graphics& graphics);//cập nhật vị trí, xóa ảnh cũ
    void renderObstacles(Graphics& graphics);// vẽ vật cản
    void xlvc(dc_khunglong& va_cham);
    void clearObstacles();

extern std::vector<Obstacle> obstacles;

#endif

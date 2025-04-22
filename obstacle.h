#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "defs.h"
#include "game.h"
#include "graphics.h"

#include <vector>


#define VATCAN1 "1suongrong.png"
#define VATCAN2 "2suongrong.png"
#define VATCAN3 "3suongrong.png"



struct Obstacle {
    SDL_Texture* texture;
    SDL_Rect rect;
};


    void spawnObstacle(Graphics& graphics);//sinh vật cản mới
    void updateObstacles(Graphics& graphics);//cập nhật vị trí, xóa ảnh cũ
    void renderObstacles(Graphics& graphics);// vẽ vật cản
    bool xlvc(dc_khunglong& va_cham,Graphics& graphics,Mix_Chunk* collisionSound,int score,int& highscore);
    void clearObstacles();

extern std::vector<Obstacle> obstacles;

#endif

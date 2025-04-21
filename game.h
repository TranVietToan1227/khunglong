#ifndef _GAME_H
#define _GAME_H

#include "defs.h"
#include "graphics.h"


static const int INITIAL_SPEED= -20;
static const int trong_luc=1;
static const int ground=450;
static const int JUM_HEIGHT=100;
static const int JUM_SPEED=8;

struct dc_khunglong{
    int x;
    int y;
    int speed=INITIAL_SPEED;
    bool isJumping=false;// trạng thái nhảy
    bool isFalling=false;// trạng thái rơi
    bool isGrounded=true;// trạng thái có tiếp xúc với mặt đất không

    void move(){
        if(isJumping){
        y+=speed;
        speed+=trong_luc;
        if(y<ground-JUM_HEIGHT){
            isJumping=false;
            isFalling=true;
        }
      }
      else if(isFalling){
        y+=speed;
        if(y>=ground){
            y=ground;
            isFalling=false;
            isGrounded=true;
        }
        speed+=trong_luc;
      }

    }
    void dc_len(){
       if(!isJumping&&!isFalling&& y==ground){
        isJumping=true;
        isGrounded=false;
        speed=INITIAL_SPEED;
       }
    }

    void render(const dc_khunglong& mouse,  Graphics& graphics) {
    SDL_Rect filled_rect;
    filled_rect.x = mouse.x;
    filled_rect.y = mouse.y;
    filled_rect.w = PLAYER_WIDTH;
    filled_rect.h = PLAYER_HEIGHT;
    SDL_RenderCopy(graphics.renderer,graphics.loadTexture(ANH_NHAN_VAT),nullptr,&filled_rect);
    }

    bool gameOver(const dc_khunglong mouse){
       return mouse.x<=0||mouse.x>=SCREEN_WIDTH
              || mouse.y<=0||mouse.y>=SCREEN_HEIGHT;
    }

};
#endif


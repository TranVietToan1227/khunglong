#ifndef _GAME_H
#define _GAME_H

#include "defs.h"
#include "graphics.h"


static const int INITIAL_SPEED= -32;
static const int trong_luc=2;
static const int ground=450;


struct dc_khunglong{
    int x;
    int y;
    int speed=INITIAL_SPEED;
    int dx=0;
    int dy=0;
    bool isJumping=false;
    void move(){
        if(isJumping){
        x+=dx;
        y+=speed;
        speed+=trong_luc;
        if(y>=ground){
            y=ground;
            speed=0;
            isJumping=false;
        }
      }
    }
    void dc_len(){
       if(!isJumping){
        isJumping=true;
        speed=INITIAL_SPEED;
       }
    }
    void dc_xuong(){
        dx=0;
        dy+=speed;
    }
    void dc_phai(){
        dx+=speed;
        dy=0;
    }
    void dc_trai(){
        dx=-speed;
        dy=0;
    }

    void render(const dc_khunglong& mouse,  Graphics& graphics,scollingBackground& background) {
    SDL_Rect filled_rect;
    filled_rect.x = mouse.x;
    filled_rect.y = mouse.y;
    filled_rect.w = 70;
    filled_rect.h = 70;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));
    background.scoll(5);
    graphics.render(background);
    SDL_RenderCopy(graphics.renderer,graphics.loadTexture(ANH_NHAN_VAT),nullptr,&filled_rect);
    }

    bool gameOver(const dc_khunglong mouse){
       return mouse.x<=0||mouse.x>=SCREEN_WIDTH
              || mouse.y<=0||mouse.y>=SCREEN_HEIGHT;
    }

};
#endif


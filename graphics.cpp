#include <iostream>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game.h"
#include "obstacle.h"

void Graphics::init(){
    SDL_INIT_EVERYTHING;
    window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

}
SDL_Texture* Graphics::loadTexture(const char* filename){
   SDL_Texture* texture=IMG_LoadTexture(renderer,filename);
   return texture;
}
void Graphics::prepareScene(SDL_Texture* filename,SDL_Rect* dinoRect){
    SDL_RenderCopy(renderer,filename,nullptr,dinoRect);
}
void Graphics::renderTexture(SDL_Texture* texture,int x, int y){
    SDL_Rect dest;
    dest.x=x;
    dest.y=y;
    SDL_QueryTexture(texture,nullptr,nullptr,&dest.w,&dest.h);
    SDL_RenderCopy(renderer,texture,nullptr,&dest);
}
void Graphics::render(const scollingBackground& bgr){
      renderTexture(bgr.texture,bgr.scollingOffset,0);
      renderTexture(bgr.texture,bgr.scollingOffset-bgr.width,0);
}
void Graphics::presentScene(){
    SDL_RenderPresent(renderer);
}
void Graphics::quit(){
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

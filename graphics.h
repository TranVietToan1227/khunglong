#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"

struct scollingBackground{
  SDL_Texture* texture;
  int scollingOffset=0;
  int width=PLAYER_WIDTH;
  int height=PLAYER_HEIGHT;

  void setTexture(SDL_Texture* _texture){
      texture=_texture;
      SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
  }
  void scoll(int distance){
      scollingOffset-=distance;
      if(scollingOffset<0){
        scollingOffset=width;
      }
  }
};


struct Graphics{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect dinoRect={PLAYER_X,PLAYER_Y,PLAYER_WIDTH,PLAYER_HEIGHT};

    SDL_Texture* loadTexture(const char* filename);

void init();

void prepareScene(SDL_Texture* filename, SDL_Rect* dinoRect);

void renderTexture(SDL_Texture* texture, int x, int y);

void render(const scollingBackground& bgr) ;

void presentScene();

void quit();


};

#endif // _GRAPHICS__H

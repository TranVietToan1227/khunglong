#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"

struct scollingBackground{
  SDL_Texture* texture;
  int scollingOffset=0;
  int width,height;

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
    SDL_Texture* loadTexture(const char* filename);
    SDL_Rect dinoRect={20,450,50,50};
    void init();
    void prepareScene(SDL_Texture* filename1,SDL_Texture* filename2,SDL_Rect* dinoRect);
    void prepareScene(SDL_Texture* filename,SDL_Rect dinoRect);
    void renderTexture(SDL_Texture* texture, int x, int y);
    void render(const scollingBackground& bgr);
    void presentScene();

    void quit();


};

#endif // _GRAPHICS__H

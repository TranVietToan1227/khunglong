#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <algorithm>
#include <vector>

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

    void renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h);

    void renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h, const double cx, const double cy, const double cw, const double ch);

    void renderTexture(SDL_Texture *image, const double x, const double y);

void render(const scollingBackground& bgr) ;


void presentScene();

void quit();


};
extern std::vector<SDL_Rect> clips;
extern std::vector<SDL_Rect> clips2;
struct Sprite {
    SDL_Texture* texture;
    int currentFrame = 0;


    void init(SDL_Texture* _texture, int frames, const int _clips [][4]);

    void tick();

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
    void renderSprite(int x, int y,Graphics& graphics) {
        const SDL_Rect* clip = getCurrentClip();
        SDL_Rect renderQuad = {x, y, getCurrentClip()->w, getCurrentClip()->h};
        SDL_RenderCopy(graphics.renderer,texture, clip, &renderQuad);
    }
};



#endif // _GRAPHICS__H

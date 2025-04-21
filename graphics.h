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

void renderTexture(SDL_Texture* texture, int x, int y);

void render(const scollingBackground& bgr) ;


void presentScene();

void quit();


};
extern std::vector<SDL_Rect> clips;
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

 extern std::vector<SDL_Rect> hhkl;
struct Dino{
    SDL_Texture* texture;
    int currentFrame=0;

    void init(SDL_Texture* _texture,int frames, const int _hhkl [][4]);
    void tick();

    const SDL_Rect* getCurrenthhkl() const{
    return &(hhkl[currentFrame]);
    }
    void renderDino(int x,int y,Graphics graphics){
    const SDL_Rect* kl=getCurrenthhkl();
    SDL_Rect renderQuad = {x, y, getCurrenthhkl()->w, getCurrenthhkl()->h};
        SDL_RenderCopy(graphics.renderer,texture, kl, &renderQuad);
    }
};


#endif // _GRAPHICS__H

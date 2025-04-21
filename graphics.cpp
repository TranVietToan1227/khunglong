#include "graphics.h"
  std:: vector<SDL_Rect> clips;
  std:: vector<SDL_Rect> clips2;

void Graphics::init(){
    SDL_INIT_EVERYTHING;
    window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

}

SDL_Texture* Graphics::loadTexture(const char* filename) {
    SDL_Surface* tempSurface=IMG_Load(filename);
    SDL_SetColorKey(tempSurface,SDL_TRUE,SDL_MapRGB(tempSurface->format,255,255,255));
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void Graphics::prepareScene(SDL_Texture* filename,SDL_Rect* dinoRect){
    SDL_RenderCopy(renderer,filename,nullptr,dinoRect);
}
void Graphics::renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h, const double cx, const double cy, const double cw, const double ch) {
    SDL_Rect PrsDest = {x,y,w,h};
    SDL_Rect CutDest = {cx,cy,cw,ch};
    SDL_RenderCopy(renderer, image, &CutDest, &PrsDest);

}

void Graphics::renderTexture(SDL_Texture *image, const double x, const double y) {
    SDL_Rect dest;
    dest.x=x;
    dest.y=y;
    SDL_QueryTexture(image,nullptr,nullptr,&dest.w,&dest.h);
    SDL_RenderCopy(renderer,texture,nullptr,&dest);
}

void Graphics::renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h) {
    SDL_Rect Dest = {x,y,w,h};
    SDL_RenderCopy(renderer,image,NULL,&Dest);
}
void Graphics::render(const scollingBackground& bgr){
      renderTexture(bgr.texture,bgr.scollingOffset,0,bgr.width,bgr.height);
      renderTexture(bgr.texture,bgr.scollingOffset-bgr.width,0,bgr.width,bgr.height);
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

    void Sprite::init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void Sprite::tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }



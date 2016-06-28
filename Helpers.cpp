#include "Helpers.h"

void drawPointer(SDL_Renderer* renderer, Vec2 bottom, Vec2 top){
    lineRGBA(renderer, bottom.x, bottom.y, top.x, top.y, 255, 0, 255, 255); 
    ellipseRGBA(renderer, top.x, top.y, 10, 10, 255, 0, 255, 255);
};

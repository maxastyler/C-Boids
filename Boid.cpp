#include "Boid.h"

void Boid::render(SDL_Renderer* renderer){
    ellipseRGBA(renderer, pos.x, pos.y, scale, scale, 0, 0, 0, 255);  
    Vec2 dir=vel.normalised()*scale+pos;
    lineRGBA(renderer, pos.x, pos.y, dir.x, dir.y, 0, 0, 0, 255); 
};

Boid::Boid(Vec2 _pos, Vec2 _vel){
    scale=10;
    pos=_pos;
    vel=_vel;
};

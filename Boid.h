#ifndef BOID
#define BOID

#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

class Boid
{
    private:

        Vec2 pos;
        Vec2 vel;
        float maxVel=0.3;
        float maxAcc=0.005;
        float scale=10;
        
        float perceptionAngle=2;
        float perceptionRange=100;

    public:

        Boid():pos(Vec2(0, 0)){};
        Boid(float _x, float _y):pos(Vec2(_x, _y)){};
        Boid(Vec2, Vec2);
        Boid(float _scale):scale(_scale){};
        Boid(float _x, float _y, float _scale):pos(Vec2(_x, _y)), scale(_scale){};
        Boid(Vec2 vec):pos(vec){};
        void render(SDL_Renderer*);

        Vec2 getPos(){return pos;};
        void setPos(Vec2 newVec){pos=newVec;};
        Vec2 getVel(){return vel;};
        void setVel(Vec2 newVec){vel=newVec;};

        void limitVel(){vel.limit(maxVel);};

        float getX(){return pos.x;};
        float getY(){return pos.y;};
        float getMaxVel(){return maxVel;};
        float getMaxAcc(){return maxAcc;};
        void setX(float _x){pos.x=_x;};
        void setY(float _y){pos.y=_y;};

        float getScale(){return scale;};
        void setScale(float _scale){scale=_scale;};

        float getPerceptionAngle(){return perceptionAngle;};
        float getPerceptionRange(){return perceptionRange;};
};

#endif

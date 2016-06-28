#include "Clock.h"

Clock::Clock(){
    startTime=SDL_GetTicks();
    frameTime=startTime;
    newTime=startTime;
    lastTime=startTime;
};

int Clock::update(){
    newTime=SDL_GetTicks();
    frameTime=newTime-lastTime;
    lastTime=newTime;
    return frameTime;
}


#ifndef CLOCK
#define CLOCK

#include <SDL2/SDL.h>

class Clock
{

    private:
        int startTime;
        int frameTime;
        int newTime;
        int lastTime;
    public:
        Clock();
        int getStartTime(){return startTime;};
        int getFrameTime(){return frameTime;};
        int update();

};

#endif

#ifndef BOIDMANAGER
#define BOIDMANAGER

#include <vector>
#include "Boid.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class BoidManager
{

    private:
        vector <Boid> boids;
        SDL_Rect bounds;
    public:
        BoidManager(int, SDL_Rect);  
        void addBoids(int);
        void addBoid(int, int);
        void removeNear(int, int);
        void render(SDL_Renderer*);
        void update(int, Vec2);
        Vec2 centreOfMass(Boid*);
        Vec2 avoidBoids(Boid*);
        Vec2 matchVel(Boid*);
        Vec2 boundBoids(Boid*);
        bool checkAngle(Boid*, Boid*); 
        bool checkRange(Boid*, Boid*);
        bool checkSeen(Boid*, Boid*);

};

#endif

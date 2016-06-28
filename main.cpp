#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Boid.h"
#include "Vector.h"
#include "BoidManager.h"
#include "Clock.h"
#include "Helpers.h"
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Joystick* controller;
int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
bool init();
bool initJoystick();
void close();

using namespace std;

int main(int argc, char* args[])
{
    init();
    initJoystick();
    bool running = true;

    BoidManager manager(60, SDL_Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    Clock clock{};
    int dt;

    Vec2 pull(0, 0);
    int mousePosX=SCREEN_WIDTH/2;
    int mousePosY=SCREEN_HEIGHT/2;
    bool mmClicked=false;
    Vec2 mouseVec(mousePosX, mousePosY);

    SDL_Event e;
    while (running)
    {

        dt=clock.update(); 

        while (SDL_PollEvent(&e)!=0){
            if (e.type==SDL_QUIT){
                running = false;
            };
            if (e.type==SDL_MOUSEBUTTONDOWN){
                if (e.button.button==SDL_BUTTON_LEFT){
                    manager.addBoid(e.button.x, e.button.y); 
                };
                if (e.button.button==SDL_BUTTON_RIGHT){
                    manager.removeNear(e.button.x, e.button.y);
                };
                if (e.button.button==SDL_BUTTON_MIDDLE){
                    mmClicked=true;
                };
            };
            if (e.type==SDL_MOUSEBUTTONUP){
                if (e.button.button==SDL_BUTTON_MIDDLE){
                    mmClicked=false;
                };
            };
        };
        if (mmClicked){
            SDL_GetMouseState(&mousePosX, &mousePosY);            
        };
        mouseVec=Vec2(mousePosX, mousePosY); 
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawPointer(renderer, Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), mouseVec);
        pull=mouseVec-Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        pull/=60;
        manager.render(renderer);

        SDL_RenderPresent(renderer);

        manager.update(dt, pull);

    };

    close();

};

bool init(){
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)<0)
    {
        success=false;
    }
    else
    {
        window = SDL_CreateWindow("Boids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window==NULL){
            success=false;
        }
        else {
            renderer=SDL_CreateRenderer(window, -1, 0);
        }
    }
    return success;
};

bool initJoystick(){
    if (SDL_NumJoysticks() > 0){
        controller=SDL_JoystickOpen(0);
        if (controller==NULL) return false;
        else return true;
    };
    return false;
};

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_Quit();
};

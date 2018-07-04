
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "Game.h"

int main(int argc, char *argv[])
{

    Game* mainGame = new Game();

    const int FPS = 60;

    //How many miliseconds per frame
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    float frameTime;


    while (1)
    {
        frameStart = SDL_GetTicks();
        mainGame->processEvents();
        mainGame->render();


        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }


    return 0;
}

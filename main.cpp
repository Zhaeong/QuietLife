
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "SDLHandler.h"
#include "GameObj.h"

int main(int argc, char *argv[])
{
    SDLHandler SH(640, 480);

    const int FPS = 60;

    //How many miliseconds per frame
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    float frameTime;


    GameObj playerObj(0, 0, SH.renderer);
    playerObj.loadImage("res/bikeMan.bmp");

    SH.addGameObject(playerObj);

    while (1)
    {
        frameStart = SDL_GetTicks();

        string eventName = SH.getEvent();

        if(eventName == "MOVE_LEFT")
        {
            cout << eventName;
            GameObj player = SH.gameObjectArray.at(0);
            player.x_location += 5;

            SH.gameObjectArray[0] = player;
        }
        SH.renderGameObjects();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }


    return 0;
}


#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "SDLHandler.h"
#include "GameObj.h"

int main(int argc, char *argv[])
{
    SDLHandler SH(640, 480);

    GameObj playerObj;
    playerObj.loadSurface("res/bikeMan.bmp");

    while (1) {

        SH.gameObjectArray.clear();

        string eventName = SH.getEvent();

        if(eventName == "MOVE_LEFT")
        {
            cout << eventName;
            playerObj.x_location += 2;

            cout << playerObj.x_location;
        }

        SH.addGameObject(playerObj);
        SH.renderGameObjects();


    }

    return 0;
}

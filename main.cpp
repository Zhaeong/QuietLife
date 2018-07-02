
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "SDLHandler.h"
#include "GameObj.h"

int main(int argc, char *argv[])
{
    SDLHandler SH(640, 480);

    GameObj playerObj(0, 0, SH.renderer);
    playerObj.loadImage("res/bikeMan.bmp");

    SH.addGameObject(playerObj);

    while (1)
    {
        string eventName = SH.getEvent();

        if(eventName == "MOVE_LEFT")
        {
            cout << eventName;
            GameObj player = SH.gameObjectArray.at(0);
            player.x_location += 1;

            SH.gameObjectArray[0] = player;
        }
        SH.renderGameObjects();
    }


    return 0;
}

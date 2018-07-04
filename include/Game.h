#ifndef GAME_H
#define GAME_H

//Standard Lib
#include <string>
#include <vector>

//Project Lib
#include <SDL2/SDL.h>
#include "SDLHandler.h"
#include "GameObj.h"


class Game
{
    public:

        Game();
        virtual ~Game();

        SDLHandler* SH;

        SDL_Rect* cameraRect;
        GameObj *playerObj;

        vector<GameObj> gameObjectArray;




        void addGameObject(GameObj gameObj);

        void processEvents();
        void render();

    protected:

    private:
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

//Standard Lib
#include <string>
#include <vector>

//Project Lib
#include <SDL2/SDL.h>
#include "SDLHandler.h"
#include "GameObj.h"

#include "GameUtil.h"

class Game
{
    public:

        Game();
        virtual ~Game();

        int gameHeight;
        int gameWidth;

        int minBoundX;
        int minBoundY;
        int maxBoundX;
        int maxBoundY;

        SDLHandler *SH;

        SDL_Rect *cameraRect;

        GameObj *playerObj;

        GameObj *backGroundObj;

        vector<GameObj> gameObjectArray;

        void addGameObject(GameObj gameObj);

        void processEvents();
        void render();

    protected:

    private:
};

#endif // GAME_H

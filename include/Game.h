#ifndef GAME_H
#define GAME_H

//Standard Lib
#include <string>
#include <vector>

//Project Lib
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "SDLHandler.h"
#include "GameObj.h"

#include "GameUtil.h"

using namespace std;

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
        GameObj *fontObj;

        vector<GameObj> gameObjectArray;

        TTF_Font *gameFont;

        //functions
        void addGameObject(GameObj gameObj);

        void processEvents();
        void render();

    protected:

    private:
};

#endif // GAME_H

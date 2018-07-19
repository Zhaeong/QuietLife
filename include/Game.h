#ifndef GAME_H
#define GAME_H

//Standard Lib
#include <string>
#include <vector>
#include <algorithm>

//Project Lib
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//Game Libs

#include "SDLHandler.h"
#include "GameObj.h"
#include "PixelObj.h"
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

        vector<PixelObj> gameGroundArray;

        TTF_Font *gameFont;

        //functions

        void processEvents();
        void render();

        int currentPixelPos;
        PixelObj *currentPixel;

        //helper functions
        void addGameObject(GameObj gameObj);

        bool processTexture(GameObj *gObj);


    protected:

    private:
};

#endif // GAME_H

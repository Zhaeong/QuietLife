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

#include "CharacterObj.h"
#include "TextureObj.h"

#include "SceneLoader.h"

#include "UIHandler.h"


using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        bool bRunGame;

        int minBoundX;
        int minBoundY;
        int maxBoundX;
        int maxBoundY;

        SDLHandler *SH;

        SceneLoader *mSceneLoader;

        UIHandler *mUIHandler;

        SDL_Rect *cameraRect;

        CharacterObj *playerChar;

        vector<CharacterObj> mCharObjectArray;

        //functions
        void processEvents();
        void render();

        //helper functions
        void addCharObj(CharacterObj charObj);


    protected:

    private:
};

#endif // GAME_H

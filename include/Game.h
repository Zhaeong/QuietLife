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
using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        bool bRunGame;

        int gameHeight;
        int gameWidth;

        int minBoundX;
        int minBoundY;
        int maxBoundX;
        int maxBoundY;

        SDLHandler *SH;

        SceneLoader *mSceneLoader;


        SDL_Rect *cameraRect;

        CharacterObj *playerChar;

        GameObj *fontObj;

        TextureObj *dialogPanel;
        GameObj *dialogText;

        vector<CharacterObj> mCharObjectArray;

        TTF_Font *gameFont;

        //functions

        void processEvents();
        void render();

        //helper functions
        void addCharObj(CharacterObj charObj);

        //bool processTexture(GameObj *gObj);


    protected:

    private:
};

#endif // GAME_H

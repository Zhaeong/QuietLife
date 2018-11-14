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


class UIHandler;
class SceneLoader;
using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        bool bRunGame;

        SDLHandler *SH = NULL;

        SceneLoader *mSceneLoader = NULL;

        UIHandler *mUIHandler= NULL;

        SDL_Rect *cameraRect = NULL;

        CharacterObj *playerChar = NULL;

        vector<CharacterObj> mCharObjectArray;

        Uint32 mTimePassed;


        bool bMouseDown;

        int mouseXpos, mouseYpos;

        //functions
        void processEvents();
        void render();

        //helper functions
        void addCharObj(CharacterObj charObj);
        void centerCamOnPlayer();
        void setCamPos(int x, int y);


    protected:

    private:
};

#endif // GAME_H

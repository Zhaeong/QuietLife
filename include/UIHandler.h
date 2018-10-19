#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include <vector>

#include "Game.h"

#include "GameUtil.h"
#include "SDLHandler.h"
#include "TextureObj.h"
#include "GameObj.h"
#include "CharacterObj.h"

class Game;
const int LEFTCURSOR = 1;
const int RIGHTCURSOR = 2;

using namespace std;

class UIHandler
{
    public:
        UIHandler(SDLHandler *SH, Game *mainGame);
        virtual ~UIHandler();

        bool bRenderDialog;

        SDLHandler *mSH;
        Game *mMainGame;

        vector<TextureObj> mTextureArray;

        TextureObj *mouseCursorTexture;

        TextureObj *mBackgroundTexture;
        GameObj *mDialogText;

        GameObj *mBottomDialogText;
        GameObj *debugText;

        string getUserInput();

        void setDialog(string dialogString, int xPos, int yPos);
        void addTexture(TextureObj textureObj);
        void insertTexture(TextureObj textureObj, int pos);

        void render();

    protected:

    private:
};

#endif // UIHANDLER_H

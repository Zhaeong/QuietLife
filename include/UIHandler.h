#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include <vector>

#include "GameUtil.h"
#include "SDLHandler.h"
#include "TextureObj.h"
#include "GameObj.h"
#include "CharacterObj.h"

const int LEFTCURSOR = 1;
const int RIGHTCURSOR = 2;

using namespace std;

class UIHandler
{
    public:
        UIHandler(SDLHandler *SH, CharacterObj *playerChar);
        virtual ~UIHandler();

        SDLHandler *mSH;
        CharacterObj *mPlayerChar;

        vector<TextureObj> mTextureArray;

        GameObj *dialogText;

        GameObj *debugText;

        string getUserInput();

        void addTexture(TextureObj textureObj);
        void insertTexture(TextureObj textureObj, int pos);

        void render();

    protected:

    private:
};

#endif // UIHANDLER_H

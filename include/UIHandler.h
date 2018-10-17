#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include <vector>

#include "GameUtil.h"
#include "SDLHandler.h"
#include "TextureObj.h"

const int LEFTCURSOR = 1;
const int RIGHTCURSOR = 2;

using namespace std;

class UIHandler
{
    public:
        UIHandler(SDLHandler *SH);
        virtual ~UIHandler();

        SDLHandler *mSH;

        vector<TextureObj> mTextureArray;

        string getUserInput();

        void addTexture(TextureObj textureObj);
        void insertTexture(TextureObj textureObj, int pos);

        void render();

    protected:

    private:
};

#endif // UIHANDLER_H

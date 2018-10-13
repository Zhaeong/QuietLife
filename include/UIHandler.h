#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include <vector>

#include "SDLHandler.h"
#include "TextureObj.h"

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

        void render();

    protected:

    private:
};

#endif // UIHANDLER_H

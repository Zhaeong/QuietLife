#ifndef CHARACTEROBJ_H
#define CHARACTEROBJ_H

#include <vector>
#include <string>
#include <iostream>

#include "TextureObj.h"
#include "SDLHandler.h"

using namespace std;


class CharacterObj
{
    public:
        CharacterObj(SDLHandler *SH, string name);
        virtual ~CharacterObj();

        string mName;
        SDLHandler *mSH;
        vector<TextureObj> mTextureArray;

        int mXpos;
        int mYpos;


        int mWidth;
        int mHeight;


        void addTexture(TextureObj textureObj);
        void render(int xPos, int yPos);

        void setPos(int xPos, int yPos);
        void setDimension(int width, int height);

    protected:

    private:
};

#endif // CHARACTEROBJ_H

#ifndef CHARACTEROBJ_H
#define CHARACTEROBJ_H

#include <vector>
#include <string>
#include <iostream>

//For opening directories
#include <dirent.h>

#include <fstream>

#include "TextureObj.h"
#include "SDLHandler.h"
#include "GameUtil.h"
#include "AnimDef.h"
#include "SpriteAnimDef.h"

using namespace std;


class CharacterObj
{
    public:
        CharacterObj(SDLHandler *SH, string name);
        virtual ~CharacterObj();

        string mName;
        SDLHandler *mSH;
        vector<TextureObj> mTextureArray;

        //A vector of vector of Anim defs
        vector<AnimDef> mAnimArray;

        int mXpos;
        int mYpos;


        int mWidth;
        int mHeight;

        SDL_RendererFlip mFlipType;


        void addTexture(TextureObj textureObj);
        void render(int xPos, int yPos);

        void setPos(int xPos, int yPos);
        void setDimension(int width, int height);

        void getTextures(string dirPath);
        void getAnimate(string dirPath);

        void loadAnimation(string animationName);

    protected:

    private:
};

#endif // CHARACTEROBJ_H

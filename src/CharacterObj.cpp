#include "CharacterObj.h"

CharacterObj::CharacterObj(SDLHandler *SH, string name)
{
    cout << "Creating Character: " << name << "\n";
    //ctor
    mName = name;
    mSH = SH;

    setPos(0,0);
}

CharacterObj::~CharacterObj()
{
    //dtor
}


void CharacterObj::addTexture(TextureObj textureObj)
{
    mTextureArray.push_back(textureObj);
}

void CharacterObj::render(int xPos, int yPos)
{
    //Render objects in game array
    for(TextureObj tObj : mTextureArray)
    {
        //should do a boundary check to see if object is in view before rendering
        //Need to convert position of obj to cameras position
        SDL_Rect srcRect;
        SDL_Rect dstRect;

        srcRect.x=0;
        srcRect.y=0;
        srcRect.h=tObj.mHeight;
        srcRect.w=tObj.mWidth;

        dstRect.x = xPos;
        dstRect.y = yPos;
        dstRect.h = tObj.mHeight;
        dstRect.w = tObj.mWidth;




        tObj.renderTexture(srcRect, dstRect);
    }
}

void CharacterObj::setPos(int xPos, int yPos)
{
    mXpos = xPos;
    mYpos = yPos;
}

void CharacterObj::setDimension(int width, int height)
{
    mWidth = width;
    mHeight = height;
}

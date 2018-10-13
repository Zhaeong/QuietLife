#include "UIHandler.h"


#include "TextureObj.h"
UIHandler::UIHandler(SDLHandler *SH)
{
    mSH = SH;
}

UIHandler::~UIHandler()
{
    //dtor
}

string UIHandler::getUserInput()
{
    string eventName = mSH->getEvent();

    if(eventName == "EXIT")
    {
        return "EXIT";
    }
    else if(eventName == "MOVE_LEFT")
    {
        return "MOVE_LEFT";
    }
    else if(eventName == "MOVE_RIGHT")
    {
        return "MOVE_RIGHT";
    }
    else if(eventName == "KEYUP")
    {
        return "KEYUP";
    }
    else if(eventName == "KEY_E")
    {
        return "KEY_E";
    }
    else
    {
        return "NONE";
    }

}

void UIHandler::addTexture(TextureObj textureObj)
{
    mTextureArray.push_back(textureObj);
}

void UIHandler::render()
{
    //Render objects in game array
    for(unsigned int i = 0; i < mTextureArray.size(); i++)
    {
        TextureObj& tObj = mTextureArray[i];

        SDL_Rect srcRect;
        SDL_Rect dstRect;

        srcRect.x=0;
        srcRect.y=0;
        srcRect.h=tObj.mHeight;
        srcRect.w=tObj.mWidth;

        //To get the position of the texture relative to the character
        dstRect.x = tObj.mPosition.x;
        dstRect.y = tObj.mPosition.y;
        dstRect.h = tObj.mHeight;
        dstRect.w = tObj.mWidth;


        tObj.renderTexture(srcRect, dstRect, SDL_FLIP_NONE);

    }
}

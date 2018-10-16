#include "UIHandler.h"


#include "TextureObj.h"
UIHandler::UIHandler(SDLHandler *SH)
{
    mSH = SH;

    cout << "Loading Dialog Panel";

    TextureObj uiBackground(SH, "res/png/dialogPanel.png");
    uiBackground.setPos(0, 240, 0);
    uiBackground.setDim(640, 240);
    addTexture(uiBackground);


    TextureObj leftCursor(SH, "res/png/leftCursor.png");
    leftCursor.setPos(10, 280, 0);
    leftCursor.setDim(50, 50);
    addTexture(leftCursor);

}

UIHandler::~UIHandler()
{
    //dtor
}

string UIHandler::getUserInput()
{

    int mouseXpos, mouseYpos;

    string eventName = mSH->getEvent(&mouseXpos, &mouseYpos);

    //cout << "mouse down, x:" << mouseXpos << " y:" << mouseYpos << "\n";


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
        return "MOVE_STOP";
    }
    else if(eventName == "KEY_E")
    {
        return "KEY_E";
    }
    else if(eventName == "MOUSEDOWN")
    {

        if(pointInBox(mouseXpos, mouseYpos, mTextureArray[1].mPosition.x, mTextureArray[1].mPosition.y, mTextureArray[1].mWidth, mTextureArray[1].mHeight))
        {
            cout << "hit left cursor\n";
            return "MOVE_LEFT";
        }
        return "MOUSEDOWN";
    }
    else if(eventName == "MOUSEUP")
    {
        return "MOVE_STOP";
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

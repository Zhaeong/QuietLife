#include "UIHandler.h"



UIHandler::UIHandler(SDLHandler *SH, Game *mainGame)
{
    mSH = SH;
    mMainGame = mainGame;

    cout << "Loading Dialog Panel";

    //Load Mouse Texture
    mouseCursorTexture = new TextureObj(mSH, "res/png/mouseCursor.png");
    mouseCursorTexture->removeWhitespace();

    //Load dialog Texture and text for interactions
    mBackgroundTexture = new TextureObj(mSH, "res/png/dialogPanel.png");
    mBackgroundTexture->setDim(200, 50);
    mDialogText = new GameObj(0,0,0, mSH);
    bRenderDialog = false;

    TextureObj uiBackground(SH, "res/png/dialogPanel.png");
    uiBackground.setPos(0, GAMEHEIGHT / 3 * 2, 0);
    uiBackground.setDim(GAMEWIDTH, GAMEHEIGHT / 3);
    addTexture(uiBackground);

    TextureObj leftCursor(SH, "res/png/leftCursor.png");

    int cursorHeight = (GAMEHEIGHT / 3 * 2) + (GAMEHEIGHT / 6) - (leftCursor.mHeight / 2);

    leftCursor.setPos(10,cursorHeight , 0);
    leftCursor.setDim(50, 50);
    insertTexture(leftCursor, LEFTCURSOR);


    TextureObj rightCursor(SH, "res/png/rightCursor.png");
    rightCursor.setPos(GAMEWIDTH - 60, cursorHeight, 0);
    rightCursor.setDim(50, 50);
    insertTexture(rightCursor, RIGHTCURSOR);

    //Create dialog text
    mBottomDialogText = new GameObj(0,0,0, mSH);
    mBottomDialogText->loadText("I live because of you o mighty creator!", GAMEWIDTH);

    //Create debug text
    debugText = new GameObj(0, 0, 0, SH);
    debugText->loadText("Debugging", 200);


}

UIHandler::~UIHandler()
{
    //dtor
}

string UIHandler::getUserInput()
{
    int mouseXpos, mouseYpos;

    string eventName = mSH->getEvent(&mouseXpos, &mouseYpos);

    //set mouse texture position
    mouseCursorTexture->setPos(mouseXpos, mouseYpos, 0);

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
        if(pointInTexture(mouseXpos, mouseYpos, mTextureArray[LEFTCURSOR]))
        {
            return "MOVE_LEFT";
        }
        else if(pointInTexture(mouseXpos, mouseYpos, mTextureArray[RIGHTCURSOR]))
        {
            return "MOVE_RIGHT";
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

void UIHandler::insertTexture(TextureObj textureObj, int pos)
{
    mTextureArray.insert(mTextureArray.begin()+ pos, textureObj);
}


void UIHandler::setDialog(string dialogString, int xPos, int yPos)
{
    mBackgroundTexture->setPos(xPos, yPos, 0);
    mDialogText->mXpos = xPos;
    mDialogText->mYpos = yPos;
    mDialogText->loadText(dialogString, mBackgroundTexture->mWidth);
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

    //Render dialog text
    SDL_Rect dialogFontRectSrc, dialogFontRectTarget;
    dialogFontRectSrc.h = mBottomDialogText->mHeight;
    dialogFontRectSrc.w = mBottomDialogText->mWidth;
    dialogFontRectSrc.x = 0;
    dialogFontRectSrc.y = 0;

    dialogFontRectTarget.h = mBottomDialogText->mHeight;
    dialogFontRectTarget.w = mBottomDialogText->mWidth;
    dialogFontRectTarget.x = 0;
    dialogFontRectTarget.y = (GAMEHEIGHT / 3 ) * 2;


    mBottomDialogText->render(dialogFontRectSrc, dialogFontRectTarget);



    //render dialog

    if(bRenderDialog)
    {
        SDL_Rect dialogSrc, dialogDst;
        dialogSrc.h = mBackgroundTexture->mHeight;
        dialogSrc.w = mBackgroundTexture->mWidth;
        dialogSrc.x = 0;
        dialogSrc.y = 0;

        dialogDst.h = mBackgroundTexture->mHeight;
        dialogDst.w = mBackgroundTexture->mWidth;
        dialogDst.x = mBackgroundTexture->mPosition.x;
        dialogDst.y = mBackgroundTexture->mPosition.y;

        mBackgroundTexture->renderTexture(dialogSrc, dialogDst, SDL_FLIP_NONE);
        mDialogText->render(dialogSrc,dialogDst);
    }



    //Render mouse cursor
    SDL_Rect mouseSrc, mouseDst;

    mouseSrc.h = mouseCursorTexture->mHeight;
    mouseSrc.w = mouseCursorTexture->mWidth;
    mouseSrc.x = 0;
    mouseSrc.y = 0;

    mouseDst.h = mouseCursorTexture->mHeight;
    mouseDst.w = mouseCursorTexture->mWidth;
    mouseDst.x = mouseCursorTexture->mPosition.x;
    mouseDst.y = mouseCursorTexture->mPosition.y;

    mouseCursorTexture->renderTexture(mouseSrc, mouseDst, SDL_FLIP_NONE);




    if(DEBUGMODE)
    {
        SDL_Rect fontRect;

        fontRect.h = debugText->mHeight;
        fontRect.w = debugText->mWidth;
        fontRect.x = 0;
        fontRect.y = 0;

        debugText->loadText("pla - x:" + to_string(mMainGame->playerChar->mXpos) + " y:" + to_string(mMainGame->playerChar->mYpos), 200);

        debugText->render(fontRect, fontRect);
    }
}

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
    mBackgroundTexture->setDim(200, 500);
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
    mDialogText->loadText(dialogString, mBackgroundTexture->mWidth);
    mBackgroundTexture->mHeight = mDialogText->mHeight;

    //Set the dialog pos to be -10 - height of the dialog so it appears above the coords
    int renderY = yPos - mDialogText->mHeight - 10;
    mBackgroundTexture->setPos(xPos, renderY, 0);
    mDialogText->mXpos = xPos;
    mDialogText->mYpos = renderY;
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
        SDL_Rect dialogBckSrc, dialogBckDst;
        dialogBckSrc.h = mBackgroundTexture->mHeight;
        dialogBckSrc.w = mBackgroundTexture->mWidth;
        dialogBckSrc.x = 0;
        dialogBckSrc.y = 0;

        dialogBckDst.h = mDialogText->mHeight;
        dialogBckDst.w = mBackgroundTexture->mWidth;
        dialogBckDst.x = mBackgroundTexture->mPosition.x;
        dialogBckDst.y = mBackgroundTexture->mPosition.y;

        mBackgroundTexture->renderTexture(dialogBckSrc, dialogBckDst, SDL_FLIP_NONE);


        SDL_Rect dialogSrc, dialogDst;
        dialogSrc.h = mDialogText->mHeight;
        dialogSrc.w = mDialogText->mWidth;
        dialogSrc.x = 0;
        dialogSrc.y = 0;

        dialogDst.h = mDialogText->mHeight;
        dialogDst.w = mDialogText->mWidth;
        dialogDst.x = mDialogText->mXpos;
        dialogDst.y = mDialogText->mYpos;
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

void UIHandler::loadMouseTexture(string texturePath)
{
    if(texturePath != mouseCursorTexture->mImgLocation)
    {
        mouseCursorTexture->loadTexture(texturePath);
        mouseCursorTexture->removeWhitespace();
    }

}

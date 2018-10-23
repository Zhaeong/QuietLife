#include "Game.h"

Game::Game()
{
    cout << "Init Game\n";

    bRunGame = true;
    //Temple OS H and W

    SH = new SDLHandler(GAMEWIDTH, GAMEHEIGHT);

    SDL_ShowCursor(SDL_DISABLE);


    ////////////////////////
    //Initialize libraries//
    ////////////////////////

    //Initialize PNG loading
    cout << "Loading IMG Lib\n";
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    //Initialize SDL_ttf
    cout << "Loading Font Lib\n";
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    //Load background texture
    cout << "Loading Background\n";
    mSceneLoader = new SceneLoader(SH);
    mSceneLoader->loadScenesFromDirectory("res/scenes");
    mSceneLoader->loadScene("bedroom.png");

    //Set game bound according to game background
    minBoundX = mSceneLoader->minBoundX;
    minBoundY = mSceneLoader->minBoundY;
    maxBoundX = mSceneLoader->maxBoundX;
    maxBoundY = mSceneLoader->maxBoundY;


    cout << "Creating CharObj\n";
    //player char
    playerChar = new CharacterObj(SH, "Player");

    playerChar->setPos(mSceneLoader->playerInitX, mSceneLoader->playerInitY);
    playerChar->setDimension(15, 70);
    playerChar->getTextures("res/characters/steve");
    playerChar->getAnimate("res/characters/steve");


    //create UI elements
    mUIHandler = new UIHandler(SH, this);

    //create new char
    CharacterObj bobChar(SH, "Bob");
    bobChar.setPos(100, 40);
    bobChar.setDimension(30, 70);
    bobChar.mXRenderOffset = 10;
    bobChar.getTextures("res/characters/bob");
    bobChar.getAnimate("res/characters/bob");
    bobChar.loadAnimation("walk");
    bobChar.currScene = "hallway.png";
    bobChar.loadDialog("res/characters/bob/intro.dialog");

    addCharObj(bobChar);

    //cameraRect
    //Load camera to be same
    cameraRect = new SDL_Rect;

    cameraRect->w = GAMEWIDTH;
    cameraRect->h = GAMEHEIGHT;

    cameraRect->x = playerChar->mXpos + (playerChar->mWidth  /2) - (cameraRect->w/2);
    cameraRect->y = playerChar->mYpos + (playerChar->mHeight  /2) - (cameraRect->h/2);


}

Game::~Game()
{
    //dtor
}

void Game::processEvents()
{
    //string eventName = mUIHandler->getUserInput();


    int mouseXpos, mouseYpos;

    string eventName = SH->getEvent(&mouseXpos, &mouseYpos);

    string actionName = "NONE";


    ///////////////////////////////////////////////////////////
    //First check which image to render as the mouse texture
    //////////////////////////////////////////////////////////

    //set mouse texture position
    mUIHandler->mouseCursorTexture->setPos(mouseXpos, mouseYpos, 0);

    //check if mouse is collided with scene transition obj

    //Check if player is currently over a link transition obj
    string sceneCol = "NONE";

    for(unsigned int i = 0; i < mSceneLoader->mCurrentScene.mLinkObjArray.size(); i++)
    {
        LinkObj& lObj = mSceneLoader->mCurrentScene.mLinkObjArray[i];

        //checks if player is collided with scene transition obj
        if(horizontalColDetector(playerChar->mXpos, playerChar->mWidth, lObj.mXpos, lObj.mWidth))
        {
            sceneCol = lObj.mName;
        }

        //checks if mouse if collided with scene transition obj
        int mouseXWorld = mouseXpos + cameraRect->x;
        int mouseYWorld = mouseYpos + cameraRect->y;

        if(pointInBox(mouseXWorld, mouseYWorld, lObj.mXpos, lObj.mYpos, lObj.mWidth, lObj.mHeight))
        {
            mUIHandler->loadMouseTexture("res/png/mouseTalk.png");
        }
        else
        {
            mUIHandler->loadMouseTexture("res/png/mouseCursor.png");
        }


    }


    //cout << "mouse down, x:" << mouseXpos << " y:" << mouseYpos << "\n";
    if(eventName == "EXIT")
    {
        actionName = "EXIT";
    }
    else if(eventName == "MOVE_LEFT")
    {
        actionName = "MOVE_LEFT";
    }
    else if(eventName == "MOVE_RIGHT")
    {
        actionName = "MOVE_RIGHT";
    }
    else if(eventName == "KEYUP")
    {
        actionName = "MOVE_STOP";
    }
    else if(eventName == "KEY_E")
    {
        actionName = "KEY_E";
    }
    else if(eventName == "MOUSEDOWN")
    {
        if(pointInTexture(mouseXpos, mouseYpos, mUIHandler->mTextureArray[LEFTCURSOR]))
        {
            actionName = "MOVE_LEFT";
        }
        else if(pointInTexture(mouseXpos, mouseYpos, mUIHandler->mTextureArray[RIGHTCURSOR]))
        {
            actionName = "MOVE_RIGHT";
        }
        else
        {
            actionName = "MOUSEDOWN";
        }
    }
    else if(eventName == "MOUSEUP")
    {
        actionName = "MOVE_STOP";
    }
    else
    {
        actionName = "NONE";
    }

    //cout << actionName;



    CharacterObj *charCol = NULL;
    for(unsigned int i = 0; i < mCharObjectArray.size(); i++)
    {
        CharacterObj& charObj = mCharObjectArray[i];

        if(horizontalColDetector(playerChar->mXpos, playerChar->mWidth, charObj.mXpos, charObj.mWidth))
        {

            charCol = &charObj;

        }
        else
        {
            //Reset all character dialogs to 0
            charObj.currDialogLine = 0;
        }
    }

    if(actionName == "EXIT")
    {
        bRunGame = false;
    }
    if(actionName == "MOVE_LEFT")
    {
        playerChar->currState = "MOVE_LEFT";
    }

    if(actionName == "MOVE_RIGHT")
    {
        playerChar->currState = "MOVE_RIGHT";
    }

    if(actionName == "MOVE_STOP")
    {
        playerChar->currState = "MOVE_STOP";
    }

    if(actionName == "KEY_E")
    {
        cout << "Pressed E" << "\n";
        if(sceneCol != "NONE")
        {
            mSceneLoader->loadScene(sceneCol);
        }

        if(charCol != NULL)
        {
            mUIHandler->bRenderDialog = true;

            int charCamXpos = charCol->mXpos - cameraRect->x;
            int charCamYpos = charCol->mYpos - cameraRect->y;

            //cout << "PlaX:" << charCol->mXpos << " Y:" << charCol->mYpos << "\n";
            //cout << "CamX:" << cameraRect->x << " Y:" << cameraRect->y << "\n";
            //cout << "PlaCamX:" << charCamXpos << " Y:" << charCamYpos << "\n";

            mUIHandler->setDialog(charCol->mDialogArray[charCol->currDialogLine], charCamXpos, charCamYpos);
            charCol->addDialogLine();
        }
        else
        {
            mUIHandler->bRenderDialog = false;
        }



    }


    string playerHitDirection = hitBoundary1D(playerChar->mXpos, playerChar->mWidth, minBoundX, maxBoundX);

    if(playerChar->currState == "MOVE_LEFT")
    {
        if(playerHitDirection != "LEFT")
        {
            playerChar->mXpos -= 3;
            playerChar->mFlipType = SDL_FLIP_HORIZONTAL;
            playerChar->loadAnimation("walk");
        }
    }
    else if(playerChar->currState == "MOVE_RIGHT")
    {
        playerChar->mXpos += 3;
        playerChar->mFlipType = SDL_FLIP_NONE;
        playerChar->loadAnimation("walk");
    }
    else if(playerChar->currState == "MOVE_STOP")
    {
        playerChar->loadAnimation("idle");
    }

    //Check if the camera rect hits the game boundary

    string cameraHitDirectrion = hitBoundary1D(convertPlayerXtoCamX(playerChar->mXpos, playerChar->mWidth, cameraRect), cameraRect->w, minBoundX, maxBoundX);

    if(cameraHitDirectrion != "LEFT" && cameraHitDirectrion != "RIGHT")
    {
        cameraRect->x = convertPlayerXtoCamX(playerChar->mXpos, playerChar->mWidth, cameraRect);
    }


}
void Game::render()
{
    SDL_RenderClear(SH->renderer);

    //Render background and Scene Textures

    mSceneLoader->renderScene(*cameraRect);

    //Render Player
    playerChar->render(*cameraRect);


    //////////////////////
    //Render Dialog Panel
    //////////////////////

    mUIHandler->render();


    //Render characters in the scene
    //Need to get pointer to charObj due to rendering affecting the char animation
    for(unsigned int charNum = 0; charNum < mCharObjectArray.size(); charNum++)
    {
        CharacterObj& charObj = mCharObjectArray[charNum];
        if(charObj.currScene == mSceneLoader->mCurrentScene.mName)
        {
            charObj.render(*cameraRect);
        }
    }

    //Swap buffers to present backbuffer to screen
    SDL_RenderPresent(SH->renderer);

}

//Helper functions

void Game::addCharObj(CharacterObj charObj)
{
    mCharObjectArray.push_back(charObj);
}

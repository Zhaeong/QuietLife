#include "Game.h"




Game::Game()
{
    cout << "Init Game\n";

    bRunGame = true;
    //Temple OS H and W

    SH = new SDLHandler(GAMEWIDTH, GAMEHEIGHT);

    mUIHandler = new UIHandler(SH);


    //Initialize libraries

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



    //Load debug font texture
    gameFont = TTF_OpenFont("res/fonts/AmaticSC-Regular.ttf", 28);
    SDL_Color textColor = { 0, 0, 0 };

    fontObj = new GameObj(0, 0, SH);
    fontObj->loadText(gameFont, "heyyyyy baby", textColor, 200);


    cout << "Creating CharObj\n";
    //player char
    playerChar = new CharacterObj(SH, "Player");

    playerChar->setPos(mSceneLoader->playerInitX, mSceneLoader->playerInitY);
    playerChar->setDimension(15, 70);
    playerChar->getTextures("res/characters/steve");
    playerChar->getAnimate("res/characters/steve");



    //create new char
    CharacterObj bobChar(SH, "Bob");
    bobChar.setPos(100, 40);
    bobChar.setDimension(15, 70);
    bobChar.getTextures("res/characters/bob");
    bobChar.getAnimate("res/characters/bob");
    bobChar.loadAnimation("walk");
    bobChar.currScene = "hallway.png";

    addCharObj(bobChar);


    //cameraRect

    //Load camera to be same
    cameraRect = new SDL_Rect;

    cameraRect->w = GAMEWIDTH;
    cameraRect->h = GAMEHEIGHT;

    cameraRect->x = playerChar->mXpos + (playerChar->mWidth  /2) - (cameraRect->w/2);
    cameraRect->y = playerChar->mYpos + (playerChar->mHeight  /2) - (cameraRect->h/2);

    dialogText = new GameObj(0,0, SH);




}

Game::~Game()
{
    //dtor
}

void Game::processEvents()
{
    string eventName = mUIHandler->getUserInput();



    //Check if player is currently over a link transition obj
    string sceneCol = "NONE";
    for(unsigned int i = 0; i < mSceneLoader->mCurrentScene.mLinkObjArray.size(); i++)
    {
        LinkObj& lObj = mSceneLoader->mCurrentScene.mLinkObjArray[i];

        if(horizontalColDetector(playerChar->mXpos, playerChar->mWidth, lObj.mXpos, lObj.mWidth))
        {
            cout << "Collided with: " << lObj.mName << "\n";
            sceneCol = lObj.mName;
        }
    }

    if(eventName == "EXIT")
    {
        bRunGame = false;
    }
    if(eventName == "MOVE_LEFT")
    {
        playerChar->currState = "MOVE_LEFT";
        //nextX = originalPlayerX - 4;
        //playerChar->mFlipType = SDL_FLIP_HORIZONTAL;
        //playerChar->loadAnimation("walk");
    }

    if(eventName == "MOVE_RIGHT")
    {
        playerChar->currState = "MOVE_RIGHT";
        //nextX = originalPlayerX + 4;
        //playerChar->mFlipType = SDL_FLIP_NONE;
        //playerChar->loadAnimation("walk");
    }

    if(eventName == "MOVE_STOP")
    {
        //playerChar->loadAnimation("idle")
        playerChar->currState = "MOVE_STOP";
    }

    if(eventName == "KEY_E")
    {
        cout << "Pressed E" << "\n";
        if(sceneCol != "NONE")
        {
            mSceneLoader->loadScene(sceneCol);
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

    //////////////////////////
    //Render debug font
    //////////////////////////
    SDL_Rect fontRect;

    fontRect.h = fontObj->m_height;
    fontRect.w = fontObj->m_width;
    fontRect.x = 0;
    fontRect.y = 0;


    SDL_Color textColor = { 0, 0, 0 };
    fontObj->loadText(gameFont,
                      "pla - x:" + to_string(playerChar->mXpos) + " y:" + to_string(playerChar->mYpos) + "\n" +
                      "cam - x:" + to_string(cameraRect->x) + " y:" + to_string(cameraRect->y),
                      textColor,
                      200);


    fontObj->renderEx(fontRect, fontRect);

    //////////////////////
    //Render Dialog Panel
    //////////////////////

    mUIHandler->render();

    //Render text on top of the dialog panel

    SDL_Rect dialogFontRectSrc, dialogFontRectTarget;

    dialogFontRectSrc.h = dialogText->m_height;
    dialogFontRectSrc.w = dialogText->m_width;
    dialogFontRectSrc.x = 0;
    dialogFontRectSrc.y = 0;

    dialogFontRectTarget.h = dialogText->m_height;
    dialogFontRectTarget.w = dialogText->m_width;
    dialogFontRectTarget.x = 0;
    dialogFontRectTarget.y = (GAMEHEIGHT / 3 ) * 2;

    dialogText->loadText(gameFont, "I live because of you o mighty creator!", textColor, GAMEWIDTH);

    dialogText->renderEx(dialogFontRectSrc, dialogFontRectTarget);


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

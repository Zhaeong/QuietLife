#include "Game.h"




Game::Game()
{
    cout << "Init Game\n";

    bRunGame = true;
    //Temple OS H and W
    gameWidth = 640;
    gameHeight = 480;
    SH = new SDLHandler(gameWidth, gameHeight);

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

    cameraRect->w = gameWidth;
    cameraRect->h = gameHeight;

    cameraRect->x = playerChar->mXpos + (playerChar->mWidth  /2) - (cameraRect->w/2);
    cameraRect->y = playerChar->mYpos + (playerChar->mHeight  /2) - (cameraRect->h/2);

    cout << "player width: " << playerChar->mWidth << "\n";


    cout << "Loading Dialog Panel";

    TextureObj uiBackground(SH, "res/png/dialogPanel.png");
    uiBackground.setPos(0, 240, 0);
    uiBackground.setDim(640, 240);
    mUIHandler->addTexture(uiBackground);


    TextureObj leftCursor(SH, "res/png/leftCursor.png");
    leftCursor.setPos(10, 280, 0);
    leftCursor.setDim(50, 50);
    mUIHandler->addTexture(leftCursor);


    dialogText = new GameObj(0,0, SH);




}

Game::~Game()
{
    //dtor
}

void Game::processEvents()
{
    string eventName = mUIHandler->getUserInput();

    int originalPlayerX = playerChar->mXpos;
    int originalPlayerY = playerChar->mYpos;

    int originalCamX = cameraRect->x;
    int originalCamY = cameraRect->y;


    //Check if player is currently over a link transition obj
    string sceneCol = "NONE";
    for(unsigned int i = 0; i < mSceneLoader->mCurrentScene.mLinkObjArray.size(); i++)
    {
        LinkObj& lObj = mSceneLoader->mCurrentScene.mLinkObjArray[i];

        if(horizontalColDetector(originalPlayerX, playerChar->mWidth, lObj.mXpos, lObj.mWidth))
        {
            cout << "Collided with: " << lObj.mName << "\n";
            sceneCol = lObj.mName;
        }
    }

    int nextX = originalPlayerX;
    int nextY = originalPlayerY;

    if(eventName == "EXIT")
    {
        bRunGame = false;
    }
    if(eventName == "MOVE_LEFT")
    {
        nextX = originalPlayerX - 4;
        playerChar->mFlipType = SDL_FLIP_HORIZONTAL;
        playerChar->loadAnimation("walk");
    }

    if(eventName == "MOVE_RIGHT")
    {
        nextX = originalPlayerX + 4;
        playerChar->mFlipType = SDL_FLIP_NONE;
        playerChar->loadAnimation("walk");
    }

    if(eventName == "KEYUP")
    {
        playerChar->loadAnimation("idle");
    }

    if(eventName == "KEY_E")
    {
        cout << "Pressed E" << "\n";
        if(sceneCol != "NONE")
        {
            mSceneLoader->loadScene(sceneCol);
        }

    }

    /*
    if(eventName == "MOVE_DOWN")
    {
        nextY = originalY + 4;
        playerChar->loadAnimation("walk");
    }

    if(eventName == "MOVE_UP")
    {
        playerChar->loadAnimation("idle");
        nextY = originalY - 4;
    }
    */

    playerChar->mXpos = nextX;
    playerChar->mYpos = nextY;

    SDL_Rect playerRect;
    playerRect.x = playerChar->mXpos;
    playerRect.y = playerChar->mYpos;
    playerRect.w = playerChar->mWidth;
    playerRect.h = playerChar->mHeight;


    //Check if the camera rect hits the game boundary

    string playerHitDirection = hitBoundary(convertPlayerXtoCamX(&playerRect, cameraRect),
                                      convertPlayerYtoCamY(&playerRect, cameraRect),
                                      cameraRect->w,
                                      cameraRect->h,
                                      minBoundX,
                                      minBoundY,
                                      maxBoundX,
                                      maxBoundY);

    string cameraHitDirectrion = hitBoundary(cameraRect->x,
                                      cameraRect->y,
                                      cameraRect->w,
                                      cameraRect->h,
                                      minBoundX,
                                      minBoundY,
                                      maxBoundX,
                                      maxBoundY);

    //Depending on where it hit, revert player position to original

    if(playerHitDirection == "LEFT" || playerHitDirection == "RIGHT")
    {
        //cout << "hit:" << playerHitDirection << "\n";
        cameraRect->x = originalCamX;
        cameraRect->y = originalCamY;
    }
    else
    {
        cameraRect->x = convertPlayerXtoCamX(&playerRect, cameraRect);
        cameraRect->y = convertPlayerYtoCamY(&playerRect, cameraRect);
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

    SDL_Rect dialogRectSrc, dialogRectTarget;

    //dialogRectSrc.h = dialogPanel->mHeight;
    //dialogRectSrc.w = dialogPanel->mWidth;
    dialogRectSrc.x = 0;
    dialogRectSrc.y = 0;

    //make it so that it takes up a third of the bottom screen
    dialogRectTarget.h = gameHeight / 3 ;
    dialogRectTarget.w = gameWidth;
    dialogRectTarget.x = 0;
    dialogRectTarget.y = (gameHeight / 3 ) * 2;

    //dialogPanel->renderTexture(dialogRectSrc, dialogRectTarget, SDL_FLIP_NONE);
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
    dialogFontRectTarget.y = (gameHeight / 3 ) * 2;

    dialogText->loadText(gameFont, "I live because of you o mighty creator!", textColor, gameWidth);

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

    //Swap buffers
    SDL_RenderPresent(SH->renderer);

}

//Helper functions

void Game::addCharObj(CharacterObj charObj)
{
    mCharObjectArray.push_back(charObj);
}

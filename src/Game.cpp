#include "Game.h"

Game::Game()
{


    cout << "Init Game\n";

    bRunGame = true;
    //Temple OS H and W
    gameWidth = 640;
    gameHeight = 480;
    SH = new SDLHandler(gameWidth, gameHeight);

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
    backGroundObj = new TextureObj(SH, "res/png/scenes/bedroom.png");

    //Set game bound according to game background
    minBoundX = 0;
    minBoundY = 0;
    maxBoundX = backGroundObj->mWidth;
    maxBoundY = backGroundObj->mHeight;

    //Load camera to be same
    cameraRect = new SDL_Rect;
    cameraRect->h = gameHeight;
    cameraRect->w = gameWidth;
    cameraRect->x = 0;
    cameraRect->y = 0;

    //Load debug font texture
    gameFont = TTF_OpenFont("res/fonts/AmaticSC-Regular.ttf", 28);
    SDL_Color textColor = { 0, 0, 0 };

    fontObj = new GameObj(0, 0, SH);
    fontObj->loadText(gameFont, "heyyyyy baby", textColor, 200);


    cout << "Creating CharObj\n";
    //player char
    playerChar = new CharacterObj(SH, "Player");

    playerChar->setPos(400, 400);
    playerChar->setDimension(180, 140);

    playerChar->getTextures("res/png/steve");

    playerChar->getAnimate("res/png/steve");

    cout << "Loading Dialog Panel";
    dialogPanel = new TextureObj(SH, "res/png/dialogPanel.png");

    dialogText = new GameObj(0,0, SH);




}

Game::~Game()
{
    //dtor
}

void Game::processEvents()
{
    string eventName = SH->getEvent();

    int originalX = playerChar->mXpos;
    int originalY = playerChar->mYpos;

    int nextX = originalX;
    int nextY = originalY;

    if(eventName == "EXIT")
    {
        bRunGame = false;
    }
    if(eventName == "MOVE_LEFT")
    {
        nextX = originalX - 4;
        playerChar->mFlipType = SDL_FLIP_HORIZONTAL;
    }

    if(eventName == "MOVE_RIGHT")
    {
        nextX = originalX + 4;
        playerChar->mFlipType = SDL_FLIP_NONE;
    }

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

    playerChar->mXpos = nextX;
    playerChar->mYpos = nextY;

    SDL_Rect playerRect;
    playerRect.x = playerChar->mXpos;
    playerRect.y = playerChar->mYpos;
    playerRect.w = playerChar->mWidth;
    playerRect.h = playerChar->mHeight;


    //Check if the camera rect hits the game boundary

    string hitDirection = hitBoundary(convertPlayerXtoCamX(&playerRect, cameraRect),
                                      convertPlayerYtoCamY(&playerRect, cameraRect),
                                      cameraRect->w,
                                      cameraRect->h,
                                      minBoundX,
                                      minBoundY,
                                      maxBoundX,
                                      maxBoundY);


    //Depending on where it hit, revert player position to original
    if(hitDirection == "LEFT" || hitDirection == "RIGHT")
    {
        playerChar->mXpos = originalX;
    }
    else if (hitDirection == "TOP" || hitDirection == "BOTTOM")
    {
        playerChar->mYpos = originalY;
    }

    //update camera position based on final player position
    //First the player position needs to be offset by its height and width, then minus the game dimensions

    cameraRect->x = convertPlayerXtoCamX(&playerRect, cameraRect);
    cameraRect->y = convertPlayerYtoCamY(&playerRect, cameraRect);
}
void Game::render()
{
    SDL_RenderClear(SH->renderer);

    //Render background
    SDL_Rect dstRectBckObj;

    dstRectBckObj.h = cameraRect->h;
    dstRectBckObj.w = cameraRect->w;
    dstRectBckObj.x = 0;
    dstRectBckObj.y = 0;
    //backGroundObj->render(*cameraRect, dstRectBckObj);

    backGroundObj->renderTexture(*cameraRect, dstRectBckObj, SDL_FLIP_NONE);
    //Render objects in game array


    for(GameObj gObj : gameObjectArray)
    {
        //should do a boundary check to see if object is in view before rendering
        //Need to convert position of obj to cameras position
        SDL_Rect srcRect;
        SDL_Rect dstRectObj;

        srcRect.x=0;
        srcRect.y=0;
        srcRect.h=gObj.m_height;
        srcRect.w=gObj.m_width;

        dstRectObj.h = gObj.m_height;
        dstRectObj.w = gObj.m_width;

        //The position is the objects position minus the camera position
        //in order to get the object's place in accordance with the camera
        dstRectObj.x = gObj.m_xPos - cameraRect->x ;
        dstRectObj.y = gObj.m_yPos - cameraRect->y;

        gObj.renderEx(srcRect, dstRectObj);
    }



    //Render Player

    //Set player output render box to middle of screen
    int playerX = (cameraRect->w / 2) - (playerChar->mWidth /2);
    int playerY = (cameraRect->h / 2) - (playerChar->mHeight /2);

    playerChar->render(playerX, playerY);

    //Render debug font

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

    dialogRectSrc.h = dialogPanel->mHeight;
    dialogRectSrc.w = dialogPanel->mWidth;
    dialogRectSrc.x = 0;
    dialogRectSrc.y = 0;

    //make it so that it takes up a third of the bottom screen
    dialogRectTarget.h = gameHeight / 3 ;
    dialogRectTarget.w = gameWidth;
    dialogRectTarget.x = 0;
    dialogRectTarget.y = (gameHeight / 3 ) * 2;

    dialogPanel->renderTexture(dialogRectSrc, dialogRectTarget, SDL_FLIP_NONE);

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


    //Swap buffers
    SDL_RenderPresent(SH->renderer);

}

//Helper functions

void Game::addGameObject(GameObj gameObj)
{
    gameObjectArray.push_back(gameObj);
}

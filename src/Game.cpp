#include "Game.h"

Game::Game()
{
    cout << "Init Game\n";
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

    //Load Player texture
    cout << "Loading Player\n";
    playerObj = new GameObj(1000, 500, SH->renderer);
    playerObj->loadImage("res/bmp/bikeMan.bmp");

    //Load background texture
    cout << "Loading Background\n";
    backGroundObj = new GameObj(0,0, SH->renderer);
    backGroundObj->loadImage("res/bmp/background.bmp");

    //Set game bound according to game background
    minBoundX = 0;
    minBoundY = 0;
    maxBoundX = backGroundObj->m_width;
    maxBoundY = backGroundObj->m_height;

    //Load camera to be same
    cameraRect = new SDL_Rect;
    cameraRect->h = gameHeight;
    cameraRect->w = gameWidth;
    cameraRect->x = 0;
    cameraRect->y = 0;

    //Load debug font texture
    gameFont = TTF_OpenFont("res/fonts/AmaticSC-Regular.ttf", 28);
    SDL_Color textColor = { 0, 0, 0 };

    fontObj = new GameObj(0, 0, SH->renderer);
    fontObj->loadText(gameFont, "heyyyyy baby", textColor);

}

Game::~Game()
{
    //dtor
}

void Game::addGameObject(GameObj gameObj)
{
    gameObjectArray.push_back(gameObj);
}

void Game::processEvents()
{
    string eventName = SH->getEvent();

    int originalX = playerObj->m_xPos;
    int originalY = playerObj->m_yPos;

    int nextX = originalX;
    int nextY = originalY;

    if(eventName == "MOVE_LEFT")
    {
        nextX = originalX - 4;
    }

    if(eventName == "MOVE_RIGHT")
    {
        nextX = originalX + 4;
    }

    if(eventName == "MOVE_DOWN")
    {
        nextY = originalY + 4;
    }

    if(eventName == "MOVE_UP")
    {
        nextY = originalY - 4;

    }

    playerObj->m_xPos = nextX;
    playerObj->m_yPos = nextY;

    //Check if the camera rect hits the game boundary
    string hitDirection = hitBoundary(convertPlayerXtoCamX(playerObj, cameraRect),
                                      convertPlayerYtoCamY(playerObj, cameraRect),
                                      cameraRect->w,
                                      cameraRect->h,
                                      minBoundX,
                                      minBoundY,
                                      maxBoundX,
                                      maxBoundY);

    if(hitDirection == "LEFT" || hitDirection == "RIGHT")
    {
        playerObj->m_xPos = originalX;
    }
    else if (hitDirection == "TOP" || hitDirection == "BOTTOM")
    {
        playerObj->m_yPos = originalY;
    }

    //update camera position based on player position
    //First the player position needs to be offset by its height and width, then minus the game dimensions
    cameraRect->x = convertPlayerXtoCamX(playerObj, cameraRect);
    cameraRect->y = convertPlayerYtoCamY(playerObj, cameraRect);
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
    backGroundObj->render(*cameraRect, dstRectBckObj);

    //Render objects in game array
    for(GameObj gObj : gameObjectArray)
    {
        SDL_Rect dstRectObj;
        dstRectObj.h = cameraRect->h;
        dstRectObj.w = cameraRect->w;
        dstRectObj.x = 0;
        dstRectObj.y = 0;
        gObj.render(*cameraRect, dstRectObj);
    }


    //Render Player
    SDL_Rect srcRect, dstRect;

    srcRect.h = playerObj->m_height;
    srcRect.w = playerObj->m_width;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.h = playerObj->m_height;
    dstRect.w = playerObj->m_width;
    dstRect.x = (cameraRect->w / 2) - (playerObj->m_width /2);
    dstRect.y = (cameraRect->h / 2) - (playerObj->m_height /2);

    playerObj->render(srcRect, dstRect);

    //Render font

    SDL_Rect fontRect;

    fontRect.h = fontObj->m_height;
    fontRect.w = fontObj->m_width;
    fontRect.x = 0;
    fontRect.y = 0;


    SDL_Color textColor = { 0, 0, 0 };
    fontObj->loadText(gameFont,
                      "pla - x:" + to_string(playerObj->m_xPos) + " y:" + to_string(playerObj->m_yPos) + "\n" +
                      "cam - x:" + to_string(cameraRect->x) + " y:" + to_string(cameraRect->y),
                      textColor);


    fontObj->render(fontRect, fontRect);


    SDL_RenderPresent(SH->renderer);

}

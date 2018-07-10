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

    cout << "Loading Font Lib\n";
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    cout << "Loading Player\n";
    //Load Player texture
    playerObj = new GameObj(0, 0, SH->renderer);
    playerObj->loadImage("res/bmp/bikeMan.bmp");


    cout << "Loading Background\n";
    //Load background texture
    backGroundObj = new GameObj(0,0, SH->renderer);
    backGroundObj->loadImage("res/bmp/background.bmp");

    minBoundX = 0;
    minBoundY = 0;
    maxBoundX = backGroundObj->m_width;
    maxBoundY = backGroundObj->m_height;


    //Load camera pos relative to player
    cameraRect = new SDL_Rect;
    cameraRect->h = gameHeight;
    cameraRect->w = gameWidth;
    cameraRect->x = 0;
    cameraRect->y = 0;


    gameFont = TTF_OpenFont("res/fonts/AmaticSC-Regular.ttf", 28);

    //Load font texture

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

    int newX = playerObj->m_xPos;
    int newY = playerObj->m_yPos;

    if(eventName == "MOVE_LEFT")
    {
        int nextX = newX - 4;
        if(hitBoundary(nextX, newY, playerObj->m_width, playerObj->m_height,
                       minBoundX, minBoundY, maxBoundX, maxBoundY) != "LEFT")
        {
            newX  = nextX;
        }
        else
        {
            cout << "hit left";
        }
    }

    if(eventName == "MOVE_RIGHT")
    {
        int nextX = newX + 4;
        if(hitBoundary(nextX, newY, playerObj->m_width, playerObj->m_height,
                       minBoundX, minBoundY, maxBoundX, maxBoundY) != "RIGHT")
        {
            newX  = nextX;
        }
    }

    if(eventName == "MOVE_DOWN")
    {
        int nextY = newY + 4;
        if(hitBoundary(newX, nextY, playerObj->m_width, playerObj->m_height,
                       minBoundX, minBoundY, maxBoundX, maxBoundY) != "BOTTOM")
        {
            newY  = nextY;
        }
    }

    if(eventName == "MOVE_UP")
    {
        int nextY = newY - 4;
        if(hitBoundary(newX, nextY, playerObj->m_width, playerObj->m_height,
                       minBoundX, minBoundY, maxBoundX, maxBoundY) != "UP")
        {
            newY  = nextY;
        }

    }

    playerObj->m_xPos = newX;
    playerObj->m_yPos = newY;



    //update camera position based on player position
    //First the player position needs to be offset by its height and width, then minus the game dimensions
    cameraRect->x = (playerObj->m_xPos + (playerObj->m_width  /2)) - (gameWidth/2);
    cameraRect->y = (playerObj->m_yPos + (playerObj->m_height /2)) - (gameHeight/2);
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
    fontObj->loadText(gameFont, "x:" + to_string(playerObj->m_xPos) + " y:" + to_string(playerObj->m_yPos), textColor);


    fontObj->render(fontRect, fontRect);


    SDL_RenderPresent(SH->renderer);

}

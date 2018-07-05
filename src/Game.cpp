#include "Game.h"

Game::Game()
{

    gameWidth = 640;
    gameHeight = 480;
    SH = new SDLHandler(gameWidth, gameHeight);

    //Load Player texture
    playerObj = new GameObj(0, 0, SH->renderer);
    playerObj->loadImage("res/bikeMan.bmp");


    //Load background texture
    backGroundObj = new GameObj(0,0, SH->renderer);
    backGroundObj->loadImage("res/background.bmp");

    //Load camera pos relative to player
    cameraRect = new SDL_Rect;
    cameraRect->h = gameHeight;
    cameraRect->w = gameWidth;
    cameraRect->x = 0;
    cameraRect->y = 0;


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

    if(eventName == "MOVE_LEFT")
    {
        cout << eventName;
        playerObj->m_xPos  -= 4;
    }

    if(eventName == "MOVE_RIGHT")
    {
        cout << eventName;
        playerObj->m_xPos  += 4;
    }

    if(eventName == "MOVE_DOWN")
    {
        playerObj->m_yPos += 4;
    }

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

    SDL_RenderPresent(SH->renderer);
}

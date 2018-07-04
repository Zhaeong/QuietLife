#include "Game.h"

Game::Game()
{
    SH = new SDLHandler(640, 480);

    playerObj = new GameObj(0, 0, SH->renderer);
    playerObj->loadImage("res/bikeMan.bmp");

    //Load camera pos relative to player

    cameraRect = new SDL_Rect;
    cameraRect->h = 500;
    cameraRect->w = 500;
    cameraRect->x = playerObj->m_xPos;
    cameraRect->y = playerObj->m_yPos;

    GameObj backGroundObj(0,0, SH->renderer);
    backGroundObj.loadImage("res/background.bmp");
    addGameObject(backGroundObj);
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
        playerObj->m_xPos  -= 5;
    }

    if(eventName == "MOVE_RIGHT")
    {
        cout << eventName;
        playerObj->m_xPos  += 5;
    }

    if(eventName == "MOVE_DOWN")
    {
        playerObj->m_yPos += 5;
    }

    //update camera position
    cameraRect->x = playerObj->m_xPos;
    cameraRect->y = playerObj->m_yPos;
}
void Game::render()
{
    SDL_Rect srcRect, dstRect;

    srcRect.h = playerObj->m_height;
    srcRect.w = playerObj->m_width;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.h = playerObj->m_height;
    dstRect.w = playerObj->m_width;
    dstRect.x = 0;
    dstRect.y = 0;

    SDL_RenderClear(SH->renderer);


    for(GameObj gObj : gameObjectArray)
    {

        SDL_Rect srcRectObj;

        srcRectObj.h = cameraRect->h;
        srcRectObj.w = cameraRect->w;
        srcRectObj.x = cameraRect->x;
        srcRectObj.y = cameraRect->y;


        SDL_Rect dstRectObj;

        dstRectObj.h = cameraRect->h;
        dstRectObj.w = cameraRect->w;
        dstRectObj.x = 0;
        dstRectObj.y = 0;
        gObj.render(srcRectObj, dstRectObj);
    }

    playerObj->render(srcRect, dstRect);

    SDL_RenderPresent(SH->renderer);
}

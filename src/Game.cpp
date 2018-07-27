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


    //Playing with pixels
/*
    GameObj testGame(500, 500, SH);
    testGame.loadEditImage("res/png/testObj.png");

    processTexture(&testGame);

    gameObjectArray.push_back(testGame);


    */

    //Load background texture
    cout << "Loading Background\n";
    backGroundObj = new GameObj(0,0, SH);
    backGroundObj->loadEditImage("res/png/testObj.png");
    processTexture(backGroundObj);

    currentPixel = &gameGroundArray.at(0);
    currentPixelPos = 0;

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

    fontObj = new GameObj(0, 0, SH);
    fontObj->loadText(gameFont, "heyyyyy baby", textColor);


    cout << "Creating CharObj\n";
    //player char
    playerChar = new CharacterObj(SH, "Player");

    playerChar->setPos(gameGroundArray.at(0).m_X, gameGroundArray.at(0).m_Y);
    playerChar->setDimension(180, 140);


    TextureObj bikeTexture(SH, "res/bmp/bike.bmp");
    TextureObj manTexture(SH, "res/bmp/man.bmp");

    manTexture.setRotateTargets(-30, 30);
    playerChar->addTexture(bikeTexture);
    playerChar->addTexture(manTexture);




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

    if(eventName == "MOVE_LEFT")
    {
        //nextX = originalX - 4;
        nextX = currentPixel->m_X;
        nextY = currentPixel->m_Y - playerChar->mHeight;
        currentPixelPos += 10;
        currentPixel = &gameGroundArray.at(currentPixelPos);
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
    backGroundObj->render(*cameraRect, dstRectBckObj);

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

        gObj.render(srcRect, dstRectObj);
    }


    //Render Player

    //Set player output render box to middle of screen
    int playerX = (cameraRect->w / 2) - (playerChar->mWidth /2);
    int playerY = (cameraRect->h / 2) - (playerChar->mHeight /2);

    playerChar->render(playerX, playerY);

    //Render font

    SDL_Rect fontRect;

    fontRect.h = fontObj->m_height;
    fontRect.w = fontObj->m_width;
    fontRect.x = 0;
    fontRect.y = 0;


    SDL_Color textColor = { 0, 0, 0 };
    fontObj->loadText(gameFont,
                      "pla - x:" + to_string(playerChar->mXpos) + " y:" + to_string(playerChar->mYpos) + "\n" +
                      "cam - x:" + to_string(cameraRect->x) + " y:" + to_string(cameraRect->y),
                      textColor);


    fontObj->render(fontRect, fontRect);

    SDL_RenderPresent(SH->renderer);

}

//Helper functions

void Game::addGameObject(GameObj gameObj)
{
    gameObjectArray.push_back(gameObj);
}


bool Game::processTexture(GameObj *gObj)
{
    bool result = false;

    if(gObj->lockTexture())
    {
        //Allocate format from window
        Uint32 format = SDL_GetWindowPixelFormat( SH->window );
        SDL_PixelFormat* mappingFormat = SDL_AllocFormat( format );

        //Get pixel data
        Uint32* pixels = (Uint32*)gObj->getPixels();

        //4 bytes per pixel

        int pixelWidth = ( gObj->m_pitch / 4 );
        int pixelCount = pixelWidth * gObj->m_height;

        //Map colors
        Uint32 colorKey = SDL_MapRGB( mappingFormat, 0, 0, 0 );
        //Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0x00 );

        Uint32 white = SDL_MapRGB( mappingFormat, 255, 255, 255 );

        //Color key pixels

        int pixelX = 0;
        int pixelY = 0;

        for( int i = 0; i < pixelCount; i++ )
        {
            if( pixels[ i ] == colorKey )
            {
                PixelObj colorPix(pixelX, pixelY, pixels[i]);
                gameGroundArray.push_back(colorPix);

                pixels[ i ] = white;
            }


            //Set the next pixel's X and Y position
            pixelX += 1;
            if(pixelX == pixelWidth)
            {
                pixelX = 0;
                pixelY += 1;
            }

        }
        sort(gameGroundArray.begin(), gameGroundArray.end(), sortByX);
        cout << "Number of items:" << gameGroundArray.size();




        //Unlock texture
        if(gObj->unlockTexture())
        {
            result = true;
        }

        //Free format
        SDL_FreeFormat( mappingFormat );
    }
    else
    {
        cout << "Issue with locking texture" << gObj->m_imageLocation;
    }

    return result;
}

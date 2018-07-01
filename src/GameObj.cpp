#include "GameObj.h"

GameObj::GameObj()
{
    //ctor
    x_location = 0;
    y_location = 0;
}

GameObj::~GameObj()
{
    //dtor
}

void GameObj::loadSurface(string surfaceLocation)
{
    imageLocation = surfaceLocation;
    surface = SDL_LoadBMP(surfaceLocation.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
    }

    width = surface->w;
    height = surface->h;

}

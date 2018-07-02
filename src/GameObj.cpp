#include "GameObj.h"

GameObj::GameObj(int x_pos, int y_pos, SDL_Renderer *renderer)
{
    x_location = x_pos;
    y_location = y_pos;
    m_renderer = renderer;
}

GameObj::~GameObj()
{
}

void GameObj::loadImage(string imgLocation)
{
    imageLocation = imgLocation;
    SDL_Surface *surface = SDL_LoadBMP(imageLocation.c_str());

    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!m_texture)
    {
        cout << "texture error";
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }

    width = surface->w;
    height = surface->h;


    SDL_FreeSurface(surface);



}

#include "GameObj.h"

GameObj::GameObj(int x_pos, int y_pos, SDL_Renderer *renderer)
{
    m_xPos = x_pos;
    m_yPos = y_pos;
    m_renderer = renderer;
}

GameObj::~GameObj()
{
}

void GameObj::loadImage(string imageLocation)
{
    m_imageLocation = imageLocation;
    SDL_Surface *surface = SDL_LoadBMP(imageLocation.c_str());

    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
    }

    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 255, 255, 255 ) );
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!m_texture)
    {
        cout << "texture error";
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }

    //m_width = surface->w;
    //m_height = surface->h;

    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);


}

void GameObj::render(SDL_Rect srcRect, SDL_Rect dstRect)
{
    /*
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_width;
    srcRect.h = m_height;
    */

    SDL_RenderCopy(m_renderer, m_texture, &srcRect, &dstRect);

}

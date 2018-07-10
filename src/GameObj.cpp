#include "GameObj.h"

GameObj::GameObj(int x_pos, int y_pos, SDL_Renderer *renderer)
{
    m_texture = NULL;
    m_xPos = x_pos;
    m_yPos = y_pos;
    m_renderer = renderer;
}

GameObj::~GameObj()
{
}

void GameObj::loadImage(string imageLocation)
{
    cout << "Loading Image: " + imageLocation + "\n";
    free();

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

    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);

}

void GameObj::loadText(TTF_Font *font, string fontText, SDL_Color fontColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, fontText.c_str(), fontColor );
    if( textSurface == NULL )
    {
        cout << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError() ;
    }
    else
    { //Create texture from surface pixels
        m_texture =  SDL_CreateTextureFromSurface( m_renderer, textSurface );
        if( m_texture == NULL )
        {
            cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError() ;
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);


}

void GameObj::free()
{
    if( m_texture != NULL )
	{
		SDL_DestroyTexture( m_texture );
		m_texture = NULL;
        m_xPos = 0;
        m_yPos = 0;

        m_width = 0;
        m_height = 0;
	}
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

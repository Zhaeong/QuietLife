#include "GameObj.h"

GameObj::GameObj(int x_pos, int y_pos, SDLHandler *SH)
{
    m_texture = NULL;
    m_xPos = x_pos;
    m_yPos = y_pos;
    m_SH = SH;

    m_rotation = 0;
}

GameObj::~GameObj()
{
}

//Getters and Setters

void* GameObj::getPixels()
{
    return m_pixels;
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
    m_texture = SDL_CreateTextureFromSurface(m_SH->renderer, surface);
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

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( font, fontText.c_str(), fontColor, 150 );
    if( textSurface == NULL )
    {
        cout << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError() ;
    }
    else
    { //Create texture from surface pixels
        m_texture =  SDL_CreateTextureFromSurface( m_SH->renderer, textSurface );
        if( m_texture == NULL )
        {
            cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError() ;
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);

}

void GameObj::loadEditImage(string imageLocation)
{
    free();

    SDL_Surface* loadedSurface = IMG_Load( imageLocation.c_str() );

    if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imageLocation.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_GetWindowPixelFormat( m_SH->window ), 0 );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create blank streamable texture
			m_texture = SDL_CreateTexture( m_SH->renderer, SDL_GetWindowPixelFormat( m_SH->window ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( m_texture == NULL )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Lock texture for manipulation
				SDL_LockTexture( m_texture, NULL, &m_pixels, &m_pitch );

				//Copy loaded/formatted surface pixels
				memcpy( m_pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Unlock texture to update
				SDL_UnlockTexture( m_texture );
				m_pixels = NULL;

				//Get image dimensions
				m_width = formattedSurface->w;
				m_height = formattedSurface->h;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}

		//Get rid of old loaded surface

		//This block of code saves the surface as a png to location
		//const char * location = "res/png/out.png";
        //IMG_SavePNG(loadedSurface, location);

		SDL_FreeSurface( loadedSurface );
	}

}


bool GameObj::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( m_pixels != NULL )
	{
		cout << "Texture is already locked!\n";
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( m_texture, NULL, &m_pixels, &m_pitch ) != 0 )
		{
			cout << "Unable to lock texture! %s\n" << SDL_GetError();
			success = false;
		}
	}

	return success;
}

bool GameObj::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( m_pixels == NULL )
	{
		cout << "Texture is not locked!\n";
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( m_texture );
		m_pixels = NULL;
		m_pitch = 0;
	}

	return success;
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

        m_pixels = NULL;
		m_pitch = 0;
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

    SDL_RenderCopy(m_SH->renderer, m_texture, &srcRect, &dstRect);

}

void GameObj::renderEx(SDL_Rect srcRect, SDL_Rect dstRect)
{
    /*
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_width;
    srcRect.h = m_height;
    */

    m_rotation += 1;
    //Flip type
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    SDL_RenderCopyEx(m_SH->renderer, m_texture, &srcRect, &dstRect, m_rotation, NULL, flipType);

}

#include "TextureObj.h"

TextureObj::TextureObj(SDLHandler *SH, string imgLocation)
{
    cout << "Loading: " << imgLocation << "\n";
    mSH = SH;

    //Make sure to initialize texture to null or else SDL_DestroyTexture will crash program
    mTexture = NULL;

    free();


    SDL_Surface* loadedSurface = IMG_Load( imgLocation.c_str() );



    if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", imgLocation.c_str(), IMG_GetError() );
	}
	else
	{

		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_GetWindowPixelFormat( mSH->window ), 0 );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{

			//Create blank streamable texture
			mTexture = SDL_CreateTexture( mSH->renderer, SDL_GetWindowPixelFormat( mSH->window ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
			if( mTexture == NULL )
			{
				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{

				//Lock texture for manipulation
				SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch );

				//Copy loaded/formatted surface pixels
				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

				//Unlock texture to update
				SDL_UnlockTexture( mTexture );
				mPixels = NULL;

				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface( formattedSurface );
		}

		//Get rid of old loaded surface

		//This block of code saves the surface as a png to location
		//const char * location = "res/png/out.png";
        //IMG_SavePNG(loadedSurface, location);

		SDL_FreeSurface( loadedSurface );

		cout << "Finish Loading: " << imgLocation << "\n";
	}
}

TextureObj::~TextureObj()
{
    //dtor
}

void TextureObj::free()
{

    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
	}
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mPixels = NULL;
    mPitch = 0;

    mRotation = 0;
    mRotateStart = 0;
    mRotateEnd = 0;
    mRotationDirection = true;

}

void TextureObj::renderTexture(SDL_Rect srcRect, SDL_Rect dstRect)
{
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    SDL_Point middle;
    middle.x = mWidth / 2;
    middle.y = mHeight /2;

    getRotation();

    SDL_RenderCopyEx(mSH->renderer, mTexture, &srcRect, &dstRect, mRotation, &middle, flipType);

    //SDL_RenderCopy(mSH->renderer, mTexture, &srcRect, &dstRect);

}


void TextureObj::setRotateTargets(int Start, int End)
{
    mRotateStart = Start;
    mRotateEnd = End;
}


void TextureObj::getRotation()
{
    if(mRotationDirection)
    {
        if(mRotation < mRotateEnd)
        {
            mRotation += 1;
        }
        else
        {
            mRotationDirection = false;
        }
    }
    else
    {
        if(mRotation > mRotateStart)
        {
            mRotation -= 1;
        }
        else
        {
            mRotationDirection = true;
        }
    }
}

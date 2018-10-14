#include "TextureObj.h"

TextureObj::TextureObj(SDLHandler *SH, string imgLocation)
{
    cout << "Loading: " << imgLocation << "\n";

    mImgLocation = imgLocation;
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
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface,SDL_PIXELFORMAT_ARGB8888, 0 );
		if( formattedSurface == NULL )
		{
			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{

			//Create blank streamable texture
			mTexture = SDL_CreateTexture( mSH->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
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

				cout << "image is w:" << mWidth << " h:" << mHeight << "\n";
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

    mMiddle.x = mWidth / 2;
    mMiddle.y = mHeight /2;

    mPosition.x = 0;
    mPosition.y = 0;

    mZval = 0;
    mSpeed = 1;

}

void TextureObj::renderTexture(SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flipType)
{
    //SDL_RendererFlip flipType = SDL_FLIP_NONE;



    getRotation();

    SDL_RenderCopyEx(mSH->renderer, mTexture, &srcRect, &dstRect, mRotation, &mMiddle, flipType);

    //SDL_RenderCopy(mSH->renderer, mTexture, &srcRect, &dstRect);

}


void TextureObj::setRotateTargets(int Start, int End)
{
    mRotateStart = Start;
    mRotateEnd = End;
}

void TextureObj::setMiddle(int xVal, int yVal)
{
    mMiddle.x = xVal;
    mMiddle.y = yVal;
}

void TextureObj::setPos(int xVal, int yVal, int rotation)
{
    mPosition.x = xVal;
    mPosition.y = yVal;
    mRotation = rotation;
}

void TextureObj::setDim(int width, int height)
{
    mWidth = width;
    mHeight = height;

}

void TextureObj::getRotation()
{
    if(mRotationDirection)
    {
        if(mRotation < mRotateEnd)
        {
            mRotation += mSpeed;
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
            mRotation -= mSpeed;
        }
        else
        {
            mRotationDirection = true;
        }
    }
}


bool TextureObj::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( mPixels != NULL )
	{
		cout << "Texture is already locked!\n";
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			cout << "Unable to lock texture! %s\n" << SDL_GetError();
			success = false;
		}
	}

	return success;
}

bool TextureObj::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( mPixels == NULL )
	{
		cout << "Texture is not locked!\n";
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( mTexture );
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

bool TextureObj::removeWhitespace()
{
    bool result = false;

    if(lockTexture())
    {
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        //Allocate format from window
        //For some reason only this format works
        //Uint32 format = SDL_GetWindowPixelFormat( mSH->window );

        SDL_PixelFormat* mappingFormat = SDL_AllocFormat( SDL_PIXELFORMAT_ARGB8888 );

        //Get pixel data
        Uint32* pixels = (Uint32*)mPixels;
        //4 bytes per pixel

        int pixelWidth = ( mPitch / 4 );
        int pixelCount = pixelWidth * mHeight;

        //Map colorsmImgLocation
        //Uint32 colorKey = SDL_MapRGB( mappingFormat, 0, 0, 0 );
        //Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0x00 );

        Uint32 white = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0xFF );
        Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0 );

        //Color key pixels

        int pixelX = 0;
        int pixelY = 0;

        for( int i = 0; i < pixelCount; i++ )
        {

            //Uint8 * colors = (Uint8 *) pixels[ i ];
            //Uint32 thepixel;
            Uint8 red, green, blue, alpha;

            //SDL_GetRGBA(pixels[ i ],mappingFormat,&red,&green,&blue,&alpha);
            //cout << "Before \n";
            //cout << "R:" << (int)red << "G:" << (int)green<< "B:" << (int)blue<< "A:" << (int)alpha << "\n" ;

            if( pixels[ i ] == white )
            {
                pixels[ i ] = transparent;
            }


            SDL_GetRGBA(pixels[ i ],mappingFormat,&red,&green,&blue,&alpha);


            //Set the next pixel's X and Y position
            pixelX += 1;
            if(pixelX == pixelWidth)
            {
                pixelX = 0;
                pixelY += 1;
            }

        }

        //Unlock texture
        if(unlockTexture())
        {
            result = true;
        }

        //Free format
        SDL_FreeFormat( mappingFormat );
    }
    else
    {
        cout << "Issue with locking texture" << mImgLocation;
    }

    return result;
}

void TextureObj::setZval(int zval)
{
    mZval = zval;
}

void TextureObj::setSpeed(int speed)
{
    mSpeed = speed;
}



#include "GameObj.h"

GameObj::GameObj(int x_pos, int y_pos, int rotation, SDLHandler *SH)
{
    mTexture = NULL;
    mXpos = x_pos;
    mYpos = y_pos;
    mRotation = rotation;
    mSH = SH;

    textFont = TTF_OpenFont("res/fonts/AmaticSC-Regular.ttf", 28);

    textColor = { 0, 0, 0 };


}

GameObj::~GameObj()
{
}


void GameObj::loadText(string fontText, int maxWidth)
{
    free();

    //theres a sdl bug where the string has to contain spaces for it to work
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( textFont, fontText.c_str(), textColor, maxWidth );
    if( textSurface == NULL )
    {
        cout << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError() ;
    }
    else
    { //Create texture from surface pixels
        mTexture =  SDL_CreateTextureFromSurface( mSH->renderer, textSurface );
        if( mTexture == NULL )
        {
            cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError() ;
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

}


void GameObj::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;

        mWidth = 0;
        mHeight = 0;

	}
}

void GameObj::render(SDL_Rect srcRect, SDL_Rect dstRect)
{
    //Flip type
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    SDL_RenderCopyEx(mSH->renderer, mTexture, &srcRect, &dstRect, mRotation, NULL, flipType);

}

#ifndef TEXTUREOBJ_H
#define TEXTUREOBJ_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <cstring>
#include <iostream>

#include "SDLHandler.h"


class TextureObj
{
    public:
        TextureObj(SDLHandler *SH, string imgLocation);
        virtual ~TextureObj();


        SDLHandler *mSH;

        SDL_Texture *mTexture;

        int mWidth;
        int mHeight;
        void* mPixels;
		int mPitch;
        int mRotation;


        //func

        void free();

        void renderTexture(SDL_Rect srcRect, SDL_Rect dstRect);



    protected:

    private:
};

#endif // TEXTUREOBJ_H

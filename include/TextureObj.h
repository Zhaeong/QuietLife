#ifndef TEXTUREOBJ_H
#define TEXTUREOBJ_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <cstring>
#include <iostream>

#include "SDLHandler.h"
#include "PixelObj.h"


class TextureObj
{
    public:
        TextureObj(SDLHandler *SH, string imgLocation);
        virtual ~TextureObj();


        string mImgLocation;
        SDLHandler *mSH;


        SDL_Texture *mTexture;

        int mWidth;
        int mHeight;


        //func

        void free();
        void renderTexture(SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flipType);


        //Rotation Controls
        int mRotation;
        int mRotateStart;
        int mRotateEnd;
        SDL_Point mMiddle;

        SDL_Point mPosition;

        bool mRotationDirection;

        void setPos(int xVal, int yVal, int rotation);
        void setRotateTargets(int Start, int End);
        void setMiddle(int xVal, int yVal);
        void getRotation();



        //Texture manipulation

        void* mPixels;
		int mPitch;

        bool lockTexture();
        bool unlockTexture();

        bool removeWhitespace();

        int mZval;

        void setZval(int zval);



    protected:

    private:
};

#endif // TEXTUREOBJ_H

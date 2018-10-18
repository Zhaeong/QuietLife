#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "SDLHandler.h"


using namespace std;

class GameObj
{
    public:

        GameObj(int x_pos, int y_pos, int rotation, SDLHandler *SH);

        virtual ~GameObj();

        int mXpos;
        int mYpos;

        int mWidth;
        int mHeight;

        int mRotation;


        SDL_Color textColor;

        TTF_Font *textFont;



        string mImageLocation;

        SDL_Texture *mTexture;

		SDLHandler *mSH;

        //functions

        void loadText(string fontText, int maxWidth);


        void render(SDL_Rect srcRect, SDL_Rect dstRect);
        void free();

    protected:

    private:
};

#endif // GAMEOBJ_H

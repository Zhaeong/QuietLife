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

        GameObj(int x_pos, int y_pos, SDLHandler *SH);

        virtual ~GameObj();

        int m_xPos;
        int m_yPos;

        int m_width;
        int m_height;



        string m_imageLocation;

        SDL_Texture *m_texture;

        //void pointer to pixels
        void* m_pixels;
		int m_pitch;

		SDLHandler *m_SH;

		//Getters and setter functions
		void* getPixels();

        //functions
        void loadImage(string imageLocation);
        void loadText(TTF_Font *font, string fontText, SDL_Color fontColor);

        void loadEditImage(string imageLocation);

        bool lockTexture();
        bool unlockTexture();
        void render(SDL_Rect srcRect, SDL_Rect dstRect);
        void free();

    protected:

    private:
};

#endif // GAMEOBJ_H

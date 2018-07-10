#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>


using namespace std;

class GameObj
{
    public:
        GameObj(int x_location, int y_location, SDL_Renderer* renderer);
        virtual ~GameObj();

        int m_xPos;
        int m_yPos;

        int m_width;
        int m_height;

        string m_imageLocation;

        SDL_Texture *m_texture;
        SDL_Renderer *m_renderer;

        //functions

        void loadImage(string imageLocation);
        void loadText(TTF_Font *font, string fontText, SDL_Color fontColor);
        void render(SDL_Rect srcRect, SDL_Rect dstRect);
        void free();

    protected:

    private:
};

#endif // GAMEOBJ_H

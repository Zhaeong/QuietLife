#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SDL2/SDL.h>
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

        void loadImage(string imageLocation);
        void render(SDL_Rect srcRect, SDL_Rect dstRect);

    protected:

    private:
};

#endif // GAMEOBJ_H

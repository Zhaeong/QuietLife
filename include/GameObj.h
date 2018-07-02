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

        int x_location;
        int y_location;

        int width;
        int height;

        string imageLocation;

        SDL_Texture *m_texture;
        SDL_Renderer *m_renderer;

        void loadImage(string imgLocation);

    protected:

    private:
};

#endif // GAMEOBJ_H

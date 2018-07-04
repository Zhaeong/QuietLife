#ifndef SDLHANDLER_H
#define SDLHANDLER_H
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "GameObj.h"

using namespace std;


class SDLHandler
{
    public:

        int screenHeight;
        int screenWidth;

        SDL_Event event;
        SDL_Window *window;
        SDL_Renderer *renderer;

        SDLHandler(int screenWidth, int screenHeight);
        virtual ~SDLHandler();

        string getEvent();

        void renderTexture(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect);

    protected:

    private:
};

#endif // SDLHANDLER_H

#ifndef SDLHANDLER_H
#define SDLHANDLER_H
#include <string>
#include <vector>
#include <SDL.h>


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

        string getEvent(int *mouseXpos, int *mouseYpos);

        void renderTexture(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect);

    protected:

    private:
};

#endif // SDLHANDLER_H

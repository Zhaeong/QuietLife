#include "SDLHandler.h"
#include <iostream>

SDLHandler::SDLHandler(int screenWidth, int screenHeight)
{
    screenWidth = screenWidth;
    screenHeight = screenHeight;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


}

SDLHandler::~SDLHandler()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

string SDLHandler::getEvent()
{
    string eventName = "NONE";
    /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
    /* more events on the event queue, our while loop will exit when */
    /* that occurs.                                                  */
    while( SDL_PollEvent( &event ) )
    {
    /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch( event.type )
        {
            case SDL_QUIT:
                eventName = "QUIT";

            case SDL_KEYDOWN:
                eventName = "Key press detected\n";

                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym )
                {
                    case SDLK_LEFT:
                        eventName = "MOVE_LEFT";
                        break;
                    case SDLK_RIGHT:
                        eventName = "MOVE_RIGHT";
                        break;
                    case SDLK_UP:
                        eventName = "MOVE_UP";
                        break;
                    case SDLK_DOWN:
                        eventName = "MOVE_DOWN";
                        break;
                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                eventName =  "Key release detected\n";
                break;

            case SDL_MOUSEBUTTONDOWN:

                int x, y;
                SDL_GetMouseState( &x, &y );


                cout << "mouse down, x:" << x << " y:" << y;
                break;

            default:
                break;
        }
    }

    return eventName;
}



void SDLHandler::renderTexture(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect)
{
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}


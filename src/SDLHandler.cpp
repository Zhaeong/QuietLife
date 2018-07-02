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

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);


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

                //printf( ", Name: %s", SDL_GetKeyName( event.key.keysym.sym ) );

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

            default:
                break;
        }

    }
    return eventName;
}

int SDLHandler::addGameObject(GameObj gameObj)
{
    gameObjectArray.push_back(gameObj);
    return 0;
}

void SDLHandler::renderGameObjects()
{
    SDL_RenderClear(renderer);

    for(GameObj gObj : gameObjectArray)
    {
        SDL_Rect srcrect;
        SDL_Rect dstrect;

        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.w = gObj.width;
        srcrect.h = gObj.height;

        dstrect.x = gObj.x_location;
        dstrect.y = gObj.y_location;
        dstrect.w = gObj.width;
        dstrect.h = gObj.height;

        SDL_RenderCopy(renderer, gObj.m_texture, &srcrect, &dstrect);
    }
    SDL_RenderPresent(renderer);


}


#include "EventHandler.h"




EventHandler::EventHandler()
{
    //ctor
}

EventHandler::~EventHandler()
{
    //dtor
}

string EventHandler::getEvent()
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

                printf( ", Name: %s", SDL_GetKeyName( event.key.keysym.sym ) );
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

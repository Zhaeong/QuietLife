#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <string>
#include <SDL2/SDL.h>
using namespace std;

class EventHandler
{
    public:
        SDL_Event event;
        EventHandler();
        virtual ~EventHandler();

        string getEvent();

    protected:

    private:
};

#endif // EVENTHANDLER_H

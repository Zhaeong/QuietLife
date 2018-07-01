#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SDL2/SDL.h>
#include <string>
using namespace std;

class GameObj
{
    public:
        GameObj();
        virtual ~GameObj();

        int x_location;
        int y_location;

        int width;
        int height;

        string imageLocation;
        SDL_Surface *surface;

        void loadSurface(string surfaceLocation);

    protected:

    private:
};

#endif // GAMEOBJ_H

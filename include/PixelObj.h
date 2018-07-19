#ifndef PIXELOBJ_H
#define PIXELOBJ_H

//Standard Lib


//Project Lib
#include <SDL.h>



class PixelObj
{
    public:
        PixelObj(int X, int Y, Uint32 Color);
        virtual ~PixelObj();

        int m_X;
        int m_Y;
        Uint32 m_Color;

    protected:

    private:
};

#endif // PIXELOBJ_H

#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <GameObj.h>

//Checks the source rect and see if it hits the targetrect
inline string hitBoundary(int xSource, int ySource, int wSource, int hSource, int xTarget, int yTarget, int wTarget, int hTarget)
{
    string outPut = "NONE";

    //Check left
    if(xSource < xTarget)
    {
        outPut = "LEFT";
    }

    if(xSource + wSource > xTarget + wTarget)
    {
        outPut = "RIGHT";
    }

    if(ySource < yTarget)
    {
        outPut = "TOP";
    }

    if(ySource + hSource > yTarget + hTarget)
    {
        outPut = "BOTTOM";
    }

    return outPut;
}


inline int convertPlayerXtoCamX(GameObj *playerObj, SDL_Rect *camRect)
{
    return (playerObj->m_xPos + (playerObj->m_width  /2)) - (camRect->w/2);
}

inline int convertPlayerYtoCamY(GameObj *playerObj, SDL_Rect *camRect)
{
    return (playerObj->m_yPos + (playerObj->m_height  /2)) - (camRect->h/2);
}




#endif // GAMEUTIL_H_INCLUDED

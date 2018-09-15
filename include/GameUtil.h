#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObj.h"
#include "PixelObj.h"
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


inline int convertPlayerXtoCamX(SDL_Rect *playerRect, SDL_Rect *camRect)
{
    return (playerRect->x + (playerRect->w  /2)) - (camRect->w/2);
}

inline int convertPlayerYtoCamY(SDL_Rect *playerRect, SDL_Rect *camRect)
{
    return (playerRect->y + (playerRect->h  /2)) - (camRect->h/2);
}

inline bool sortByX(const PixelObj &lhs, const PixelObj &rhs) { return lhs.m_X < rhs.m_X; }

inline string delSpaces(string &str)
{
   for(unsigned int i=0; i<str.length(); i++)
   {
       if(str[i] == ' ' || str[i] == '\t')
       {
            str.erase(i,1);
       }
   }

   return str;
}
#endif // GAMEUTIL_H_INCLUDED

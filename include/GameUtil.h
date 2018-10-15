#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObj.h"
#include "PixelObj.h"
#include "TextureObj.h"

const bool DEBUGMODE = true;

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
/*
    if(ySource < yTarget)
    {
        outPut = "TOP";
    }

    if(ySource + hSource > yTarget + hTarget)
    {
        outPut = "BOTTOM";
    }
*/
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

inline bool sortByZval(const TextureObj &lhs, const TextureObj &rhs)
{
    return lhs.mZval < rhs.mZval;
}

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

inline bool horizontalColDetector(int xPos1, int width1, int xPos2, int width2)
{
    if( (xPos1 + width1) < xPos2)
    {
        return false;
    }

    if ((xPos2 + width2) < xPos1)
    {
        return false;
    }

    return true;
}

inline bool pointInBox(int pointX, int pointY, int boxXpos, int boxYpos, int boxWidth, int boxHeight)
{
    if(pointX >= boxXpos &&
       pointX <= (boxXpos + boxWidth) &&
       pointY >= boxYpos &&
       pointY <= (boxYpos + boxHeight))
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif // GAMEUTIL_H_INCLUDED

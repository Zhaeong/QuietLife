#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObj.h"
#include "PixelObj.h"
#include "TextureObj.h"
#include "LinkObj.h"

const bool DEBUGMODE = true;

//Temple OS H and W
const int GAMEWIDTH = 640;
const int GAMEHEIGHT = 480;

class TextureObj;


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

inline string hitBoundary1D(int xSource, int wSource, int left, int right)
{
    string outPut = "NONE";

    //Check left
    if(xSource < left)
    {
        outPut = "LEFT";
    }

    if(xSource + wSource > right)
    {
        outPut = "RIGHT";
    }

    return outPut;
}


inline int convertPlayerXtoCamX(int playerX, int playerWidth, SDL_Rect *camRect)
{
    return (playerX + (playerWidth  /2)) - (camRect->w/2);
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

inline bool axisColDetector(int axisPos1, int axisWidth1, int axisPos2, int axisWidth2)
{
    if( (axisPos1 + axisWidth1) <= axisPos2)
    {
        return false;
    }

    if ((axisPos2 + axisWidth2) <= axisPos1)
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

inline bool pointInTexture(int pointX, int pointY, TextureObj tObj)
{
    if(pointX >= tObj.mPosition.x &&
       pointX <= (tObj.mPosition.x + tObj.mWidth) &&
       pointY >= tObj.mPosition.y &&
       pointY <= (tObj.mPosition.y + tObj.mHeight))
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool textureCollide(TextureObj tObjA, TextureObj tObjB)
{
    if(axisColDetector(tObjA.mPosition.x, tObjA.mWidth, tObjB.mPosition.x, tObjB.mWidth)
       &&
       axisColDetector(tObjA.mPosition.y, tObjA.mHeight, tObjB.mPosition.y, tObjB.mHeight))
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool boxCollideLink(int boxX, int boxWidth, int boxY, int boxHeight, LinkObj lObj)
{
    if(axisColDetector(boxX, boxWidth, lObj.mXpos, lObj.mWidth)
       &&
       axisColDetector(boxY, boxHeight, lObj.mYpos, lObj.mHeight))
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif // GAMEUTIL_H_INCLUDED

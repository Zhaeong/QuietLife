#include "LinkObj.h"

LinkObj::LinkObj(string name, int xPos, int yPos, int width, int height)
{
    mName = name;
    mXpos = xPos;
    mYpos = yPos;
    mWidth = width;
    mHeight = height;
}

LinkObj::~LinkObj()
{
    //dtor
}

#include "LinkObj.h"

LinkObj::LinkObj(string name, int xPos, int yPos, int width, int height, int playerX, int playerY)
{
    mName = name;
    mXpos = xPos;
    mYpos = yPos;
    mWidth = width;
    mHeight = height;
    mPlayerX = playerX;
    mPlayerY = playerY;
}

LinkObj::~LinkObj()
{
    //dtor
}

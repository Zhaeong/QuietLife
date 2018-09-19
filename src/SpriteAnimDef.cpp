#include "SpriteAnimDef.h"

SpriteAnimDef::SpriteAnimDef(string pName)
{
    picName = pName;
    xPos = 0;
    yPos = 0;

    rot = 0;
    xMid = 0;
    yMid = 0;

    rotStart = 0;
    rotEnd = 0;
}

SpriteAnimDef::~SpriteAnimDef()
{
    //dtor
}

void SpriteAnimDef::setPos(int x, int y)
{
    xPos = x;
    yPos = y;

}
void SpriteAnimDef::setRot(int r)
{
    rot = r;
}
void SpriteAnimDef::setMid(int x, int y)
{
    xMid = x;
    yMid = y;
}
void SpriteAnimDef::setRotBound(int rStart, int rEnd)
{
    rotStart = rStart;
    rotEnd = rEnd;
}

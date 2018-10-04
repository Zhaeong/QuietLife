#include "SceneObj.h"

SceneObj::SceneObj(string name, string imgPath, int top, int bottom, int left, int right, int playerX, int playerY)
{
    mName = name;
    mPath = imgPath;
    mTop = top;
    mBottom = bottom;
    mLeft = left;
    mRight = right;

    mPlayerX = playerX;
    mPlayerY = playerY;
}

SceneObj::~SceneObj()
{
    //dtor
}

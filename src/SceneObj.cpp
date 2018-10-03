#include "SceneObj.h"

SceneObj::SceneObj(string name, string imgPath, int top, int bottom, int left, int right)
{
    mName = name;
    mPath = imgPath;
    mTop = top;
    mBottom = bottom;
    mLeft = left;
    mRight = right;
}

SceneObj::~SceneObj()
{
    //dtor
}

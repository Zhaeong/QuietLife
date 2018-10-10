#include "AnimDef.h"

AnimDef::AnimDef(string aName)
{
    //ctor

    animName = aName;


}

AnimDef::~AnimDef()
{
    //dtor
}

void AnimDef::addSpriteAnime(SpriteAnimDef SAD)
{
    mSpriteAnimArray.push_back(SAD);
}

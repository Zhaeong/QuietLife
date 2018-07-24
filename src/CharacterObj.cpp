#include "CharacterObj.h"

CharacterObj::CharacterObj(SDLHandler *SH, string name)
{
    //ctor
    mName = name;
    mSH = SH;
}

CharacterObj::~CharacterObj()
{
    //dtor
}


void CharacterObj::addTexture(TextureObj textureObj)
{
    mTextureArray.push_back(textureObj);
}

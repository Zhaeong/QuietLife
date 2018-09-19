#ifndef ANIMDEF_H
#define ANIMDEF_H

#include <string>

#include <vector>

#include "SpriteAnimDef.h"

using namespace std;

class AnimDef
{
    public:
        AnimDef(string aName);
        virtual ~AnimDef();

        string animName;

        vector<SpriteAnimDef> mSpriteAnimArray;

        void addSpriteAnime(SpriteAnimDef SAD);



    protected:

    private:
};

#endif // ANIMDEF_H

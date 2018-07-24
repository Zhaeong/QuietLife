#ifndef CHARACTEROBJ_H
#define CHARACTEROBJ_H

#include <vector>
#include <string>

#include "TextureObj.h"
#include "SDLHandler.h"

using namespace std;


class CharacterObj
{
    public:
        CharacterObj(SDLHandler *SH, string name);
        virtual ~CharacterObj();

        string mName;
        SDLHandler *mSH;
        vector<TextureObj> mTextureArray;


        void addTexture(TextureObj textureObj);

    protected:

    private:
};

#endif // CHARACTEROBJ_H

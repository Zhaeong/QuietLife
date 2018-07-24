#ifndef TEXTUREOBJ_H
#define TEXTUREOBJ_H

#include "SDLHandler.h"


class TextureObj
{
    public:
        TextureObj(SDLHandler *SH, string imgLocation);
        virtual ~TextureObj();


        SDLHandler *mSH;


    protected:

    private:
};

#endif // TEXTUREOBJ_H

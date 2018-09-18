#ifndef ANIMDEF_H
#define ANIMDEF_H

#include <string>

using namespace std;

class AnimDef
{
    public:
        AnimDef();
        virtual ~AnimDef();

        string animName;

        //Rotation Controls
        int mRotation;
        int mRotateStart;
        int mRotateEnd;

    protected:

    private:
};

#endif // ANIMDEF_H

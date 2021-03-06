#ifndef SPRITEANIMDEF_H
#define SPRITEANIMDEF_H

#include <string>


using namespace std;


class SpriteAnimDef
{
    public:
        SpriteAnimDef(string pName);
        virtual ~SpriteAnimDef();

        string picName;

        //Rotation Controls
        int xPos;
        int yPos;

        int rot;
        int xMid;
        int yMid;


        int rotStart;
        int rotEnd;

        int zVal;
        int moveSpeed;

        void setPos(int x, int y);
        void setRot(int rot);
        void setMid(int x, int y);
        void setRotBound(int start, int end);
        void setZval(int zval);
        void setSpeed(int speed);

    protected:

    private:
};

#endif // SPRITEANIMDEF_H

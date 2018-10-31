#ifndef LINKOBJ_H
#define LINKOBJ_H

#include <string>

using namespace std;

class LinkObj
{
    public:
        LinkObj(string name, int xPos, int yPos, int width, int height, int playerX, int playerY);
        virtual ~LinkObj();

        string mName;
        int mXpos;
        int mYpos;

        int mWidth;
        int mHeight;

        int mPlayerX;
        int mPlayerY;

    protected:

    private:
};

#endif // LINKDEF_H

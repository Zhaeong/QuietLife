#ifndef LINKOBJ_H
#define LINKOBJ_H

#include <string>
using namespace std;

class LinkObj
{
    public:
        LinkObj(string name, int xPos, int yPos, int width, int height);
        virtual ~LinkObj();

        string mName;
        int mXpos;
        int mYpos;

        int mWidth;
        int mHeight;

    protected:

    private:
};

#endif // LINKDEF_H

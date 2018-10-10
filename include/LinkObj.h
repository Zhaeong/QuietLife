#ifndef LINKOBJ_H
#define LINKOBJ_H

#include <string>
using namespace std;

class LinkObj
{
    public:
        LinkObj(string name, int xPos, int width);
        virtual ~LinkObj();

        string mName;
        int mXpos;
        int mWidth;

    protected:

    private:
};

#endif // LINKDEF_H

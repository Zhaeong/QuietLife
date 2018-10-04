#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include <string>
using namespace std;
class SceneObj
{
    public:
        SceneObj(string name, string imgPath, int top, int bottom, int left, int right, int playerX, int playerY);
        virtual ~SceneObj();

        string mName;
        string mPath;

        int mTop;
        int mBottom;
        int mLeft;
        int mRight;

        int mPlayerX;
        int mPlayerY;




    protected:

    private:
};

#endif // SCENEOBJ_H

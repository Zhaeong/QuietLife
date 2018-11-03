#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include <string>
#include <vector>
#include "LinkObj.h"
#include "TextureObj.h"
using namespace std;


class SceneObj
{
    public:
        //SceneObj(string name, string imgPath, int top, int bottom, int left, int right, int playerX, int playerY);

        SceneObj();
        virtual ~SceneObj();

        string mName;
        string mPath;

        int mTop;
        int mBottom;
        int mLeft;
        int mRight;

        int mPlayerX;
        int mPlayerY;

        int mCamX;
        int mCamY;

        vector<LinkObj> mLinkObjArray;

        vector<TextureObj> mTextureObjectArray;

        void addLinkObj(LinkObj lObj);

        void addTextureObj(TextureObj tObj);


    protected:

    private:
};

#endif // SCENEOBJ_H

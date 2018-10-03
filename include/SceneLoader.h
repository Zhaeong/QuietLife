#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>
#include <string>

#include <dirent.h>
#include <fstream>

#include "GameUtil.h"
#include "TextureObj.h"
#include "SceneObj.h"
using namespace std;

class SceneLoader
{
    public:
        SceneLoader();
        virtual ~SceneLoader();

        TextureObj *backGroundObj;

        int minBoundX;
        int minBoundY;
        int maxBoundX;
        int maxBoundY;

        vector<SceneObj> mSceneObjArray;

        void loadScenesFromDirectory(string dirPath);


    protected:

    private:
};

#endif // SCENELOADER_H

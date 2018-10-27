#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <vector>
#include <string>

#include <dirent.h>
#include <fstream>

#include "GameUtil.h"
#include "TextureObj.h"
#include "SceneObj.h"

#include "LinkObj.h"

using namespace std;

class SceneLoader
{
    public:
        SceneLoader(SDLHandler *SH);
        virtual ~SceneLoader();

        SDLHandler *mSH;

        TextureObj *backGroundTexture;

        SceneObj mCurrentScene;

        int playerInitX;
        int playerInitY;

        vector<SceneObj> mSceneObjArray;



        void loadScenesFromDirectory(string dirPath);

        void loadScene(string sceneName);

        void renderScene(SDL_Rect cameraRect);


    protected:

    private:
};

#endif // SCENELOADER_H

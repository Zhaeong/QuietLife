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

#include "Game.h"

using namespace std;

class Game;


class SceneLoader
{
    public:
        SceneLoader(SDLHandler *SH, Game *mainGame);
        virtual ~SceneLoader();

        SDLHandler *mSH;

        Game *mMainGame;

        TextureObj *backGroundTexture;

        TextureObj *leftBound;
        TextureObj *rightBound;

        SceneObj mCurrentScene;

        int playerInitX;
        int playerInitY;

        vector<SceneObj> mSceneObjArray;



        void loadScenesFromDirectory(string dirPath);

        void loadScene(string sceneName);
        void loadScene(LinkObj linkCol);

        SceneObj* getScene(string sceneName);

        void renderScene(SDL_Rect cameraRect);


    protected:

    private:
};

#endif // SCENELOADER_H

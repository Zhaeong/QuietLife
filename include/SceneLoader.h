#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "TextureObj.h"

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

    protected:

    private:
};

#endif // SCENELOADER_H

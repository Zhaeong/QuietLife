#include "SceneLoader.h"

SceneLoader::SceneLoader(SDLHandler *SH, Game *mainGame)
{
    mSH = SH;

    mMainGame = mainGame;

    leftBound = new TextureObj(mSH, "res/png/boundTexture.png");
    rightBound = new TextureObj(mSH, "res/png/boundTexture.png");
}

SceneLoader::~SceneLoader()
{
    //dtor
}

void SceneLoader::loadScenesFromDirectory(string dirPath)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirPath.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            string fileName = ent->d_name;
            //cout << fileName;


            string filePrefix = fileName.substr(0, fileName.find("."));
            string fileSuffix = fileName.substr(fileName.find("."), fileName.length());

            if(fileSuffix == ".scene")
            {
                cout << "\nFound Scene: " + filePrefix + "\n";

                string fullPath = dirPath + "\\" + fileName;


                string line;
                ifstream myfile (fullPath);
                if (myfile.is_open())
                {
                    SceneObj newScene;
                    while ( getline (myfile,line) )
                    {
                        if(line == "STARTDEF")
                        {
                            string sceneName;
                            string scenePath;

                            int top;
                            int bottom;
                            int left;
                            int right;
                            int playerX = 0;
                            int playerY = 0;

                            int camX = 0;
                            int camY = 0;

                            //Start Texture means getting a single texture info
                            while (line != "ENDDEF" && !myfile.eof())
                            {
                                getline (myfile,line);

                                //The npos checks if the string line contains :
                                //Because if not then it is not a variable line
                                if(line.length() > 0 && line.find(':') != string::npos)
                                {
                                    line = delSpaces(line);
                                    string param = line.substr(0, line.find(":"));

                                    // + 1 because without it we include the : in the string
                                    string value = line.substr(line.find(":") + 1, line.length());
                                    //cout << "param:" << param << " val:" << value << "\n";

                                    if(param == "NAME")
                                    {
                                        sceneName = value;
                                        scenePath = dirPath + "\\" + value;
                                    }
                                    else if (param == "TOP")
                                    {
                                        top = stoi(value);
                                    }
                                    else if (param == "BOTTOM")
                                    {
                                        bottom = stoi(value);
                                    }
                                    else if (param == "LEFT")
                                    {
                                        left = stoi(value);
                                    }
                                    else if (param == "RIGHT")
                                    {
                                        right = stoi(value);
                                    }
                                    else if (param == "PLAYERX")
                                    {
                                        playerX = stoi(value);
                                    }
                                    else if (param == "PLAYERY")
                                    {
                                        playerY = stoi(value);
                                    }
                                    else if (param == "CAMX")
                                    {
                                        camX = stoi(value);
                                    }
                                    else if (param == "CAMY")
                                    {
                                        camY = stoi(value);
                                    }
                                    else
                                    {
                                        cout << "Warning INVALID Param" + param + "\n";
                                    }

                                }
                                else if(line == "ENDDEF")
                                {
                                    //cout << "Reached end of Scene Def for" + fullPath + "\n";
                                }
                                else
                                {
                                    cout << "ERROR Parsing scene file:" << fullPath;
                                }
                            }

                            //After while loop it should contain all the relevant fields for passing into animation

                            newScene.mName = sceneName;
                            newScene.mPath = scenePath;
                            newScene.mTop = top;
                            newScene.mBottom = bottom;
                            newScene.mLeft = left;
                            newScene.mRight = right;
                            newScene.mPlayerX = playerX;
                            newScene.mPlayerY = playerY;
                            newScene.mCamX = camX;
                            newScene.mCamY = camY;

                        }
                        else if(line == "LINKSTART")
                        {
                            string linkName;

                            string imgPath;

                            int xPos = 0;
                            int yPos = 0;

                            int playerLinkX = 0;
                            int playerLinkY = 0;

                            int camX = 0;
                            int camY = 0;

                            //Start Texture means getting a single texture info
                            while (line != "LINKEND" && !myfile.eof())
                            {
                                getline (myfile,line);

                                //The npos checks if the string line contains :
                                //Because if not then it is not a variable line
                                if(line.length() > 0 && line.find(':') != string::npos)
                                {
                                    line = delSpaces(line);
                                    string param = line.substr(0, line.find(":"));

                                    // + 1 because without it we include the : in the string
                                    string value = line.substr(line.find(":") + 1, line.length());
                                    //cout << "param:" << param << " val:" << value << "\n";

                                    if(param == "NAME")
                                    {
                                        linkName = value;
                                    }
                                    else if (param == "IMG")
                                    {
                                        imgPath = dirPath + "\\" + value;

                                    }
                                    else if (param == "XPOS")
                                    {
                                        xPos = stoi(value);
                                    }
                                    else if (param == "YPOS")
                                    {
                                        yPos = stoi(value);
                                    }
                                    else if (param == "PLAYERX")
                                    {
                                        playerLinkX = stoi(value);
                                    }
                                    else if (param == "PLAYERY")
                                    {
                                        playerLinkY = stoi(value);
                                    }
                                    else if (param == "CAMX")
                                    {
                                        camX = stoi(value);
                                    }
                                    else if (param == "CAMY")
                                    {
                                        camY = stoi(value);
                                    }
                                    else
                                    {
                                        cout << "Warning INVALID Param" + param + "\n";
                                    }

                                }
                                else if(line == "LINKEND")
                                {
                                    //cout << "Reached end of Scene Def for" + fullPath + "\n";
                                }
                                else
                                {
                                    cout << "ERROR Parsing scene file:" << fullPath;
                                }
                            }

                            //Add the img of the link
                            TextureObj newTexObj(mSH, imgPath);
                            newTexObj.setPos(xPos, yPos, 0);
                            newScene.addTextureObj(newTexObj);


                            //After while loop it should contain all the relevant fields for passing into animation
                            LinkObj newLink(linkName,
                                            xPos,
                                            yPos,
                                            newTexObj.mWidth,
                                            newTexObj.mHeight,
                                            playerLinkX,
                                            playerLinkY,
                                            camX,
                                            camY);
                            newScene.addLinkObj(newLink);


                        }
                        else if(line == "TEXTURESTART")
                        {
                            string texturePath;


                            int xPos;
                            int yPos;

                            //Start Texture means getting a single texture info
                            while (line != "TEXTUREEND" && !myfile.eof())
                            {
                                getline (myfile,line);

                                //The npos checks if the string line contains :
                                //Because if not then it is not a variable line
                                if(line.length() > 0 && line.find(':') != string::npos)
                                {
                                    line = delSpaces(line);
                                    string param = line.substr(0, line.find(":"));

                                    // + 1 because without it we include the : in the string
                                    string value = line.substr(line.find(":") + 1, line.length());
                                    //cout << "param:" << param << " val:" << value << "\n";

                                    if(param == "PATH")
                                    {
                                        texturePath = dirPath + "\\" + value;
                                    }
                                    else if (param == "XPOS")
                                    {
                                        xPos = stoi(value);
                                    }
                                    else if (param == "YPOS")
                                    {
                                        yPos = stoi(value);
                                    }
                                    else
                                    {
                                        cout << "Warning INVALID Param" + param + "\n";
                                    }

                                }
                                else if(line == "TEXTUREEND")
                                {
                                    //cout << "Reached end of Scene Def for" + fullPath + "\n";
                                }
                                else
                                {
                                    cout << "ERROR Parsing scene file:" << fullPath;
                                }
                            }

                            //After while loop it should contain all the relevant fields for passing into animation
                            TextureObj newTexObj(mSH, texturePath);
                            newTexObj.setPos(xPos, yPos, 0);
                            newScene.addTextureObj(newTexObj);
                        }



                    }

                    mSceneObjArray.push_back(newScene);
                    myfile.close();
                }
                else
                {
                    cout << "Unable to open file";
                }



            }
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        string errorMsg = "Couldn't open:" + dirPath;
        perror (errorMsg.c_str());
        //return EXIT_FAILURE;
    }

}


void SceneLoader::loadScene(LinkObj linkCol)
{

    string sceneName = linkCol.mName;
    for(unsigned int i = 0; i < mSceneObjArray.size(); i++)
    {
        SceneObj& sObj = mSceneObjArray[i];
        string sObjName = sObj.mName;
        if(sceneName == sObjName)
        {

            backGroundTexture = new TextureObj(mSH, sObj.mPath);


            //Instead of using the text defined boundaries just use the texture size

            if(mMainGame->playerChar != NULL)
            {
                cout << "playerX: " << mMainGame->playerChar->mXpos << "\n";
                cout << "playerY: " << mMainGame->playerChar->mYpos << "\n";

                cout << "playerXset: " << linkCol.mPlayerX << "\n";
                cout << "playerYset: " << linkCol.mPlayerY << "\n";



                mMainGame->playerChar->mXpos = linkCol.mPlayerX + (mMainGame->playerChar->mWidth / 2);
                mMainGame->playerChar->mYpos = linkCol.mPlayerY;

            }
            if(mMainGame->cameraRect != NULL)
            {
                cout << "camXset: " << linkCol.mCamX << "\n";
                cout << "camYset: " << linkCol.mCamY << "\n";
                mMainGame->setCamPos(linkCol.mCamX, linkCol.mCamY);
            }

            cout << "Loaded Scene: " << sceneName << " Path: " + sObj.mPath << "\n";
            mCurrentScene = sObj;
            return;
        }
    }

    cout << "Couldn't find scene:" << sceneName << "\n";
}

void SceneLoader::loadScene(string sceneName)
{
    for(unsigned int i = 0; i < mSceneObjArray.size(); i++)
    {
        SceneObj& sObj = mSceneObjArray[i];
        string sObjName = sObj.mName;
        if(sceneName == sObjName)
        {

            backGroundTexture = new TextureObj(mSH, sObj.mPath);

            //Instead of using the text defined boundaries just use the texture size
            playerInitX = sObj.mPlayerX;
            playerInitY = sObj.mPlayerY;

            if(mMainGame->playerChar != NULL)
            {
                cout << "playerX: " << mMainGame->playerChar->mXpos << "\n";
                cout << "playerY: " << mMainGame->playerChar->mYpos << "\n";

                cout << "playerXset: " << sObj.mPlayerX << "\n";
                cout << "playerYset: " << sObj.mPlayerY << "\n";

                mMainGame->playerChar->mXpos = sObj.mPlayerX + (mMainGame->playerChar->mWidth / 2);
                mMainGame->playerChar->mYpos = sObj.mPlayerY;
            }

            if(mMainGame->cameraRect != NULL)
            {
                cout << "camXset: " << sObj.mCamX << "\n";
                cout << "camYset: " << sObj.mCamY << "\n";
                mMainGame->setCamPos(sObj.mCamX, sObj.mCamY);
            }

            cout << "Loaded Scene: " << sceneName << " Path: " + sObj.mPath << "\n";
            mCurrentScene = sObj;
            return;
        }
    }

    cout << "Couldn't find scene:" << sceneName << "\n";


}

SceneObj* SceneLoader::getScene(string sceneName)
{
    for(unsigned int i = 0; i < mSceneObjArray.size(); i++)
    {

        if(sceneName == mSceneObjArray[i].mName)
        {
            return &mSceneObjArray[i];
        }
    }

    cout << "Couldn't find scene in getScene:" << sceneName << "\n";
    return NULL;
}

void SceneLoader::renderScene(SDL_Rect cameraRect)
{
    SDL_Rect dstRectBckObj;

    dstRectBckObj.h = cameraRect.h;
    dstRectBckObj.w = cameraRect.w;
    dstRectBckObj.x = 0;
    dstRectBckObj.y = 0;

    backGroundTexture->renderTexture(cameraRect, dstRectBckObj, SDL_FLIP_NONE);

    //Render left and right boundaries
    //The boundaries are so that its mapped to the boundaries of the scene
    //This avoids messy stuff that requires mapping each pixel in background texture
    //with the scene boundaries

    SDL_Rect boundSrc;
    boundSrc.h = rightBound->mHeight;
    boundSrc.w = rightBound->mWidth;
    boundSrc.x = 0;
    boundSrc.y = 0;

    SDL_Rect rightBoundDst;
    rightBoundDst.h = 480;
    rightBoundDst.w = 320;
    rightBoundDst.x = mCurrentScene.mRight - cameraRect.x;
    rightBoundDst.y = 0;

    rightBound->renderTexture(boundSrc, rightBoundDst, SDL_FLIP_NONE);

    SDL_Rect leftBoundDst;
    leftBoundDst.h = 480;
    leftBoundDst.w = 320;
    leftBoundDst.x = mCurrentScene.mLeft - cameraRect.x - 320;
    leftBoundDst.y = 0;

    leftBound->renderTexture(boundSrc, leftBoundDst, SDL_FLIP_NONE);

    //Then render rest of the objects in the scene
    for(TextureObj tObj : mCurrentScene.mTextureObjectArray)
    {
        //should do a boundary check to see if object is in view before rendering
        //Need to convert position of obj to cameras position
        SDL_Rect srcRect;
        SDL_Rect dstRectObj;

        srcRect.x=0;
        srcRect.y=0;
        srcRect.h=tObj.mHeight;
        srcRect.w=tObj.mWidth;

        dstRectObj.h = tObj.mHeight;
        dstRectObj.w = tObj.mWidth;

        //The position is the objects position minus the camera position
        //in order to get the object's place in accordance with the camera
        dstRectObj.x = tObj.mPosition.x - cameraRect.x ;
        dstRectObj.y = tObj.mPosition.y - cameraRect.y;

        tObj.renderTexture(srcRect, dstRectObj, SDL_FLIP_NONE);
    }

}

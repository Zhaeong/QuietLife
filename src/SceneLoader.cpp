#include "SceneLoader.h"

SceneLoader::SceneLoader(SDLHandler *SH)
{
    mSH = SH;
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
                            int playerX;
                            int playerY;

                            //Start Texture means getting a single texture info
                            while (line != "ENDDEF" && !myfile.eof())
                            {
                                getline (myfile,line);
                                cout << "The current line is:" << line << "\n";

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

                            SceneObj newScene(sceneName, scenePath, top, bottom, left, right, playerX, playerY);


                            mSceneObjArray.push_back(newScene);


                        }
                        cout << "END" << line << '\n';
                    }

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

void SceneLoader::loadScene(string sceneName)
{
    bool sceneFound = false;
    for(unsigned int i = 0; i < mSceneObjArray.size(); i++)
    {
        SceneObj& sObj = mSceneObjArray[i];
        string sObjName = sObj.mName;
        if(sceneName == sObjName)
        {
            sceneFound = true;
            backGroundTexture = new TextureObj(mSH, sObj.mPath);
            minBoundX = sObj.mLeft;
            minBoundY = sObj.mTop;
            maxBoundX = sObj.mRight;
            maxBoundY = sObj.mBottom;
            playerInitX = sObj.mPlayerX;
            playerInitY = sObj.mPlayerY;
            cout << "Loaded Scene: " << sceneName << " Path: " + sObj.mPath << "\n";
            break;
        }
    }
    if (!sceneFound)
    {
        cout << "Couldn't find scene:" << sceneName << "\n";
    }
}

void SceneLoader::renderScene(SDL_Rect cameraRect)
{
    //cout << "rendering scene" << backGroundTexture->mImgLocation << " here";
    //Render background
    SDL_Rect dstRectBckObj;

    dstRectBckObj.h = cameraRect.h;
    dstRectBckObj.w = cameraRect.w;
    dstRectBckObj.x = 0;
    dstRectBckObj.y = 0;


    backGroundTexture->renderTexture(cameraRect, dstRectBckObj, SDL_FLIP_NONE);

}

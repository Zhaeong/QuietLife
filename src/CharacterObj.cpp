#include "CharacterObj.h"

CharacterObj::CharacterObj(SDLHandler *SH, string name)
{
    cout << "Creating Character: " << name << "\n";
    //ctor
    mName = name;
    mSH = SH;

    setPos(0,0);
}

CharacterObj::~CharacterObj()
{
    //dtor
}


void CharacterObj::addTexture(TextureObj textureObj)
{
    mTextureArray.push_back(textureObj);
}

void CharacterObj::render(int xPos, int yPos)
{
    //Render objects in game array
    for(unsigned int i = 0; i < mTextureArray.size(); i++)
    {
        TextureObj& tObj = mTextureArray[i];

        SDL_Rect srcRect;
        SDL_Rect dstRect;

        srcRect.x=0;
        srcRect.y=0;
        srcRect.h=tObj.mHeight;
        srcRect.w=tObj.mWidth;

        //To get the position of the texture relative to the character
        dstRect.x = xPos + tObj.mPosition.x;
        dstRect.y = yPos + tObj.mPosition.y;
        dstRect.h = tObj.mHeight;
        dstRect.w = tObj.mWidth;


        tObj.renderTexture(srcRect, dstRect);
    }
}

void CharacterObj::setPos(int xPos, int yPos)
{
    mXpos = xPos;
    mYpos = yPos;
}

void CharacterObj::setDimension(int width, int height)
{
    mWidth = width;
    mHeight = height;
}

void CharacterObj::getAnimate(string dirPath)
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

            if(fileSuffix == ".anim")
            {
                cout << "\nFound Anim: " + filePrefix + "\n";

                string fullPath = dirPath + "\\" + fileName;


                string line;
                ifstream myfile (fullPath);
                if (myfile.is_open())
                {
                    while ( getline (myfile,line) )
                    {
                        if(line == "STARTTEXTURE")
                        {
                            string texturePath;
                            int xPos;
                            int yPos;
                            int rot;
                            int xMid;
                            int yMid;
                            int rotStart;
                            int rotEnd;
                            //Start Texture means getting a single texture info
                            while (line != "ENDTEXTURE" && !myfile.eof())
                            {


                                getline (myfile,line);
                                cout << "The current line is:" << line << "\n";

                                //The npos checks if the string line contains :
                                //Because if not then it is not a variable line
                                if(line.length() > 0 && line.find(':') != string::npos)
                                {
                                    string param = line.substr(0, line.find(":"));

                                    // + 1 because without it we include the : in the string
                                    string value = line.substr(line.find(":") + 1, line.length());
                                    cout << "param:" << param << " val:" << value << "\n";

                                    if(param == "NAME")
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
                                    else if (param == "ROTATION")
                                    {
                                        rot = stoi(value);
                                    }
                                    else if (param == "XMID")
                                    {
                                        xMid = stoi(value);
                                    }
                                    else if (param == "YMID")
                                    {
                                        yMid = stoi(value);
                                    }
                                    else if (param == "ROTSTART")
                                    {
                                        rotStart = stoi(value);
                                    }
                                    else if (param == "ROTEND")
                                    {
                                        rotEnd = stoi(value);
                                    }
                                    else
                                    {
                                        cout << "Warning INVALID Param" + param + "\n";
                                    }

                                }
                                else
                                {
                                    cout << "ERROR Parsing anim file" << fullPath;
                                }
                            }

                            //After while loop it should contain all the relevant fields for passing into animation

                            string fullPath = dirPath + "\\" + fileName;

                            TextureObj fileTexture(mSH, texturePath);
                            fileTexture.setRotateTargets(rotStart, rotEnd);
                            fileTexture.setMiddle(xMid, yMid);
                            fileTexture.setPos(xPos, yPos, rot);
                            fileTexture.removeWhitespace();


                            addTexture(fileTexture);

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

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
                      cout << line << '\n';
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

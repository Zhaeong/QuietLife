#ifndef GAMEUTIL_H_INCLUDED
#define GAMEUTIL_H_INCLUDED
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

inline string hitBoundary(int xSource, int ySource, int wSource, int hSource, int xTarget, int yTarget, int wTarget, int hTarget)
{
    string outPut = "NONE";

    //Check left
    if(xSource < xTarget)
    {
        outPut = "LEFT";
    }

    if(xSource + wSource > xTarget + wTarget)
    {
        outPut = "RIGHT";
    }

    if(ySource < yTarget)
    {
        outPut = "TOP";
    }

    if(ySource + hSource > yTarget + hTarget)
    {
        outPut = "BOTTOM";
    }

    return outPut;


}


inline SDL_Texture* loadFontTexture(SDL_Renderer *gRenderer, TTF_Font *font, string fontText, SDL_Color fontColor)
{
    //Get rid of preexisting texture
    //free();
    //Render text surface

    SDL_Texture *fontTexture;
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, fontText.c_str(), fontColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); }
    else
    { //Create texture from surface pixels
        fontTexture =  SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( fontTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        { //Get image dimensions
            //mWidth = textSurface->w;
            //mHeight = textSurface->h;
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    } //Return success
    return fontTexture;

}

#endif // GAMEUTIL_H_INCLUDED

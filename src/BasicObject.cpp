

#include "BasicObject.h"

BasicObject::BasicObject()
{
    mTexture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BasicObject::~BasicObject()
{
    Free();
}

int BasicObject::Random(const int& x)
{
    int m = x - 250;
    int random = rand() % m;
    return random;
}

bool BasicObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    if (loadedSurface != NULL)
    {
        //Remove image background
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        //Create Texture
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture != NULL)
        {
            rect.w = loadedSurface->w;
            rect.h = loadedSurface->h;
        }
        //Update the Surface
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}


void BasicObject::Free()
{

    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        rect.x = 0;
        rect.y = 0;
    }
}

void BasicObject::render(SDL_Renderer* screen,int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, rect.w, rect.h };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, mTexture, clip, &renderQuad, angle, center, flip);
}

bool BasicObject::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    //Calculate the sides of object1
    int left1 = object1.x;
    int right1 = object1.x + object1.w;
    int top1 = object1.y;
    int bottom1 = object1.y + object1.h;

    //Calculate the sides of object2
    int left2 = object2.x;
    int right2 = object2.x + object2.w;
    int top2 = object2.y;
    int bottom2 = object2.y + object2.h;

    //If any of the sides from object1 are outside of object2

    //Case 1
    if (bottom1 <= top2)
    {
        return false;
    }
    //Case 2
    if (top1 >= bottom2)
    {
        return false;
    }
    //Case 3
    if (right1 <= left2)
    {
        return false;
    }
    //Case 4
    if (left1 >= right2)
    {
        return false;
    }

    //If none of the sides from object1 are outside object2
    return true;
}

void BasicObject::show(SDL_Renderer* screen)
{
    render(screen, rect.x, rect.y, NULL);
}

void BasicObject::setColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void BasicObject::setBlendMode(const SDL_BlendMode& blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void BasicObject::setAlpha(const Uint8& alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

bool BasicObject::loadFromText(TTF_Font* font, std::string text, SDL_Color textColor, SDL_Renderer* screen)
{
    //Get rid of preexisting texture
    Free();

    SDL_Texture* textTexture = NULL;

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        if (textTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            rect.w = textSurface->w;
            rect.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    mTexture = textTexture;
    return mTexture != NULL;
}
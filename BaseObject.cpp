

#include "BaseObject.h"



BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface != NULL)
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture != NULL)
        {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    p_object_ = newTexture;
    return p_object_ != NULL;
}

void BaseObject::Free()
{

    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.x = 0;
        rect_.y = 0;
    }
}

void BaseObject::render(SDL_Renderer* screen,int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, rect_.w, rect_.h };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, p_object_, clip, &renderQuad, angle, center, flip);
}

void BaseObject::show(SDL_Renderer* screen)
{
    render(screen, rect_.x, rect_.y, NULL);
}

void BaseObject::setColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
    SDL_SetTextureColorMod(p_object_, red, green, blue);
}

void BaseObject::setBlendMode(const SDL_BlendMode& blending)
{
    SDL_SetTextureBlendMode(p_object_, blending);
}

void BaseObject::setAlpha(const Uint8& alpha)
{
    SDL_SetTextureAlphaMod(p_object_, alpha);
}
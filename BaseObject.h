
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip , double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void show(SDL_Renderer* screen);

	void Free();
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; };
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() { return p_object_; };
	int getWidth() { return rect_.w; }

	void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);
	void setAlpha(const Uint8& alpha);
	void setBlendMode(const SDL_BlendMode& blending);

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};


#endif
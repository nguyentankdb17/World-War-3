
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "General.h"

class BasicObject
{
public:
	BasicObject();
	~BasicObject();

	//Load Image and show on screen
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);

	void render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip , double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void show(SDL_Renderer* screen);

	//Make random value from y->x
	int Random(const int& x);

	void Free();

	//Set object rect
	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; };
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetObject() { return mTexture; };
	int getWidth() { return rect.w; }

	bool loadFromText(TTF_Font* font, std::string text, SDL_Color textColor, SDL_Renderer* screen);


	//Collision
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);
	void setAlpha(const Uint8& alpha);
	void setBlendMode(const SDL_BlendMode& blending);

protected:
	SDL_Texture* mTexture;
	SDL_Rect rect;
};


#endif
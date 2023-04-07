

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public BaseObject
{
public :
	static const int TANK_WIDTH = 250;
	static const int TANK_HEIGHT = 100;
	static const int TANK_VEL = 10;


	MainObject();
	void handleEvent(SDL_Event& e, SDL_Renderer* screen);
	void move();
	void showClips(std::string path, SDL_Renderer* screen);
	bool setClips(std::string path, SDL_Renderer* screen);
	SDL_Rect GetRectFrame();

	void SetBulletList(std::vector<Bullet*> bullet_list) { Bullet_list = bullet_list; }
	std::vector<Bullet*> GetBulletList() const { return Bullet_list; }
	void MakeBullet(SDL_Renderer* screen);
	void RemoveBullet(const int& index);

private :
	int x_vel;
	int y_vel;

	int frame;
	SDL_Rect frame_clip[4];

	

	std::vector < Bullet* > Bullet_list;
};

#endif
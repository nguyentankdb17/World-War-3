

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "General.h"
#include "BasicObject.h"
#include "Bullet.h"

class MainObject : public BasicObject
{
public :

	static const int TANK_WIDTH = 250;
	static const int TANK_HEIGHT = 100;
	static const int TANK_VEL = 10;
	int lives_left = 3;

	MainObject();
	//Hanlde when press
	void handleEvent(SDL_Event& e, SDL_Renderer* screen);
	void move();
	void showClips(std::string path, SDL_Renderer* screen);
	bool setClips(std::string path, SDL_Renderer* screen);
	SDL_Rect GetRectFrame();

	//Init and remove the bullet for main object
	void SetBulletList(std::vector<Bullet*> bullet_list) { Bullet_list = bullet_list; }
	std::vector<Bullet*> GetBulletList() const { return Bullet_list; }
	void MakeBullet(SDL_Renderer* screen);
	void RemoveBullet(const int& index);

	//Collision
	bool CheckCollisionToMainObject(const SDL_Rect& main_object, const SDL_Rect& threat);

private :
	int x_vel;
	int y_vel;

	int frame;
	int frame_width;
	int frame_height;

	SDL_Rect frame_clip[4];

	std::vector < Bullet* > Bullet_list;
};

#endif
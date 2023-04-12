

#ifndef THREATS_H
#define THREATS_H

#include "General.h"
#include "BasicObject.h"
#include "Bullet.h"

class Threats : public BasicObject
{
public :


	const int THREAT_WIDTH = 200;
	const int THREAT_HEIGHT = 100;
	int threat_lives;

	Threats();
	~Threats();


	//Set velocity
	void set_x_vel(const int& vel) { x_vel = vel; }
	void set_y_vel(const int& vel) { y_vel = vel; }

	//Get velocity
	int get_x_vel() const { return x_vel; }
	int get_y_vel() const { return y_vel; }

	//Move
	void Move(const int& x_border, const int& y_border);


	//Initialize the bullet for threat
	void SetBulletList(std::vector<Bullet*> bullet_list) { Bullet_list = bullet_list; }
	std::vector<Bullet*> GetBulletList() const { return Bullet_list; }
	void InitBullet(Bullet* p_bullet, std::string path , SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);

	void Reset(const int& x_border);
	void ResetBullet(Bullet* bullet);

	//Collision
	bool CheckCollisionToThreat(const SDL_Rect& threat, const SDL_Rect& bullet);

private:
	int x_vel;
	int y_vel;

	std::vector <Bullet*> Bullet_list;
};


#endif

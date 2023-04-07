

#ifndef THREATS_H
#define THREATS_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class Threats : public BaseObject
{
public :
	const int THREAT_WIDTH = 250;
	const int THREAT_HEIGHT = 100;

	Threats();
	~Threats();

	void set_x_val(const int& val) { x_val = val; }
	void set_y_val(const int& val) { y_val = val; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }
	void MoveLeft(const int& x_border, const int& y_border);
	void MoveRight(const int& x_border, const int& y_border);
	void MoveUp(const int& x_border, const int& y_border);
	void MoveDown(const int& x_border, const int& y_border);
	void MoveAround(const int& y_border);

	void SetBulletList(std::vector<Bullet*> bullet_list) { Bullet_list = bullet_list; }
	std::vector<Bullet*> GetBulletList() const { return Bullet_list; }
	void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);

private:
	int x_val;
	int y_val;

	std::vector <Bullet*> Bullet_list;
};


#endif

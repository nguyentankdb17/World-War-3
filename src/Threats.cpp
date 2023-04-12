
#include "Threats.h"

Threats::Threats()
{
	rect.x = SCREEN_WIDTH;
	rect.y = 0;
	rect.w = THREAT_WIDTH;
	rect.h = THREAT_HEIGHT;

	threat_lives = 3;

	x_vel = 0;
	y_vel = 0;
}


Threats::~Threats()
{
	if (Bullet_list.size() > 0)
	{
		for (int i = 0; i < Bullet_list.size(); i++)
		{
			Bullet* bullet = Bullet_list.at(i);
			if (bullet != NULL)
			{
				delete bullet;
				bullet = NULL;
			}
		}
		Bullet_list.clear();
	}
}
void Threats::Move(const int& x_border, const int& y_border)
{
	rect.x -= x_vel;
	if (rect.x < x_border/2)
	{
		rect.x = x_border/2;
		rect.y -= y_vel;
		if (rect.y < -THREAT_HEIGHT)
		{

			rect.x = x_border;
			rect.y = Random(y_border);
		}

	}
}

void Threats::InitBullet(Bullet* bullet, std::string path, SDL_Renderer* screen)
{
	if (bullet != NULL)
	{
		bool check = bullet->LoadImg(path, screen);
		if (check)
		{
			bullet->set_is_move(true);
			bullet->SetRect(rect.x, rect.y + rect.h);
			bullet->set_x_vel(10);
			bullet->set_y_vel(10);
			Bullet_list.push_back(bullet);
		}
	}
}

void Threats::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < Bullet_list.size(); i++)
	{
		Bullet* bullet = Bullet_list.at(i);
		if (bullet)
		{
			if (bullet->get_is_move())
			{
				bullet->show(screen);
				bullet->MoveRightToLeft();
			}
			else
			{
				bullet->set_is_move(true);
				bullet->SetRect(rect.x, rect.y + rect.h * 0.8);
			}
		}
	}
}

bool Threats::CheckCollisionToThreat(const SDL_Rect& threat, const SDL_Rect& bullet)
{
	//Calculate the sides of threat
	int left1 = threat.x;
	int right1 = threat.x + threat.w;
	int top1 = threat.y;
	int bottom1 = threat.y + threat.h;

	//Calculate the sides of bullet
	int left2 = bullet.x;
	int right2 = bullet.x + bullet.w;
	int top2 = bullet.y;
	int bottom2 = bullet.y + bullet.h;

	//If any of the sides from threat are outside of bullet

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

	//If none of the sides from threat are outside bullet
	return true;
}

void Threats::Reset(const int& x_border)
{
	rect.x = x_border;
	rect.y = Random(SCREEN_HEIGHT);

	for (int i = 0; i < Bullet_list.size(); i++)
	{
		Bullet* bullet = Bullet_list.at(i);
		if (bullet)
		{
			ResetBullet(bullet);
		}
	}
}

void Threats::ResetBullet(Bullet* bullet)
{
	bullet->SetRect(rect.x, rect.y + rect.h * 0.5);
}
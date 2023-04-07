
#include "Threats.h"

Threats::Threats()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = 0;
	rect_.w = THREAT_WIDTH;
	rect_.h = THREAT_HEIGHT;

	x_val = 0;
	y_val = 0;
}


Threats::~Threats()
{

}
void Threats::MoveLeft(const int& x_border, const int& y_border)
{
	rect_.x -= x_val;
	if (rect_.x < 0)
	{
		rect_.x = x_border;
		int rand_h = rand() % 400;
		if (rand_h > SCREEN_HEIGHT - 200)
		{
			rand_h = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_h;
	}
}

void Threats::MoveRight(const int& x_border, const int& y_border)
{
	rect_.x += x_val;
	if (rect_.x > x_border)
	{
		rect_.x = 0;
	}
}

void Threats::MoveUp(const int& x_border, const int& y_border)
{
	rect_.y -= y_val;
	if (rect_.y < 0)
	{
		rect_.y = y_border;
	}
}

void Threats::MoveDown(const int& x_border, const int& y_border)
{
	rect_.y += y_val;
	if (rect_.y > y_border)
	{
		rect_.y = 0;
	}
}

void Threats::MoveAround(const int& y_border)
{
	rect_.y -= y_val;
	if (rect_.y < 0)
	{
		rect_.y = 0;
		rect_.y += y_val;
		if (rect_.y > y_border)
		{
			rect_.y = y_border;
		}
	}
}

void Threats::InitBullet(Bullet* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		bool ret = p_bullet->LoadImg("image//Bullet.png", screen);
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->SetRect(rect_.x, rect_.y + rect_.h);
			p_bullet->set_x_val(15);
			Bullet_list.push_back(p_bullet);
		}
	}
}

void Threats::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < Bullet_list.size(); i++)
	{
		Bullet* p_bullet = Bullet_list.at(i);
		if (p_bullet)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->show(screen);
				p_bullet->HandleMoveRightToLeft();
			}
			else
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.8);
			}
		}
	}
}
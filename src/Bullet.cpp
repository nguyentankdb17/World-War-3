
#include "Bullet.h"

Bullet::Bullet()
{
    rect.x = 0;
    rect.y = 0;
    x_vel = 0;
    y_vel = 0;
    is_move = false;
}

Bullet::~Bullet()
{
    Free();
}

void Bullet::MoveLeftToRight(const int& x_border, const int& y_border)
{
    if (is_move == true)
    {
        rect.x += x_vel;
        if (rect.x > x_border)
        {
            is_move = false;
        }
    }
}

void Bullet::MoveRightToLeft()
{
    rect.x -= x_vel;
    if (rect.x < 0)
    {
        is_move = false;
    }
}

void Bullet::MoveCross()
{
    rect.x -= 2 * x_vel;
    rect.y -= y_vel;
    if (rect.x < 0 || rect.y < 0)
    {
        is_move = false;
    }
}


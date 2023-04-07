
#include "Bullet.h"

Bullet::Bullet()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val = 0;
    y_val = 0;
    is_move = false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMoveLeftToRight(const int& x_border, const int& y_border)
{
    if (is_move == true)
    {
        rect_.x += x_val;
        if (rect_.x > x_border)
        {
            is_move = false;
        }
    }
}

void Bullet::HandleMoveRightToLeft()
{
    rect_.x -= x_val;
    if (rect_.x < 0)
    {
        is_move = false;
    }
}

void Bullet::HandleInputAction(SDL_Event events)
{
    ;//Todo
}

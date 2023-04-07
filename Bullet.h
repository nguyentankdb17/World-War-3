
#ifndef BULLET_H
#define BULLET_H

#include "BaseObject.h"
#include "CommonFunc.h"

class Bullet : public BaseObject
{
public:
    const int BULLET_HEIGHT = 10;
    const int BULLET_WIDTH = 30;

    Bullet();
    ~Bullet();
    void HandleInputAction(SDL_Event events);
    void HandleMoveLeftToRight(const int& x_border, const int& y_border);
    void HandleMoveRightToLeft();

    bool get_is_move() const { return is_move; }
    void set_is_move(bool is_move_) { is_move = is_move_; }
    void SetWidthHeight(const int& widht, const int& height) { rect_.w = widht; rect_.h = height; };

    void set_x_val(const int& val) { x_val = val; }
    void set_y_val(const int& val) { y_val = val; }

    int get_x_val() const { return x_val; }
    int get_y_val() const { return y_val; }

private:
    int x_val;
    int y_val;

    bool is_move;
};


#endif
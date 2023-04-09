
#ifndef BULLET_H
#define BULLET_H

#include "BasicObject.h"
#include "General.h"

class Bullet : public BasicObject
{
public:

    enum BulletType
    {
        MAINOBJECT = 1,
        HELICOPTER = 2,
        PLANE = 3,
        TANK = 4
    };

    const int BULLET_HEIGHT = 10;
    const int BULLET_WIDTH = 30;

    const int BULLET_THREAT_HEIGHT = 10;
    const int BULLET_THREAT_WIDTH = 10;

    //Destructor & Constructor
    Bullet();
    ~Bullet();

    //Move the bullet
    void MoveLeftToRight(const int& x_border, const int& y_border);
    void MoveRightToLeft();
    void MoveCross();

    //Get and set the status
    bool get_is_move() const { return is_move; }
    void set_is_move(bool is_move_) { is_move = is_move_; }

    void SetWidthHeight(const int& widht, const int& height) { rect.w = widht; rect.h = height; };

    //Set velocity
    void set_x_vel(const int& vel) { x_vel = vel; }
    void set_y_vel(const int& vel) { y_vel = vel; }

    //Get velocity
    int get_x_vel() const { return x_vel; }
    int get_y_vel() const { return y_vel; }

private:
    //Velocity
    int x_vel;
    int y_vel;

    //Check the bullet move or not
    bool is_move;
};


#endif
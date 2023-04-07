
#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_vel = 0;
	y_vel = 0;
    frame = 0;
}

void MainObject::handleEvent(SDL_Event& e, SDL_Renderer* screen)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: y_vel -= TANK_VEL; break;
        case SDLK_DOWN: y_vel += TANK_VEL; break;
        case SDLK_LEFT: x_vel -= TANK_VEL; break;
        case SDLK_RIGHT: x_vel += TANK_VEL; break;
        case SDLK_SPACE:
            Bullet* p_bullet = new Bullet();
            p_bullet->LoadImg("image//Bullet.png", screen);
            p_bullet->SetRect(this->rect_.x + this->rect_.w*0.87, this->rect_.y + this->rect_.h * 0.33);
            p_bullet->set_is_move(true);
            p_bullet->set_x_val(20);
            Bullet_list.push_back(p_bullet);
            break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: y_vel += TANK_VEL; break;
        case SDLK_DOWN: y_vel -= TANK_VEL; break;
        case SDLK_LEFT: x_vel += TANK_VEL; break;
        case SDLK_RIGHT: x_vel -= TANK_VEL; break;
        }
    }

    else
    {
        //
    }
}


void MainObject::move()
{
    //Move the dot left or right
    rect_.x += x_vel;

    //If the dot went too far to the left or right
    if ((rect_.x < 0) || (rect_.x + TANK_WIDTH > SCREEN_WIDTH))
    {
        //Move back
        rect_.x -= x_vel;
    }

    //Move the dot up or down
    rect_.y += y_vel;

    //If the dot went too far up or down
    if ((rect_.y < 0) || (rect_.y + TANK_HEIGHT > SCREEN_HEIGHT))
    {
        //Move back
        rect_.y -= y_vel;
    }
}


bool MainObject::setClips(std::string path,SDL_Renderer* screen)
{
    if(!LoadImg(path, screen))
    {
        return false;
    }
    else
    {
            frame_clip[0].x = 0;
            frame_clip[0].y = 0;
            frame_clip[0].w = 250;
            frame_clip[0].h = 100;

            frame_clip[1].x = 250;
            frame_clip[1].y = 0;
            frame_clip[1].w = 250;
            frame_clip[1].h = 100;

            frame_clip[2].x = 500;
            frame_clip[2].y = 0;
            frame_clip[2].w = 250;
            frame_clip[2].h = 100;

            frame_clip[3].x = 750;
            frame_clip[3].y = 0;
            frame_clip[3].w = 250;
            frame_clip[3].h = 100;
    }
    return true;
}

void MainObject::MakeBullet(SDL_Renderer* screen)
{
    for (int i = 0; i < Bullet_list.size(); i++)
    {
        Bullet* p_bullet = Bullet_list.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->HandleMoveLeftToRight(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->show(screen);
            }
            else
            {
                if (p_bullet != NULL)
                {
                    Bullet_list.erase(Bullet_list.begin() + i);
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& index)
{
    for (int i = 0; i < Bullet_list.size(); i++)
    {
        if (index < Bullet_list.size())
        {
            Bullet* p_bullet = Bullet_list.at(index);
            Bullet_list.erase(Bullet_list.begin() + index);

            if (p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
    }
}

void MainObject::showClips(std::string path, SDL_Renderer* screen)
{
    if (setClips(path, screen))
    {
        while (frame >= 0) {
            SDL_Rect* currentClip = &frame_clip[frame/4];
            SDL_Rect renderQuad = { rect_.x, rect_.y, 250, 100 };
            if (currentClip != NULL)
            {
                renderQuad.w = currentClip->w;
                renderQuad.h = currentClip->h;
            }

            BaseObject::render(screen, rect_.x, rect_.y, currentClip);

            ++frame;
            SDL_Delay(5);
            if (frame/4 >= 4)
            {
                frame = 0;
            }
        }
    }

}




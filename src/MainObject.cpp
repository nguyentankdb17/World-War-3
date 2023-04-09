
#include "MainObject.h"

MainObject::MainObject()
{
	rect.x = 0;
	rect.y = 0;
	x_vel = 0;
	y_vel = 0;
    frame = 0;
    frame_width = 0;
    frame_height = 0;
}

void MainObject::handleEvent(SDL_Event& e, SDL_Renderer* screen)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: y_vel -= TANK_VEL; break;
        case SDLK_DOWN: y_vel += TANK_VEL; break;
        case SDLK_LEFT: x_vel -= TANK_VEL; break;
        case SDLK_RIGHT: x_vel += TANK_VEL; break;
        case SDLK_SPACE:
            Bullet* bullet = new Bullet();
            bullet->LoadImg("image//mainobject_bullet.png", screen);
            bullet->SetRect(this->rect.x + this->rect.w*0.23, this->rect.y + this->rect.h * 0.33);
            bullet->set_is_move(true);
            bullet->set_x_vel(10);
            Bullet_list.push_back(bullet);
            break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
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
    //Move the tank left or right
    rect.x += x_vel;
    if ((rect.x < 0) || (rect.x + TANK_WIDTH > SCREEN_WIDTH))
    {
        rect.x -= x_vel;
    }

    //Move the tank up or down
    rect.y += y_vel;
    if ((rect.y < 0) || (rect.y + TANK_HEIGHT > SCREEN_HEIGHT - 45))
    {
        rect.y -= y_vel;
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
        //Set size
        frame_width = rect.w / 4;
        frame_height = rect.h;

        //Set clips
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = frame_width;
        frame_clip[0].h = frame_height;

        frame_clip[1].x = frame_width;
        frame_clip[1].y = 0;
        frame_clip[1].w = frame_width;
        frame_clip[1].h = frame_height;

        frame_clip[2].x = frame_width*2;
        frame_clip[2].y = 0;
        frame_clip[2].w = frame_width;
        frame_clip[2].h = frame_height;

        frame_clip[3].x = frame_width*3;
        frame_clip[3].y = 0;
        frame_clip[3].w = frame_width;
        frame_clip[3].h = frame_height;
    }
    return true;
}

void MainObject::MakeBullet(SDL_Renderer* screen)
{
    for (int i = 0; i < Bullet_list.size(); i++)
    {
        Bullet* bullet = Bullet_list.at(i);
        if (bullet != NULL)
        {
            if (bullet->get_is_move())
            {
                bullet->MoveLeftToRight(SCREEN_WIDTH,SCREEN_HEIGHT);
                bullet->show(screen);
            }
            else
            {
                if (bullet != NULL)
                {
                    Bullet_list.erase(Bullet_list.begin() + i);
                    delete bullet;
                    bullet = NULL;
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
            Bullet* bullet = Bullet_list.at(index);
            Bullet_list.erase(Bullet_list.begin() + index);

            if (bullet != NULL)
            {
                delete bullet;
                bullet = NULL;
            }
        }
    }
}

void MainObject::showClips(std::string path, SDL_Renderer* screen)
{
    if (setClips(path, screen))
    {
        if (frame >= 4)
        {
            frame = 0;
        }
        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = { rect.x, rect.y, 250, 100 };
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        render(screen, rect.x, rect.y, currentClip);

        ++frame;
        SDL_Delay(5);

    }
}

bool MainObject::CheckCollisionToMainObject(const SDL_Rect& main_object, const SDL_Rect& threat)
{
    //Calculate the sides of main_object
    int left1 = main_object.x + 10;
    int right1 = main_object.x + main_object.w*0.2;
    int top1 = main_object.y + 10 ;
    int bottom1 = main_object.y + main_object.h*0.9;

    //Calculate the sides of threat
    int left2 = threat.x;
    int right2 = threat.x + threat.w;
    int top2 = threat.y;
    int bottom2 = threat.y + threat.h;

    //If any of the sides from main_object are outside of threat

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

    //If none of the sides from main_object are outside threat
    return true;
}




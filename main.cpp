
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Bullet.h"
#include "Threats.h"

BaseObject g_background;
MainObject g_tank;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create window
    g_window = SDL_CreateWindow("World War 3",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
}

 void close()
 {
        g_tank.Free();
        g_background.Free();

        SDL_DestroyRenderer(g_screen);
        g_screen = NULL;

        SDL_DestroyWindow(g_window);
        g_window = NULL;

        IMG_Quit();
        SDL_Quit();
 }

bool LoadMedia()
{
    bool success = true;

    if (!g_tank.LoadImg("image//tank.png", g_screen))
    {
        printf("Failed to load tank texture!\n");
        success = false;
    }

    if (!g_background.LoadImg("image//background.png",g_screen))
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    return success;
}



int main (int argc, char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }
    if (!LoadMedia())
    {
        return -1;
    }

    int scrollingOffset = 0;

    int frame = 0;
    bool quit = false;
    Threats* p_threats = new Threats[THREATS_NUM];
    for (int i = 0; i < THREATS_NUM; i++)
    {
        Threats* p_threat = (p_threats + i);
        if (p_threat)
        {
            p_threat->LoadImg("image//threat.png", g_screen);
            int rand_h = rand() % 600;
            if (rand_h > SCREEN_HEIGHT)
            {
                rand_h = SCREEN_HEIGHT * 0.3;
            }
            p_threat->SetRect(SCREEN_WIDTH + i * 400, rand_h);
            p_threat->set_x_val(2);
            p_threat->set_y_val(2);

            Bullet* p_bullet = new Bullet();
            p_threat->InitBullet(p_bullet, g_screen);
        }
    }
    while (!quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                quit = true;
            }

            g_tank.handleEvent(g_event, g_screen);
        }



        //Scroll background
        --scrollingOffset;
        if (scrollingOffset < -g_background.getWidth())
        {
            scrollingOffset = 0;
        }

        SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_screen);

        //Render backgroun
        SDL_Delay(20);
        g_background.render(g_screen, scrollingOffset, 0, NULL);
        g_background.render(g_screen, scrollingOffset + g_background.getWidth(), 0, NULL);

        g_tank.show(g_screen);
        //g_tank.showClips("image//tank_sprite", g_screen);

        //Move the tank
        g_tank.move();

        

        for (int i = 0; i < THREATS_NUM; i++)
        {
            Threats* p_threat = (p_threats + i);
            p_threat->show(g_screen);
            p_threat->MoveLeft(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        g_tank.MakeBullet(g_screen);

        //Update screen
        SDL_RenderPresent(g_screen);
    }

    close();
    return 0;
}




#include "General.h"
#include "BasicObject.h"
#include "MainObject.h"
#include "Bullet.h"
#include "Threats.h"
#include <SDL_ttf.h>


//Initialize the Object
BasicObject g_background;
BasicObject g_text ;
MainObject g_flytank;


bool Init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //Create window
    g_window = SDL_CreateWindow("World War 3",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create Renderer
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            //Set background color
            SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }
    return true;
}

 void close()
 {
     //Destroy object
     g_flytank.Free();
     g_background.Free();

     //Destroy Renderer
     SDL_DestroyRenderer(g_screen);
     g_screen = NULL;

     //Destroy Window
     SDL_DestroyWindow(g_window);
     g_window = NULL;

     //Quit
     IMG_Quit();
     SDL_Quit();
 }

bool LoadMedia()
{
    bool success = true;

    gFont = TTF_OpenFont("font//UTMFacebook.ttf", 28);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
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
    if (TTF_Init() == -1)
    {
        return -1;
    }
    if (Init() == false)
    {
        return -1;
    }
    if (!LoadMedia())
    {
        return -1;
    }

    int scrollingOffset = 0;

    bool quit = false;

    int game_point = 0;

    int lives_left = 5;

    //Init the Threats and Bullets
    Threats* threats = new Threats[THREATS_NUM];
    for (int i = 0; i < THREATS_NUM; i++)
    {
        Threats* threat = (threats + i);

        threat->LoadImg("image//helicopter_threat.png", g_screen);
        //Random the start position for the threats
        int random = rand() % SCREEN_HEIGHT;
        if (random > SCREEN_HEIGHT - 250)
        {
            random = SCREEN_HEIGHT * 0.5;
        }
        threat->SetRect(SCREEN_WIDTH + i*400, random);
        threat->set_x_vel(2);
        threat->set_y_vel(2);

        //Init the Bullet
        Bullet* bullet = new Bullet();
        threat->InitBullet(bullet, "image//threat_bullet.png", g_screen);
    }
    
 

    while (!quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                quit = true;
            }
            //Handle Press
            g_flytank.handleEvent(g_event, g_screen);
        }

        //Scroll background
        --scrollingOffset;
        if (scrollingOffset < -g_background.getWidth())
        {
            scrollingOffset = 0;
        }

        //Set the background color
        SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
        //Refresh the screen
        SDL_RenderClear(g_screen);

        //Render background
        SDL_Delay(20);
        g_background.render(g_screen, scrollingOffset, 0, NULL);
        g_background.render(g_screen, scrollingOffset + g_background.getWidth(), 0, NULL);

        //Show the flytank
        g_flytank.showClips("image//tank_sprite.png", g_screen);

        //Move the flytank
        g_flytank.move();

        //Make bullet for the flytank
        g_flytank.MakeBullet(g_screen);

        //Show the threat and make bullet
        for (int i = 0; i < THREATS_NUM; i++)
        {
            Threats* threat = (threats + i);

            threat->show(g_screen);
            threat->Move(SCREEN_WIDTH, SCREEN_HEIGHT);
            if (threat->GetRect().x <= SCREEN_WIDTH)
            {
                threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            }


            //Collision threat's bullet to main object
            bool checkmain_object = false;
            std::vector<Bullet*> bullet_threat = threat->GetBulletList();
            for (int i = 0; i < bullet_threat.size(); i++)
            {
                Bullet* bullet = bullet_threat.at(i);
                if (bullet)
                {
                    checkmain_object = g_flytank.CheckCollisionToMainObject(g_flytank.GetRect(),bullet->GetRect());
                    if (checkmain_object == true)
                    {
                        threat->ResetBullet(bullet);
                        break;
                    }
                }
            }

            //Collision threats to main object
            bool checkthreat_main_object = false;
            checkthreat_main_object = g_flytank.CheckCollisionToMainObject(g_flytank.GetRect(), threat->GetRect());
            if (checkthreat_main_object == true)
            {
                threat->Reset(SCREEN_WIDTH);
                break;
            }

            //Collision main object's bullet to threats
            bool checkthreat = false;
            std::vector<Bullet*> bullet_mainobj = g_flytank.GetBulletList();
            for (int i = 0; i < bullet_mainobj.size(); i++)
            {
                Bullet* bullet = bullet_mainobj.at(i);
                if (bullet)
                {
                    checkthreat = threat->CheckCollisionToThreat(threat->GetRect(), bullet->GetRect());
                    if (checkthreat == true)
                    {
                        g_flytank.RemoveBullet(i);
                        break;
                    }
                }
            }

            if (checkthreat || checkthreat_main_object)
            {
                threat->threat_lives--;
                if (threat->threat_lives == 0)
                {
                    game_point++;
                    threat->Reset(SCREEN_WIDTH);
                    break;
                }
            }

            if (checkmain_object || checkthreat_main_object)
            {
                lives_left--;
                if (lives_left > 0)
                {
                    SDL_Delay(1000);
                    g_flytank.SetRect(0, SCREEN_HEIGHT - 150);
                    break;
                }
                else
                {
                    if (MessageBox(NULL, L"YOU DIED ! LET'S TRY AGAIN", L"GAME OVER !", MB_OK | MB_ICONSTOP) == IDOK)
                    {
                        quit = true;
                        break;
                    }
                }
            }
        }

        //Init text color
        SDL_Color blackColor = { 0, 0, 0 };
        SDL_Color greenColor = { 0, 255, 0, };
        SDL_Color redColor = { 255 , 0 , 0, };

        //Init time
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;

        if (val_time <= 0)
        {
            if (MessageBox(NULL, L"END OF TIME", L"GAME OVER !", MB_OK | MB_ICONSTOP) == IDOK)
            {
                quit = true;
                break;
            }
        }
        else
        {
            //Show time
            std::string str_time = "Time: " + std::to_string(val_time);
            g_text.loadFromText(gFont, str_time, greenColor, g_screen);
            g_text.render(g_screen, 50, 550, NULL);
        }

        std::string pts = "Total Points : " + std::to_string(game_point);
        g_text.loadFromText(gFont, pts, blackColor, g_screen);
        g_text.render(g_screen, 400, 550, NULL);

        std::string lives = "Lives Left : " + std::to_string(lives_left);
        g_text.loadFromText(gFont, lives, redColor, g_screen);
        g_text.render(g_screen, 800, 550, NULL);

        //Update screen
        SDL_RenderPresent(g_screen);
    }

    delete[] threats;
    close();
    return 0;
}



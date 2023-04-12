
#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static TTF_Font* gFont = NULL;

//Screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int THREATS_NUM = 5;


#endif
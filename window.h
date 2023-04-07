#include "include.h"

#ifndef WINDOW_H
#define WINDOW_H

//Screen
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_WIDTH = 1000;
static const int SCREEN_BPP = 32;

// Color Module
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

//Window
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


#endif
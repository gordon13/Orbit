#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL2/SDL.h"
#include "../lib/rapidjson/document.h"
#include <vector>

using namespace rapidjson;

//Levels data
extern Document levelsDocument;
extern std::string background;
//extern std::vector <int, int> player_start;

//user data
extern Document userDocument;
extern int score;
extern int current_level;


//The surfaces
extern SDL_Surface *sPlayer;
extern SDL_Window *gWindow;
extern SDL_Surface *screen;

//The event structure
extern SDL_Event event;

//The dimensions of the level
extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

#endif
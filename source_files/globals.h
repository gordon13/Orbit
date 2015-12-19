#ifndef GLOBALS_H
#define GLOBALS_H
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

//The header
#include "SDL2/SDL.h"

//Levels document
extern Document levelsDocument;

//The surfaces
extern SDL_Surface *dot;
extern SDL_Window *gWindow;
extern SDL_Surface *screen;

//The event structure
extern SDL_Event event;

#endif
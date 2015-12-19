//The headers
#include "SDL2/SDL.h"
#include "globals.h"
#include "../lib/rapidjson/document.h"

//Levels document
Document levelsDocument;

//The surfaces
SDL_Surface *dot = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;
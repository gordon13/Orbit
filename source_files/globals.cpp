//The headers
#include "SDL2/SDL.h"
#include "globals.h"
#include "../lib/rapidjson/document.h"
#include <vector>

using namespace rapidjson;

//Levels data
Document levelsDocument;
std::string background;
//std::vector <int, int> player_start;

//Levels document
Document userDocument;
int score;
int current_level;

//The surfaces
SDL_Surface *sPlayer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

int LEVEL_WIDTH;
int LEVEL_HEIGHT;
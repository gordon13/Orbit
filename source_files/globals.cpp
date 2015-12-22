//The headers
#include "SDL2/SDL.h"
#include "globals.h"
#include "../lib/rapidjson/document.h"
#include <vector>

using namespace rapidjson;
using namespace std;

//Levels data
Document levelsDocument;
string background;
vector<int> player_start;

vector<> level_array;

//Levels document
Document userDocument;
int score;
int current_level;

//The surfaces
SDL_Surface *sSpace = NULL;
SDL_Surface *sPlayer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

int LEVEL_WIDTH = 2048;
int LEVEL_HEIGHT = 2048;
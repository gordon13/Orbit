//The headers
#include "SDL2\SDL.h"
#include "globals.h"

//levels data
char* levelsJSON = std::ifstream ifile("source_files/levels.json");
Document d;
d.Parse(levelsJSON);

LevelsStruct

printf(LevelsStruct)

//The surfaces
SDL_Surface *dot = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;
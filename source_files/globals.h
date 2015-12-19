#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL2\SDL.h"

#include <vector>

//Levels data
struct Background
{
	std::string image;
};

struct Playerstart
{
	int x;
	int y;
};

struct Object
{
	std::string type;
	int x;
	int y;
	int scale;
	int gravity;
	std::string image;
};

struct LevelsStruct 
{
	std::vector<Background> background;
	std::vector<Playerstart> playerstart;
	std::vector<Object> objects;
};

//The surfaces
extern SDL_Surface *dot;
extern SDL_Surface *screen;

//The event structure
extern SDL_Event event;

#endif
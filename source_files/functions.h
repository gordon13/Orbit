#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//The headers
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

//File Loader
SDL_Surface *load_image( std::string filename );

//Surface blitter
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

//get levels json
bool get_levels();

//get user data json
bool get_user_data();

//Initialization
bool init();

//File loading
bool load_files();

//Clean up
void clean_up();

#endif
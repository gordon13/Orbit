#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "constants.h"
#include "functions.h"
#include "globals.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/rapidjson.h"
#include "../lib/rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;

SDL_Surface *load_image( std::string filename ) 
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", filename.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool get_levels()
{
    printf( "Attempting to read file...\n");
    FILE* fp = fopen("source_files/Levels/levels.txt", "rb"); // non-Windows use "r"
    if (!fp) {
        printf( "File doesn't exist\n");
        return false;
    }
    printf( "1\n");
    char readBuffer[65536];
    printf( "2\n");

    //FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    StringStream is(fp);
    printf( "3\n");
    levelsDocument.ParseStream(is);
    printf( "4\n");
    fclose(fp);
    //string s((istreambuf_iterator<char>(levelFile)), istreambuf_iterator<char>());
    //ifstream levelFile;
    //levelFile.open("D:/Programming/Orbit/source_files/Levels/levels.json", ios_base::in); 
    //levelFile.open("D:/Programming/Orbit/source_files/Levels/levels.json", ios_base::in); 
    // if (!levelFile)
    // {
    //     printf( "Could not load levels file");
    //     return false;
    // }

    if (!levelsDocument.IsObject())
    {
        printf( "Could not load levels file");
        return false;
    }

    // assert(levelsDocument.HasMember("background"));
    // assert(levelsDocument["background"].IsString());
    // printf("background = %s\n", levelsDocument["background"].GetString());
    printf( "5\n");
    //printf(content.c_str());

    // FILE* fp = NULL;
    // if ( (fp = fopen("D:/Programming/Orbit/source_files/levels.json", "rb")) == NULL)
    // {
    //     printf( "Could not load levels file");
    //     return false;
    // }
    // char readBuffer[65536];
    // FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    // levelsDocument->ParseStream(is);
    // fclose(fp);
    printf("Levels loaded\n");
    return true;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }

    //Create window
    gWindow = SDL_CreateWindow( "Orbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    else
    {
        //Get window surface
        screen = SDL_GetWindowSurface( gWindow );
    }

    //If there was in error in setting up the screen
    if( screen == NULL )
    {
        return false;    
    }
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the dot image
    dot = load_image( "resources/doge.bmp" );
    
    //If there was a problem in loading the dot
    if( dot == NULL )
    {
        return false;    
    }
    
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( dot );
    SDL_FreeSurface( screen );
    
    //Quit SDL
    SDL_Quit();
}

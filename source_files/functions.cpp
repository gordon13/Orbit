#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
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


bool get_user_data()
{
    FILE* fp = fopen("user_files/user.txt", "rb"); // non-Windows use "r"
    if (!fp) {
        printf( "File doesn't exist\n");
        return false;
    }
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    userDocument.ParseStream(is);
    fclose(fp);

    if (!userDocument.IsObject())
    {
        printf( "Could not load user data\n");
        return false;
    }
    /*static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
    for (Value::ConstMemberIterator itr = userDocument.MemberBegin(); itr != userDocument.MemberEnd(); ++itr)
    {
        printf("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
    }*/

    Value::ConstMemberIterator itr_level = userDocument.FindMember("current_level");
    Value::ConstMemberIterator itr_score = userDocument.FindMember("score");
    if (itr_level == userDocument.MemberEnd() || itr_score == userDocument.MemberEnd())
    {
        printf("'current_level' and 'score' not found\n");
        return false;
    }
    std::ostringstream oss;
    current_level = itr_level->value.GetInt();
    score = itr_score->value.GetInt();
    printf("User data loaded\n");
    printf("level: %d, score:%d \n", current_level, score);
    return true;
}


bool get_levels()
{
    FILE* fp = fopen("source_files/Levels/levels.txt", "rb"); // non-Windows use "r"
    if (!fp) {
        printf( "File doesn't exist\n");
        return false;
    }
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    levelsDocument.ParseStream(is);
    fclose(fp);

    if (!levelsDocument.IsObject())
    {
        printf("Could not load levels file\n");
        return false;
    }

    //find current level data
    ostringstream convert;
    convert << current_level;
    string temp_str = convert.str();
    const char* str_c_level = temp_str.c_str();

    //convert.str()
    printf("Get background and player_start for level %s \n", str_c_level);
    //get current level object
    Value::ConstMemberIterator itr_level = levelsDocument.FindMember(str_c_level);

    //get background image location
    const Value& level_obj = levelsDocument[str_c_level];
    background = level_obj["background"]["image"].GetString();

    //get player start location
    int xy[] = {level_obj["player_start"]["x"].GetInt(), level_obj["player_start"]["y"].GetInt()};
    player_start.assign(xy, xy+2);

    if (background.empty() || player_start.size() != 2)
    {
        printf("'background' and 'player start' not found\n");
        return false;
    }
    printf("Levels loaded\n");
    printf("Background: %s, Start pos:%d %d \n", background.c_str(), player_start[0], player_start[1]);
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
    sPlayer = load_image( "resources/doge.bmp" );
    
    //If there was a problem in loading the sPlayer
    if( sPlayer == NULL )
    {
        return false;    
    }
    
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( sPlayer );
    SDL_FreeSurface( screen );
    
    //Quit SDL
    SDL_Quit();
}

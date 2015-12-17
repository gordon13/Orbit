/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2\SDL.h>
#include <stdio.h>
#include <string>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gSpace = NULL;

SDL_Surface* loadSurface( std::string path );

//Starts up SDL and creates window
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "Orbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

//Loads media
bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gSpace = SDL_LoadBMP( "resources/space.bmp" );
    if( gSpace == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "resources/space.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL
void close()
{
    //Deallocate surface
    SDL_FreeSurface( gSpace );
    gSpace = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( gSpace, NULL, gScreenSurface, NULL );

            //Update the surface
            SDL_UpdateWindowSurface( gWindow );

            //Wait two seconds
            SDL_Delay( 2000 );
        }


        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        //CORE GAME LOOP
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                else if ( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP:
                        printf("Up!");
                        break;

                        case SDLK_DOWN:
                        printf("Down!");
                        break;

                        case SDLK_LEFT:
                        printf("Left!");
                        break;

                        case SDLK_RIGHT:
                        printf("Right!");
                        break;
                    }
                }
            }
            //Apply the image
            SDL_BlitSurface( gSpace, NULL, gScreenSurface, NULL );
        
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

int main( int argc, char* args[] )
{
    //get user data
    if( get_user_data() == false )
    {
        return false;
    }

    //get levels
    if( get_levels() == false )
    {
        return false;
    }

    //Quit flag
    bool quit = false;

    //The frame rate regulator
    Timer fps;

    //The dot that will be used
    Dot player;

    //The earth
    Entity earth;

    //The camera area
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Initialize
    if( init() == false )
    {
        return 1;
    }
    
    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
    
    
    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();
        
        //==============//
        //Handle input
        //==============//
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            player.handle_input();
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                printf("quit!\n");
                //Quit the program
                quit = true;
                break;
            }
        }


        //==============//
        //Update position
        //==============//
        //Move the dot
        player.move();
        
        //camera stuff
        camera.x = ( player.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
        camera.y = ( player.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

        //Keep the camera in bounds
        if( camera.x < 0 )
        { 
            camera.x = 0;
        }
        if( camera.y < 0 )
        {
            camera.y = 0;
        }
        if( camera.x > LEVEL_WIDTH - camera.w )
        {
            camera.x = LEVEL_WIDTH - camera.w;
        }
        if( camera.y > LEVEL_HEIGHT - camera.h )
        {
            camera.y = LEVEL_HEIGHT - camera.h;
        }

        //==============//
        //Draw
        // -background first
        // -objects/characters
        // -update screen (so things move)
        // -cap framerate (for reasons?)
        //==============//
        
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        apply_surface( 0, 0, sSpace, screen );
        //draw earth
        //earth.draw(camera.x, camera.y);
        //Show the dot on the screen
        player.show(camera.x, camera.y);
        
        //Update the screen
        if( SDL_UpdateWindowSurface( gWindow ) == -1 )
        {
            return 1;    
        }
        
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }
        
    //Clean up
    clean_up();
    
    return 0;    
}
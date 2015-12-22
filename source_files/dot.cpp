//The headers
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Dot::Dot()
{
    //Initialize the offsets
    x = player_start[0];
    y = player_start[1];
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Dot::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += DOT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += DOT_WIDTH / 2; break;    
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += DOT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel -= DOT_WIDTH / 2; break;    
        }        
    }
}

void Dot::move()
{
    //Move the dot left or right
    x += xVel;
    
    // //If the dot went too far to the left or right
    // if( ( x < 0 ) || ( x + DOT_WIDTH > SCREEN_WIDTH ) )
    // {
    //     //move back
    //     x -= xVel;    
    // }
    
    //Move the dot up or down
    y += yVel;
    
    // //If the dot went too far up or down
    // if( ( y < 0 ) || ( y + DOT_HEIGHT > SCREEN_HEIGHT ) )
    // {
    //     //move back
    //     y -= yVel;    
    // }
}

void Dot::show(int camX, int camY)
{
    //Show the dot
    apply_surface( x - camX, y - camY, sPlayer, screen );
}

int Dot::getPosX()
{
    return x;
}

int Dot::getPosY()
{
    return y;
}
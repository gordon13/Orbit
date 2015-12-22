//The headers
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <stdio.h>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

using namespace std;

Entity::Entity()
{
    //Initialize the offsets
    x = 0;
    y = 0;
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Entity::update()
{
    //Move the Entity left or right
    x += xVel;

    //Move the Entity up or down
    y += yVel;
}

void Entity::draw(SDL_Surface* entitySurface, int camX, int camY)
{
    //Show the Entity
    apply_surface( x - camX, y - camY, entitySurface, screen );
}

int Entity::getPosX()
{
    return x;
}

int Entity::getPosY()
{
    return y;
}

void Entity::setPosX(int xin)
{
    x = xin;
}

void Entity::setPosY(int yin)
{
    y = yin;
}

void Entity::clean_up()
{
}
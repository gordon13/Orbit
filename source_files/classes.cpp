//The headers
#include "SDL2\SDL.h"
#include <string>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Dot::Dot()
{
    //Initialize the offsets
    x = 0;
    y = 0;
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}
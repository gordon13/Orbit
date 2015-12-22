#ifndef CLASSES_H
#define CLASSES_H
#include <string>
using namespace std;

class Entity
{
    private:
    //The X and Y offsets of the dot
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;

    public:
    float getScale();

    void setScale();

    int getPosX();

    int getPosY();

    void setPosX(int xin);

    void setPosY(int yin);

    //Initializes the variables
    Entity();
    
    //Moves the dot
    void update();

    //Shows the dot on the screen
    void draw(SDL_Surface* entitySurface, int camX, int camY);

    void clean_up();
};

class EntityPhysable : Entity
{    
    public:
    //Initializes the variables
    EntityPhysable();

    void add_impulse();
};

class Dot
{
    private:
    //The X and Y offsets of the dot
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;
    
    public:
    int getPosX();
    int getPosY();
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
    
    //Initializes the variables
    Dot();
    
    //Takes key presses and adjusts the dot's velocity
    void handle_input();
    
    //Moves the dot
    void move();
    
    //Shows the dot on the screen
    void show(int camX, int camY);
};

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
    public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();    
};

#endif
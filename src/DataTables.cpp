#include "DataTables.h"
#include "Ship.h"
#include "Planet.h"

std::vector<ShipData> initializeShipData()
{
    std::vector<ShipData> data(Ship::TypeCount);
    data[Ship::Basic].hitpoints = 100;
    data[Ship::Basic].mass = 20;
    data[Ship::Basic].speed = 20.f;
    data[Ship::Basic].texture = Textures::Basic;
    data[Ship::Super].hitpoints = 160;
    data[Ship::Super].mass = 20;
    data[Ship::Super].speed = 350.f;
    data[Ship::Super].texture = Textures::Super;
    return data;
}

std::vector<PlanetData> initializePlanetData()
{
    std::vector<PlanetData> data(Planet::TypeCount);
    data[Planet::Moon].hitpoints = 100;
    data[Planet::Moon].mass = 300;
    data[Planet::Moon].speed = 0;
    data[Planet::Moon].texture = Textures::Moon;
    data[Planet::Earth].hitpoints = 160;
    data[Planet::Earth].mass = 500;
    data[Planet::Earth].speed = 0;
    data[Planet::Earth].texture = Textures::Earth;
    return data;
}

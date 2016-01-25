#ifndef DATATABLES_H
#define DATATABLES_H

#include "ResourceIdentifiers.h"

#include <vector>

class Ship;

struct ShipData
{
    int hitpoints;
    int mass;
    float speed;
    Textures::ID texture;
};

class Planet;

struct PlanetData
{
    int hitpoints;
    int mass;
    float speed;
    Textures::ID texture;
};


std::vector<ShipData>	initializeShipData();
std::vector<PlanetData>	initializePlanetData();

#endif // DATATABLES_H

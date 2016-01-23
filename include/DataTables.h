#ifndef DATATABLES_H
#define DATATABLES_H

#include <ResourceIdentifiers.h>

#include "ResourceIdentifiers.h"

#include <vector>

class Ship;

struct ShipData
{
    int hitpoints;
    float speed;
    Textures::ID texture;
};


std::vector<ShipData>	initializeShipData();

#endif // DATATABLES_H

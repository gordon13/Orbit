#include "DataTables.h"
#include "Ship.h"

std::vector<ShipData> initializeShipData()
{
    std::vector<ShipData> data(Ship::TypeCount);
    data[Ship::Basic].hitpoints = 100;
    data[Ship::Basic].speed = 200.f;
    data[Ship::Basic].texture = Textures::Basic;
    data[Ship::Super].hitpoints = 160;
    data[Ship::Super].speed = 350.f;
    data[Ship::Super].texture = Textures::Super;
    return data;
}

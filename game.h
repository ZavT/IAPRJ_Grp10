#pragma once
#include "map.h"
#include "sewer.h"
#include "player.h"
#include "enemy.h"
#include "inventory.h"
#include "bunker.h"
#include "town.h"

//names for locations to track the current map that is active
enum class Location {
    Sewer1,
    Sewer2,
    Sewer3,
    Town,
    Lab, 
    Bunker,
    MainWorld
};

class game
{
private:
    //map objects
    map worldMap;
    sewer Sewer1;
    sewer Sewer2;
    sewer Sewer3;
    bunker Bunker;
    town Town;

    player player; // player object
    inventory bag; //inventory/bag object z
    //enemy enemy; // testing

    Location currentMap = Location::MainWorld; //default is main world

    map& activeMap();
public:
    game();

    void createWorldMap();
    void Run();
    void checkMapChange();
    void discoverpoi();
};


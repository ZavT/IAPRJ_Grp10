#pragma once
#include "map.h"
#include "sewer.h"
#include "player.h"
#include "enemy.h"
#include "inventory.h"
#include "menu.h"
#include "bunker.h"
#include "town.h"
#include "lab.h"

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
    lab Lab;

    player player; // player object
    inventory bag; //inventory/bag object z
    menu settings;
    //enemy enemy; // testing

    Location currentMap = Location::MainWorld; //default is main world

    map& activeMap();
    enemy** activeEnemy(int& totalCount);
    void handleMovement(int dx, int dy);
public:
    game();

    void createWorldMap();
    void Intro();
    void Run();
    void checkMapChange();
    void discoverpoi();
    void battlesequence(enemy& currentEnemy);
};


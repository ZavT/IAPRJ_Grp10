#pragma once
#include "map.h"
#include "enemy.h"
class bunker :
    public map
{
public:
    bunker();
    ~bunker();
    bunker(const bunker&) = delete;
    bunker& operator=(const bunker&) = delete;

    map bunkerMap;
    enemy** bunkerEnemy;
    int BunkerEnemyCount;
    
    void printbunkerMap();
};


#pragma once
#include "map.h"
#include "enemy.h"

class game;

class sewer :
    public map
{
private:
    //bool sewerActive[3];
public:
    sewer();

    void printSewerMap(int sewernum);
    void testActiveEnemy(int sewernum);
    map sewerMap;
    enemy testEnemy[2];
};


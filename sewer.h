#pragma once
#include "map.h"
#include "enemy.h"

class game;

class sewer :
    public map
{
private:

public:
    sewer();
    ~sewer();
    sewer(const sewer&) = delete;
    sewer& operator=(const sewer&) = delete;

    void printSewerMap(int sewernum);

    map sewerMap;
    enemy** sewerEnemy;
    int enemyCount;
};


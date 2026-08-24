#pragma once
#include "map.h"
#include "enemy.h"

class lab :
    public map
{
public:
    lab();
    map labMap;
    enemy** labEnemy;
    void printlabMap();
};


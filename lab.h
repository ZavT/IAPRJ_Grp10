#pragma once
#include "map.h"
#include "enemy.h"

class lab :
    public map
{
public:
    lab();
    ~lab();
    lab(const lab&) = delete;
    lab& operator=(const lab&) = delete;

    map labMap;
    enemy** labEnemy;
    enemy** TheScientist;
    int labEnemyCount;

    void summonBoss();
    void printlabMap();
};


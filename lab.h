#pragma once
#include "map.h"
#include "enemy.h"
#include "boss.h"

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
    boss* TheScientist = nullptr;
    int labEnemyCount;
  

    void summonBoss();
    void printlabMap();
    void checkRoomClear();
};


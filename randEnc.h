#pragma once
#include "map.h"
#include "enemy.h"

class randEnc : public map
{
public:
	randEnc();
    ~randEnc();
    randEnc(const randEnc&) = delete;
    randEnc& operator=(const randEnc&) = delete;

    void printRandEncMap(int randencnum);

    map randEncMap;
    enemy** randEncEnemy;
    int enemyCount;
};


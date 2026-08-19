#pragma once
#include "entity.h"
#include "enemy.h"

class enemy;

class player :
    public entity
{
public:
    void move(int moveX, int moveY);
    void borderCol(int moveX, int moveY);
    void testAttack(enemy& targetenemy);
};


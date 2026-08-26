#pragma once
#include "enemy.h"
class boss :
    public enemy
{
public:
    boss(int posX, int posY, int id) : enemy(posX, posY, id, 150) {} //to just fix errors //change later

    char getSymbol() override { return 'B'; }
};


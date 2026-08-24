#pragma once
#include "enemy.h"
class boss :
    public enemy
{
    boss(int posX, int posY, int id) : enemy(posX, posY, id, 150) {} //to just fix errors //change later
};


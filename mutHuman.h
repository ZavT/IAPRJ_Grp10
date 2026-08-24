#pragma once
#include "enemy.h"
class mutHuman :
    public enemy
{
public:
    char getSymbol() override { return 'H'; }
};


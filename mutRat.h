#pragma once
#include "enemy.h"
class mutRat :
    public enemy
{
public:
    char getSymbol() override { return 'R'; }
};


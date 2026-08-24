#pragma once
#include "enemy.h"
class mutRat :
    public enemy
{
public:
    mutRat(int posX, int posY, int id);

    void displayStats() const override;
    char getSymbol() override { return 'R'; }
};


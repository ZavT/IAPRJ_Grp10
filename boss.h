#pragma once
#include "enemy.h"
class boss :
    public enemy
{
private: 
    bool bossActive = true;
public:
    boss(int posX, int posY, int id) : enemy(posX, posY, id, 200) { } //to just fix errors //change later
   ~boss();

    char getSymbol() override { return 'B'; }

    void setBossActive(bool state);
    bool getBossActive() const;
};


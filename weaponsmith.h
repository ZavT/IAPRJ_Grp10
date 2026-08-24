#pragma once
#include "player.h"
#include "inventory.h"

class weaponsmith
{
private:
    bool isOpen;

public:
    weaponsmith();
    void weaponsmithOpen(player& p, inventory& bag);
};


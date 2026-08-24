#pragma once
#include "npc.h"
#include "player.h"
#include "inventory.h"

class weaponsmith :
    public npc
{
private:
    bool isOpen;

public:
    weaponsmith();
    void weaponsmithOpen(player& p, inventory& bag);
};


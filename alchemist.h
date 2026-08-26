#pragma once
#include "player.h"
#include "inventory.h"

class alchemist
{
private:
    bool isOpen;

public:
    alchemist();
    void alchemistOpen(player& p, inventory& bag);
};


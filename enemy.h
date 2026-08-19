#pragma once
#include "entity.h"
#include "player.h"

class player;

class enemy :
    public entity
{
public:
    enemy();
    void checkForPlayer(player& player);
};


#pragma once
#include "entity.h"
#include "player.h"

class player;

class enemy :
    public entity
{
public:
    enemy(int posX, int posY, int id, int health, int attack, int weapon);
    virtual ~enemy();

    void checkForPlayer(player& player);
};


#pragma once
#include "entity.h"
#include "player.h"

class player;

class enemy :
    public entity
{
private:
    bool isTargeting;
public:
    enemy(int posX, int posY, int id, int health, int attack, int weapon);
    virtual ~enemy();

    void checkForPlayer(player& player);

    void enemyBehaviour(player& player);

    void enemyMove(int moveX, int moveY);
};


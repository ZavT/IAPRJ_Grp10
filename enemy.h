#pragma once
#include "entity.h"
#include "player.h"

class player;
class map;

class enemy :
    public entity
{
private:
    bool isTargeting;
public:
    enemy();
    void checkForPlayer(player& player);

    void enemyBehaviour(player& player, map& currentMap);

    void enemyMove(int moveX, int moveY);
    void enemyBorderCol(int moveX, int moveY, int maxBorderX, int maxBorderY);

    virtual char getSymbol() { return 'E';}
};


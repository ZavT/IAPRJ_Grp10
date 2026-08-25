#pragma once
#include "entity.h"

class player;
class map;

class enemy :
    public entity
{
private:
    bool isTargeting;
    bool spawned = false;
    bool justEscaped = false;
public:
    enemy(int posX, int posY, int id, int healthPoints);
    virtual ~enemy();

    void checkForPlayer(player& player);

    void enemyBehaviour(player& player, map& currentMap, enemy** allEnemies, int enemyCount, int currentIdx);

    void enemyMove(int moveX, int moveY);
    void enemyBorderCol(int moveX, int moveY, int maxBorderX, int maxBorderY);

    bool enemyCheckCol(int checkX, int checkY, player& player, enemy** allEnemies, int enemyCount, int currentIdx);

    virtual char getSymbol() { return 'E';}

    void setSpawnState(bool s);
    bool isSpawned();

    void setEscapeState(bool escaped);
    bool getEscapeState();
};


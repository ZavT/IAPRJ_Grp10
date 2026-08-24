#pragma once

class enemy;

class inspect
{
private:
    bool isOpen;

public:
    inspect();
    void inspectOpen(enemy** enemies, int enemyCount);
};
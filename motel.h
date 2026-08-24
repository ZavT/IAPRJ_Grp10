#pragma once
#include "entity.h"

class motel :
    public entity
{
public:
    motel(int x, int y, int healPoints);

    int getHealPoints() const;

    void interact(player* Player) override;
};

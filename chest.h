#pragma once
#include "entity.h"
class chest :
    public entity
{
public:
    chest(int posX, int posY, int lootedKeyFragment, int lootedGold);

    int getLootedGold() const;
    int getLootedKeyFragment() const;

    void interact(player* Player) override;
protected:
    int lootedGold;
    int lootedKeyFragment;
};

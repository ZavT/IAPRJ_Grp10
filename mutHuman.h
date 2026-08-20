#pragma once
#include "enemy.h"
class mutHuman :
    public enemy
{
public:
	mutHuman(int x, int y, int id);

	void displayStats() const override;
};


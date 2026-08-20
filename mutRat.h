#pragma once
#include "enemy.h"
class mutRat :
    public enemy
{
public:
	mutRat(int x, int y, int id);

	void displayStats() const override;
};


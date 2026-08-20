#pragma once
#include "player.h"
class inventory : public player
{
private:
	int tab;
	int weapons;
	int potions;
	int others;
	int items;

public:
	inventory();
	void inventoryMenu();
};


#pragma once
#include <vector>
#include "player.h"
#include "weapon.h"
#include "consumable.h"

class inventory 
{
private:
	bool bagOpen;
	int tab;
	int equippedWeaponIndex;
	std::vector<weapon> ownedWeapons;
	std::vector<consumable> ownedPotions;
	int others;

public:
	inventory();
	void inventoryMenu(player& p);
	void addWeapon(weapon newWeapon);
	void addPotion(consumable newPotion);
};


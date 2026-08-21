#pragma once
#include "weapon.h"
#include "consumable.h"
class itemDB {
public: //static dont need to create a itemdb obj pls just use "itemDB::GetCombatKnife();" for eg.
	//weapons
	static weapon getCombatKnife();
	static weapon getAssaultRifle();
	static weapon getAxe();
	static weapon getSniperRifle();
	static weapon getSledgeHammer();
	static weapon getPistol();

	//potions
	static consumable getHealthPotion();
	static consumable getAccuracyPotion();
	static consumable getDamagePotion();
};
#include "weapon.h"

weapon::weapon() : item("weapon test", 0, 0) {
	damage = 0;
	accuracy = 0;
	isMelee = false;
}

weapon::weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc)
	: item(weaponname, weaponprice,  weaponAP){
	damage = weapondmg;
	accuracy = weaponacc;
	isMelee = false;
}

int weapon::getweapondmg(player& p){
	if (isMelee)
	{
		return damage + static_cast<int>(p.getPlayerStrengthFinal());
	}
	else
	{
		return damage ;
	}
}

int weapon::getweaponacc(player& p){
	if (isMelee)
	{
		return accuracy;
	}
	else
	{
		return accuracy + static_cast<int>(p.getPlayerStrengthFinal());
	}
}

void weapon::setMeleeWeapon(bool m)
{
	isMelee = m;
}

bool weapon::getweaponismelee()
{
	return isMelee;
}

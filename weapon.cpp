#include "weapon.h"

weapon::weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc, bool isM)
	: item(weaponname, weaponprice,  weaponAP){
	damage = weapondmg;
	accuracy = weaponacc;
	isMelee = isM;
}

int weapon::getweapondmg(player& p){
	if (isMelee)
	{
		return damage + static_cast<int>(p.getPlayerStrengthFinal());
	}
	else
	{
		return damage;
	}
}

int weapon::getweaponacc(){
	return accuracy;
}

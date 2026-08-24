#include "weapon.h"

weapon::weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc)
	: item(weaponname, weaponprice,  weaponAP){
	damage = weapondmg;
	accuracy = weaponacc;
}

int weapon::getweapondmg(){
	return damage;
}

int weapon::getweaponacc(){
	return accuracy;
}


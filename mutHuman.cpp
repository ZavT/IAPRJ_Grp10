#include "mutHuman.h"
#include <iostream>
using namespace std;

mutHuman::mutHuman(int posX, int posY, int id)
	: enemy(posX, posY, id + '0', 20, attack, weapon) {
}

void mutHuman::displayStats() const
{
	string weaponName;
	switch (getWeapon()) {
	case 1:
		weaponName = "Assault Rifle";
		break;
	case 2:
		weaponName = "Axe";
		break;
	case 3:
		weaponName = "Sniper Rifle";
		break;
	case 4:
		weaponName = "Sledgehammer";
		break;
	case 5:
		weaponName = "Pistol";
		break;
	default:
		weaponName = "Unknown";
	}
	cout << "Mutant Human" << " Health:" << getHealth() << " Attack:" << getAttack() << " Weapon:" << weaponName;
}
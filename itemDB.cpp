#include "itemDB.h"

//WEAPONS
weapon itemDB::getCombatKnife(){
	//weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc);
	return weapon("Combat Knife",0, 1, 5, 100 );
}

weapon itemDB::getAssaultRifle(){
	return weapon("Assault Rifle",20,2,15,85);
}

weapon itemDB::getAxe(){
	return weapon("Axe", 10, 1, 10, 98);
}

weapon itemDB::getSniperRifle(){
	return weapon("Sniper Rifle", 30, 3, 25, 95);
}

weapon itemDB::getSledgeHammer(){
	return weapon("Sledge Hammer", 15, 2, 15, 98);
}

weapon itemDB::getPistol(){
	return weapon("Pistol",10,2,5,70);
}

//consumable::consumable(std::string potionname, int potionprice, int potionAP, int potioneffectvalue, int potioneffecttype)
consumable itemDB::getHealthPotion(){
	return consumable("Health Potion", 10,1,20,1); // type 1 = health potion 
}

consumable itemDB::getAccuracyPotion(){
	return consumable("Accuracy Potion", 20, 1, 20, 2); //type 2 = accuracy
}

consumable itemDB::getDamagePotion() {
	return consumable("Damage Potion", 20, 1, 15, 3); //type 3 = damage hello
}


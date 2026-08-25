#pragma once
#include "item.h"
#include "player.h"
#include <string>
class weapon :
    public item {
private: 
    int damage;
    int accuracy;
    bool isMelee;

public:
    weapon();
    weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc);
    int getweapondmg(player& p);
    int getweaponacc();
    void setMeleeWeapon(bool m);
    bool getweaponismelee();
};

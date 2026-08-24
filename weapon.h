#pragma once
#include "item.h"
#include <string>
class weapon :
    public item {
private: 
    int damage;
    int accuracy;

public:
    weapon(std::string weaponname, int weaponprice, int weaponAP, int weapondmg, int weaponacc);
    int getweapondmg();
    int getweaponacc();

};

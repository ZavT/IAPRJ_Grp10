#pragma once
#include "item.h"
#include <string>
class consumable :
    public item {

public:
    consumable(std::string potionname, int potionprice, int potionAP, int potioneffectvalue, int potioneffecttype);
    int getpotType();
    int getpotValue();
};

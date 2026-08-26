#pragma once
#include "item.h"
#include <string>
class consumable :
    public item {

private:
    int effectvalue;
    int effecttype;

public:
    consumable();
    consumable(std::string potionname, int potionprice, int potionAP, int potioneffectvalue, int potioneffecttype);
    int getpotType();
    int getpotValue();
};

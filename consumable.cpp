#include "consumable.h"

consumable::consumable() : item("Empty", 0, 0) { //fix errors
	effectvalue = 0;
	effecttype = 0;
}

consumable::consumable(std::string potionname, int potionprice, int potionAP, int potioneffectvalue, int potioneffecttype)
	:item(potionname, potionprice, potionAP)
{
	effectvalue = potioneffectvalue;
	effecttype = potioneffecttype;
}

int consumable::getpotType()
{
	return effecttype;
}

int consumable::getpotValue()
{
	return effectvalue;
}


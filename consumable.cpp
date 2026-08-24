#include "consumable.h"

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


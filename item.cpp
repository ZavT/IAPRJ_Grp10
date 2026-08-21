#include "item.h"

item::item(std::string itemname, int itemprice, int itemAP){
	name = itemname;
	price = itemprice;
	apcost = itemAP;
}

std::string item::getItemName(){
	return name;
}

int item::getItemPrice(){
	return price;
}

int item::getItemAPcost(){
	return apcost;
}

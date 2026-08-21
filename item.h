#pragma once
#include <string>
#include "inventory.h"
class item{

private:
    std::string name;
    int price;
    int apcost;

public: 
    item(std::string name, int price, int apCost);
    std::string getItemName();
    int getItemPrice();
    int getItemAPcost();
};


#include "alchemist.h"
#include <iostream>
#include <conio.h>
#include "itemDB.h"
#include <thread>
#include <chrono>

#define ESCAPE_KEY 27

alchemist::alchemist()
{
    isOpen = false;
}

void alchemist::alchemistOpen(player& p, inventory& bag)
{
    isOpen = true;

    while (isOpen) {
        system("CLS");

        std::cout << "\t============Alchemist============\n\n";

        std::cout << "AP: Action points. Each potion requires a certain amount of AP to use.\n\n" << std::endl;
        std::cout << "Enter the item's number to purchase it.\n\n" << std::endl;
        std::cout << "1. Health Potion. Cost: 10 gold. <1 AP | +20 HP>\n" << std::endl;
        std::cout << "2. Damage potion. Cost: 20 gold. <1 AP | Increase damage by 15 for that encounter.>\n" << std::endl;
        std::cout << "\n\t[ESC] Exit to game\n";

        int ch = _getch();

        if (ch == ESCAPE_KEY) {
            isOpen = false;
            break;
        }

        int price = 0;
        consumable toAdd;
        bool validChoice = true;

        switch (ch) {
        case '1':
            price = 10;
            toAdd = itemDB::getHealthPotion();
            break;
        case '2':
            price = 20;
            toAdd = itemDB::getDamagePotion();
            break;
        default:
            validChoice = false;
            break;
        }

        if (!validChoice) continue;

        if (p.getPlayerGold() >= price) {
            p.setPlayerGold(p.getPlayerGold() - price);
            bag.addPotion(toAdd);
            std::cout << "\n\tPurchase successful! " << toAdd.getItemName() << " added to inventory.\n";
        }
        else {
            std::cout << "\n\tYou don't have enough gold for that item.\n";
        }

        std::cout << "\tPress any key to continue...";
        (void)_getch();
    }
}

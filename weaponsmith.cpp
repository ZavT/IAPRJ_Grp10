#include "weaponsmith.h"
#include <iostream>
#include <conio.h>
#include "itemDB.h"
#include <thread>
#include <chrono>

#define ESCAPE_KEY 27

weaponsmith::weaponsmith()
{
    isOpen = false;
}

void weaponsmith::weaponsmithOpen(player& p, inventory& bag)
{
    isOpen = true;

    while (isOpen) {
        system("CLS");

        std::cout << "\t============Weaponsmith============\n\n";

        std::cout << "AP: Action points. Each weapon requires a certain amount of AP to use.\n\n" << std::endl;
        std::cout << "Enter the item's number to purchase it.\n\n" << std::endl;
        std::cout << "1. Assault Rifle. Cost: 20 gold. <2 AP | 15 DMG | 85% Accuracy>\n" << std::endl;
        std::cout << "2. Axe. Cost: 10 gold. <1 AP | 10 DMG | 98% Accuracy>\n" << std::endl;
        std::cout << "3. Sniper Rifle. Cost: 30 gold. <3 AP | 25 DMG | 95% Accuracy>\n" << std::endl;
        std::cout << "4. Sledgehammer. Cost: 15 gold. <2 AP | 15 DMG | 98% Accuracy>\n" << std::endl;
        std::cout << "5. Pistol. Cost: 10 gold. <2 AP | 5 DMG | 70% Accuracy>\n" << std::endl;
        std::cout << "\n\t[ESC] Exit to game\n";

        int ch = _getch();

        if (ch == ESCAPE_KEY) {
            isOpen = false;
            break;
        }

        int price = 0;
        weapon toAdd;
        bool validChoice = true;

        switch (ch) {
        case '1':
            price = 20;
            toAdd = itemDB::getAssaultRifle();
            break;
        case '2':
            price = 10;
            toAdd = itemDB::getAxe();
            break;
        case '3':
            price = 30;
            toAdd = itemDB::getSniperRifle();
            break;
        case '4':
            price = 15;
            toAdd = itemDB::getSledgeHammer();
            break;
        case '5':
            price = 5;
            toAdd = itemDB::getPistol();
            break;
        default:
            validChoice = false;
            break;
        }

        if (!validChoice) continue;

        if (p.getPlayerGold() >= price) {
            p.setPlayerGold(p.getPlayerGold() - price);
            bag.addWeapon(toAdd);
            std::cout << "\n\tPurchase successful! " << toAdd.getItemName() << " added to inventory.\n";
        }
        else {
            std::cout << "\n\tYou don't have enough gold for that item.\n";
        }

        std::cout << "\tPress any key to continue...";
        (void)_getch();
    }
}

#include <iostream>
#include "inventory.h"
#include <conio.h> //char input
#include <iomanip>

inventory::inventory()
{
	tab=0;
	weapons=0;
	potions=0;
	others=0;
	items=0;
}

//press arrow keys to swaps btw tabs (Weapon, potions and others)
//press number to check item stats
//in combat
	//for weapon ask player if they want to equip/unequip
	//for potion ask player if they want to consume

void inventory::inventoryMenu()
{
	std::cout << "\t\t======Inventory======\n\n";

	std::cout << "Tab\t"
		<< std::left << std::setw(20) << "WEAPONS =="
		<< std::setw(20) << " POTIONS =="
		<< "OTHERS\n\n";

	// Item Row 1
	std::cout << "\t"
		<< std::left << std::setw(20) << "1. Assault Rifle"
		<< std::setw(20) << "1. Health x10"
		<< "1. Money x 1000\n";

	// Item Row 2
	std::cout << "\t"
		<< std::left << std::setw(20) << "2. Axe"
		<< std::setw(20) << "2. Accuracy x 1"
		<< "2. Key fragments\n";

	// Item Row 3
	std::cout << "\t"
		<< std::left << std::setw(20) << "3. Sniper Rifle"
		<< std::setw(20) << "3. Attack potion"
		<< "3. Map\n";

	// Item Row 4
	std::cout << "\t"
		<< std::left << std::setw(20) << "4. Sledgehammer"
		<< std::setw(20) << ""
		<< "\n";

	// Item Row 5
	std::cout << "\t"
		<< std::left << std::setw(20) << "5. Pistol"
		<< std::setw(20) << ""
		<< "\n\n";

	// Footer Instructions
	std::cout << "\tPress Left , right arrow key to switch tabs\n";
	std::cout << "\tPress the number to see item in current tab\n";
	std::cout << "\tPress the escape to return to map\n";

	while (true) {
		int ch = _getch();
		if (ch == 27) { //escape key
			break;
		}
	}
}

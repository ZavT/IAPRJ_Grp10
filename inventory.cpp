#include <conio.h> //char input
#include <iostream>
#include "inventory.h"

inventory::inventory()
{
	tab=0;
	weapons=0;
	potions=0;
	others=0;
	items=0;
	input = ' ';
}

void inventory::inventoryMenu()
{
	int ch = _getch();

	if (ch == 'i' || ch == 'I') {
		std::cout << "========== INVENTORY =========" << std::endl;
		std::cout << "WEAPON ==== POTIONS ==== OTHERS" << std::endl;

	}
}

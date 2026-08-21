#include <iostream>
#include "inventory.h"
#include <conio.h> //char input
#include <iomanip>

#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

inventory::inventory()
{
	tab = 0;
	weapons = 0;
	potions = 0;
	others = 0;
	items = 0;
	bagOpen = false;
}

//left with
	//equip/unequip weapon 
	//consumption of potions
//show stats

void inventory::inventoryMenu() 
{
	bagOpen = true;
	tab = 0; //makes sure to open ALL tab

	while (bagOpen) {
		system("CLS");

		std::cout << "\t\t======Inventory======\n\n";

		//show active tab (maybe use clour?)
		std::cout << (tab == 0 ? "[ALL]" : "ALL") << std::setw(20)
			<< (tab == 1 ? "[WEAPONS]" : "WEAPONS") << std::setw(20)
			<< (tab == 2 ? "[POTIONS]" : "POTIONS") << std::setw(20)
			<< (tab == 3 ? "[OTHERS]" : "OTHERS") << "\n\n";

		if (tab == 0) { // ALL TAB
			
			std::cout << "\t1. Knife\n";
			std::cout << "\t2. Assault Rifle\n";
			std::cout << "\t3. Axe\n";
			std::cout << "\t4. Sniper Rifle\n";
			std::cout << "\t5. Sledgehammer\n";
			std::cout << "\t6. Pistol\n";
			std::cout << "\t7. HP potion x10\n";
			std::cout << "\t8. Acc potion x 1\n";
			std::cout << "\t9. Atk potion\n";
			std::cout << "\t10. Money x 1000\n";
			std::cout << "\t11. Key fragments x1\n";
			std::cout << "\t12. Map\n"; 

		}
		else if (tab == 1) { // WEAPONS TAB
			
			std::cout << "\t1. Knife\n";
			std::cout << "\t2. Assault Rifle\n";
			std::cout << "\t3. Axe\n";
			std::cout << "\t4. Sniper Rifle\n";
			std::cout << "\t5. Sledgehammer\n";
			std::cout << "\t6. Pistol\n";

		}
		else if (tab == 2) { // POTIONS TAB
			
			std::cout << "\t1. HP potion x10\n";
			std::cout << "\t2. Acc potion x 1\n";
			std::cout << "\t3. Atk potion\n";
		}
		else if (tab == 3) { // OTHERS TAB
			
			std::cout << "\t1. Money x 1000\n";
			std::cout << "\t2. Key fragments x1\n";
			std::cout << "\t3. Stat points x1\n";
		}

		//instructions
		std::cout << "\n";
		std::cout << "\tPress left or right arrow key to switch between tabs\n";
		std::cout << "\tPress the number to see item in current tab\n";
		std::cout << "\tPress ESCAPE to return to map\n";

		int ch = _getch();

		if (ch == 0 || ch == 224) {
			ch = _getch(); 

			if (ch == KEY_ARROW_LEFT) {
				tab--; // Move one tab left
				if (tab < 0) tab = 3; // Wrap around to the end if they go too far
			}
			else if (ch == KEY_ARROW_RIGHT) {
				tab++; // Move one tab right
				if (tab > 3) tab = 0; // Wrap around to the start
			}
		}

		else if (ch == 27) { // 27 is the Escape key
			bagOpen = false;
		}
	}
}

#include <iostream>
#include <conio.h> //char input
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm> //std::max
#include "inventory.h"
#include "itemDB.h"

#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

inventory::inventory()
{
	bagOpen = false;
	tab = 0;
	equippedWeaponIndex = 0;
	ownedWeapons.push_back(itemDB::getCombatKnife());
	ownedPotions.push_back(itemDB::getHealthPotion());
	others = 0;
	statPoints = 5;
	
}

void inventory::addWeapon(weapon newWeapon)
{
	ownedWeapons.push_back(newWeapon);
}

void inventory::addPotion(consumable newPotion)
{
	ownedPotions.push_back(newPotion);
}

//left with
	//others items
 
void inventory::inventoryMenu(player& p)
{
	bagOpen = true;
	tab = 0;

	while (bagOpen) {
		system("CLS");

		std::cout << "\t====== INVENTORY ======\t\t====== CHARACTER ======\n\n";

		// 1. Build the Left Column (Items)
		std::vector<std::string> leftCol;

		std::string tabs = (tab == 0 ? "[ALL]   " : " ALL    ") +
			std::string(tab == 1 ? "[WEAPONS]   " : " WEAPONS    ") +
			std::string(tab == 2 ? "[POTIONS]   " : " POTIONS    ") +
			std::string(tab == 3 ? "[OTHERS]" : " OTHERS ");
		leftCol.push_back(tabs);
		leftCol.push_back(""); // Spacer

		if (tab == 0) { // ALL TAB 
			int index = 1;
			for (size_t i = 0; i < ownedWeapons.size(); i++) {
				std::string equipTag = (i == equippedWeaponIndex) ? " [E]" : "";
				leftCol.push_back(std::to_string(index++) + ". " + ownedWeapons[i].getItemName() + equipTag);
			}
			for (size_t i = 0; i < ownedPotions.size(); i++) {
				leftCol.push_back(std::to_string(index++) + ". " + ownedPotions[i].getItemName());
			}
			
			leftCol.push_back(std::to_string(index++) + ". Stat points x " + std::to_string(statPoints));
		}
		else if (tab == 1) { // WEAPONS TAB
			if (ownedWeapons.empty()) leftCol.push_back("Bag is empty.");
			for (size_t i = 0; i < ownedWeapons.size(); i++) {
				std::string equipTag = (i == equippedWeaponIndex) ? " [EQUIPPED]" : "";
				leftCol.push_back(std::to_string(i + 1) + ". " + ownedWeapons[i].getItemName() + equipTag);
			}
		}
		else if (tab == 2) { // POTIONS TAB
			if (ownedPotions.empty()) leftCol.push_back("Bag is empty.");
			for (size_t i = 0; i < ownedPotions.size(); i++) {
				leftCol.push_back(std::to_string(i + 1) + ". " + ownedPotions[i].getItemName());
			}
		}
		else if (tab == 3) { // OTHERS TAB
			leftCol.push_back("3. Stat points x " + std::to_string(statPoints));
		}

		// 2. Build the Right Column (Stats)
		std::vector<std::string> rightCol;
		rightCol.push_back("Name: " + p.getPlayerName());
		rightCol.push_back("");
		rightCol.push_back("HP:   " + std::to_string(p.getPlayerHealthPoints()) + " / " + std::to_string(p.getPlayerMaxHealthPoints()));
		rightCol.push_back("STR:  " + std::to_string(static_cast<int>(p.getPlayerStrengthFinal())));
		rightCol.push_back("AGI:  " + std::to_string(static_cast<int>(p.getPlayerAgilityFinal())));
		rightCol.push_back("LUC:  " + std::to_string(static_cast<int>(p.getPlayerLuck())));
		rightCol.push_back("END:  " + std::to_string(static_cast<int>(p.getPlayerEnduranceFinal())));
		rightCol.push_back("INT:  " + std::to_string(static_cast<int>(p.getPlayerIntelligenceFinal())));

		// 3. Print both columns side-by-side perfectly
		size_t maxRows = std::max(leftCol.size(), rightCol.size());
		for (size_t i = 0; i < maxRows; i++) {
			std::string left = (i < leftCol.size()) ? leftCol[i] : "";
			std::string right = (i < rightCol.size()) ? rightCol[i] : "";
			std::cout << "\t" << std::left << std::setw(45) << left << right << "\n";
		}

		// Instructions
		std::cout << "\n\t[Left/Right] Switch Tabs | [1-9] Inspect | [N] Edit Name | [ESC] Close\n";

		// 4. Input & Sub-menus
		int ch = _getch();

		if (ch == 'n' || ch == 'N') {
			std::string newName;
			std::cout << "\n\tEnter new name: ";
			std::cin >> newName;
			p.setPlayerName(newName);
		}
		else if (ch >= '1' && ch <= '9') {
			int itemIndex = ch - '1';

			bool inDetails = true;
			while (inDetails) { // NESTED LOOP: Pauses main menu to show details
				system("CLS");
				std::cout << "\t\t====== Details ======\n\n";

				if (tab == 1 && static_cast<size_t>(itemIndex) < ownedWeapons.size()) {
					std::cout << "\t" << ownedWeapons[itemIndex].getItemName() << "\n";
					std::cout << "\tDamage:   " << ownedWeapons[itemIndex].getweapondmg() << "\n";
					std::cout << "\tAccuracy: " << ownedWeapons[itemIndex].getweaponacc() << "%\n\n";
					std::cout << "\t[E] Equip  |  [U] Unequip  |  [ESC] Back\n";

					int act = _getch();
					if (act == 'e' || act == 'E') { equippedWeaponIndex = itemIndex; inDetails = false; }
					else if (act == 'u' || act == 'U') { equippedWeaponIndex = -1; inDetails = false; }
					else if (act == 27) { inDetails = false; }
				}
				else if (tab == 2 && static_cast<size_t>(itemIndex) < ownedPotions.size()) {
					std::cout << "\t" << ownedPotions[itemIndex].getItemName() << "\n";
					std::cout << "\tAP Cost: " << ownedPotions[itemIndex].getItemAPcost() << "\n\n";
					std::cout << "\t[C] Consume  |  [ESC] Back\n";

					int act = _getch();
					if (act == 'c' || act == 'C') {
						p.setPlayerHealthPoints(p.getPlayerHealthPoints() + 20); // Heal player
						ownedPotions.erase(ownedPotions.begin() + itemIndex); // Delete potion
						inDetails = false;
					}
					else if (act == 27) { inDetails = false; }
				}
				else if (tab == 3 && itemIndex == 2) { // Index 2 is the 3rd item (Stat Points)
					if (statPoints <= 0) {
						std::cout << "\tYou have no stat points left!\n\n\t[ESC] Back\n";
						if (_getch() == 27) inDetails = false;
					}
					else {
						std::cout << "\tUnspent Points: " << statPoints << "\n\n";
						std::cout << "\t[1] +1 STR\n\t[2] +1 AGI\n\t[3] +1 LUC\n\t[4] +1 END\n\t[5] +1 INT\n\n\t[ESC] Back\n";

						int act = _getch();
						if (act == '1') { p.setPlayerStrength(p.getPlayerStrength() + 1); statPoints--; }
						else if (act == '2') { p.setPlayerAgility(p.getPlayerAgility() + 1); statPoints--; }
						else if (act == '3') { p.setPlayerLuck(p.getPlayerLuck() + 1); statPoints--; }
						else if (act == '4') { p.setPlayerEndurance(p.getPlayerEndurance() + 1); statPoints--; }
						else if (act == '5') { p.setPlayerIntelligence(p.getPlayerIntelligence() + 1); statPoints--; }
						else if (act == 27) { inDetails = false; }
					}
				}
				else {
					inDetails = false; // Invalid selection
				}
			}
		}
		else if (ch == 0 || ch == 224) {
			ch = _getch();
			if (ch == KEY_ARROW_LEFT) { tab--; if (tab < 0) tab = 3; }
			else if (ch == KEY_ARROW_RIGHT) { tab++; if (tab > 3) tab = 0; }
		}
		else if (ch == 27) {
			bagOpen = false;
		}
	}
}


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
	ownedPotions.push_back(itemDB::getHealthPotion()); //change later
	others = 0;
	statPoints = 0;
}

void inventory::addWeapon(weapon newWeapon)
{
	ownedWeapons.push_back(newWeapon);
}

void inventory::addPotion(consumable newPotion)
{
	ownedPotions.push_back(newPotion);
}

weapon inventory::getEquippedWeapon(){
	return ownedWeapons[equippedWeaponIndex];
}

bool inventory::hasWeapon(std::string weaponName)
{
	//check if weapon in bag
	for (size_t i = 0; i < ownedWeapons.size(); i++) {
		if (ownedWeapons[i].getItemName() == weaponName) {
			return true; 
		}
	}
	return false;
}

//left with
	//others items
 
void inventory::inventoryMenu(player& p)
{
	bagOpen = true;
	tab = 0;

	while (bagOpen) {
		system("CLS");

		
		std::cout << "\t====== INVENTORY ======\n\n";

		std::cout << "\t" << (tab == 0 ? "[ALL]   " : " ALL    ")
			<< (tab == 1 ? "[WEAPONS]   " : " WEAPONS    ")
			<< (tab == 2 ? "[POTIONS]   " : " POTIONS    ")
			<< (tab == 3 ? "[OTHERS]" : " OTHERS ") << "\n\n";

		if (tab == 0) { // ALL TAB 
			int index = 1;
			for (size_t i = 0; i < ownedWeapons.size(); i++) {
				std::string equipTag = (i == equippedWeaponIndex) ? " [E]" : "";
				std::cout << "\t" << index++ << ". " << ownedWeapons[i].getItemName() << equipTag << "\n";
			}
			for (size_t i = 0; i < ownedPotions.size(); i++) {
				std::cout << "\t" << index++ << ". " << ownedPotions[i].getItemName() << "\n";
			}

			std::cout << "\t" << index++ << ". Stat points x " << p.getStatPoints() << "\n";
			std::cout << "\t" << index++ << ". Gold x " << p.getPlayerGold() << "\n";
			std::cout << "\t" << index++ << ". Key Fragments x " << p.getPlayerKeyFragment() << "\n";
		}

		else if (tab == 1) { // WEAPONS TAB
			if (ownedWeapons.empty()) std::cout << "\tBag is empty.\n";
			for (size_t i = 0; i < ownedWeapons.size(); i++) {
				std::string equipTag = (i == equippedWeaponIndex) ? " [EQUIPPED]" : "";
				std::cout << "\t" << (i + 1) << ". " << ownedWeapons[i].getItemName() << equipTag << "\n";
			}
		}
		else if (tab == 2) { // POTIONS TAB
			if (ownedPotions.empty()) std::cout << "\tBag is empty.\n";
			for (size_t i = 0; i < ownedPotions.size(); i++) {
				std::cout << "\t" << (i + 1) << ". " << ownedPotions[i].getItemName() << "\n";
			}
		}
		else if (tab == 3) { // OTHERS TAB
			std::cout << "\t1. Stat points x " << p.getStatPoints() << "\n";
			std::cout << "\t2. Gold x " << p.getPlayerGold() << "\n";
			std::cout << "\t3. Key Fragments x " << p.getPlayerKeyFragment() << "\n";
		}

		std::cout << "\n\t----------------------------------------------------------\n\n";

		//details & stat allcoation
		std::vector<std::string> leftCol; // instructions or inspection menu

		// Character stats
		std::vector<std::string> rightCol;
		rightCol.push_back("Name: " + p.getPlayerName());

		rightCol.push_back("Lvl:  " + std::to_string(p.getPlayerLevel()) + " (" + std::to_string(p.getPlayerExp()) + " EXP)");

		rightCol.push_back("HP:   " + std::to_string(p.getPlayerHealthPoints()) + " / " + std::to_string(p.getPlayerMaxHealthPoints()));
		rightCol.push_back("STR:  " + std::to_string(static_cast<int>(p.getPlayerStrengthFinal())));
		rightCol.push_back("AGI:  " + std::to_string(static_cast<int>(p.getPlayerAgilityFinal())));
		rightCol.push_back("LUC:  " + std::to_string(static_cast<int>(p.getPlayerLuck())));
		rightCol.push_back("END:  " + std::to_string(static_cast<int>(p.getPlayerEnduranceFinal())));
		rightCol.push_back("INT:  " + std::to_string(static_cast<int>(p.getPlayerIntelligenceFinal())));

		//left (Instructions)
		leftCol.push_back("[Left/Right] Switch Tabs");
		leftCol.push_back("[1-9] Inspect Item");
		leftCol.push_back("[N] Edit Name");
		leftCol.push_back("[ESC] Close Inventory");

		// bottom side-by-side
		size_t maxRows = std::max(leftCol.size(), rightCol.size());
		for (size_t i = 0; i < maxRows; i++) {
			std::string left = (i < leftCol.size()) ? leftCol[i] : "";
			std::string right = (i < rightCol.size()) ? rightCol[i] : "";
			std::cout << "\t" << std::left << std::setw(30) << left << right << "\n";
		}

		// INPUT LOGIC & NESTED MENUS
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
			while (inDetails) { // Freezes main inventory to update the bottom left menu
				system("CLS");

				std::cout << "\t====== INVENTORY ======\n\t(Inspecting Item...)\n\n";
				std::cout << "\t----------------------------------------------------------\n\n";

				leftCol.clear();

				if (tab == 1 && static_cast<size_t>(itemIndex) < ownedWeapons.size()) {
					leftCol.push_back("Item: " + ownedWeapons[itemIndex].getItemName());
					leftCol.push_back("AP Cost: " + std::to_string(ownedWeapons[itemIndex].getItemAPcost()));
					leftCol.push_back("Acc:  " + std::to_string(ownedWeapons[itemIndex].getweaponacc()) + "%");
					leftCol.push_back("Dmg:  " + std::to_string(ownedWeapons[itemIndex].getweapondmg(p) - p.getPlayerStrength()));
					leftCol.push_back("");
					leftCol.push_back("[E] Equip | [U] Unequip | [ESC] Back");
				}
				else if (tab == 2 && static_cast<size_t>(itemIndex) < ownedPotions.size()) {
					leftCol.push_back("Item: " + ownedPotions[itemIndex].getItemName());
					leftCol.push_back("AP Cost: " + std::to_string(ownedPotions[itemIndex].getItemAPcost()));
					leftCol.push_back("");
					leftCol.push_back("[C] Consume | [ESC] Back");
				}
				else if (tab == 3 && itemIndex == 0) { // 1st item (Index 0) in Others tab is Stat Points
					leftCol.push_back("Unspent Points: " + std::to_string(p.getStatPoints()));
					leftCol.push_back("");
					leftCol.push_back("Inputs: S+, S-, A+, A-, L+, L-");
					leftCol.push_back("        E+, E-, I+, I-");
					leftCol.push_back("Type 'Back' to return");
				}
				else {
					inDetails = false;
					continue;
				}

				// stat side
				rightCol.clear();
				rightCol.push_back("Name: " + p.getPlayerName());
				rightCol.push_back("HP:   " + std::to_string(p.getPlayerHealthPoints()) + " / " + std::to_string(p.getPlayerMaxHealthPoints()));
				rightCol.push_back("STR:  " + std::to_string(p.getPlayerStrength()));
				rightCol.push_back("AGI:  " + std::to_string(p.getPlayerAgility()));
				rightCol.push_back("LUC:  " + std::to_string(p.getPlayerLuck()));
				rightCol.push_back("END:  " + std::to_string(p.getPlayerEndurance()));
				rightCol.push_back("INT:  " + std::to_string(p.getPlayerIntelligence()));

				// Print the sub-menu side-by-side
				size_t maxRows = std::max(leftCol.size(), rightCol.size());
				for (size_t i = 0; i < maxRows; i++) {
					std::string left = (i < leftCol.size()) ? leftCol[i] : "";
					std::string right = (i < rightCol.size()) ? rightCol[i] : "";
					std::cout << "\t" << std::left << std::setw(40) << left << right << "\n";
				}

				// use std::cin for stats
				if (tab == 3 && itemIndex == 0) {
					std::string statInput;
					std::cout << "\n\tEnter input: ";
					std::cin >> statInput;

					if (statInput == "S+" && p.getStatPoints() > 0) { p.setPlayerStrength(p.getPlayerStrength() + 1); p.setStatPoints(p.getStatPoints() - 1); }
					else if (statInput == "S-" && p.getPlayerStrength() > 2) { p.setPlayerStrength(p.getPlayerStrength() - 1); p.setStatPoints(p.getStatPoints() + 1); }

					else if (statInput == "A+" && p.getStatPoints() > 0) { p.setPlayerAgility(p.getPlayerAgility() + 1); p.setStatPoints(p.getStatPoints() - 1); }
					else if (statInput == "A-" && p.getPlayerAgility() > 2) { p.setPlayerAgility(p.getPlayerAgility() - 1); p.setStatPoints(p.getStatPoints() + 1); }

					else if (statInput == "L+" && p.getStatPoints() > 0) { p.setPlayerLuck(p.getPlayerLuck() + 1); p.setStatPoints(p.getStatPoints() - 1); }
					else if (statInput == "L-" && p.getPlayerLuck() > 2) { p.setPlayerLuck(p.getPlayerLuck() - 1); p.setStatPoints(p.getStatPoints() + 1); }

					else if (statInput == "E+" && p.getStatPoints() > 0) { p.setPlayerEndurance(p.getPlayerEndurance() + 1); p.setStatPoints(p.getStatPoints() - 1); }
					else if (statInput == "E-" && p.getPlayerEndurance() > 2) { p.setPlayerEndurance(p.getPlayerEndurance() - 1); p.setStatPoints(p.getStatPoints() + 1); }

					else if (statInput == "I+" && p.getStatPoints() > 0) { p.setPlayerIntelligence(p.getPlayerIntelligence() + 1); p.setStatPoints(p.getStatPoints() - 1); }
					else if (statInput == "I-" && p.getPlayerIntelligence() > 2) { p.setPlayerIntelligence(p.getPlayerIntelligence() - 1); p.setStatPoints(p.getStatPoints() + 1); }

					else if (statInput == "Back" || statInput == "back") { 
						inDetails = false; }
				}

				// use standard _getch() for the rest
				else {
					int act = _getch();

					if (tab == 1) { // Weapons
						if (act == 'e' || act == 'E') { equippedWeaponIndex = itemIndex; inDetails = false; }
						else if (act == 'u' || act == 'U') { equippedWeaponIndex = -1; inDetails = false; }
					}
					else if (tab == 2) { // Potions
						if (act == 'c' || act == 'C') {
							p.setPlayerHealthPoints(p.getPlayerHealthPoints() + 20);
							ownedPotions.erase(ownedPotions.begin() + itemIndex);
							inDetails = false;
						}
					}

					if (act == 27) inDetails = false; // ESC Key
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


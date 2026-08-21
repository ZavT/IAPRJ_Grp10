#pragma once

class inventory 
{
private:
	int tab;
	int weapons;
	int potions;
	int others;
	int items;
	bool bagOpen;

public:
	inventory();
	void inventoryMenu();
};


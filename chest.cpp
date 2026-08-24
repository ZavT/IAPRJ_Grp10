#include "chest.h"
#include "player.h"
chest::chest(int posX, int posY, int lootedKeyFragment, int lootedGold)
	: entity(posX, posY, 0, 0),
	  lootedKeyFragment(lootedKeyFragment),
	  lootedGold(lootedGold)
{
}

int chest::getLootedGold() const {
	return lootedGold;
}
int chest::getLootedKeyFragment() const {
	return lootedKeyFragment;
}

// player gains looted items
void chest::interact(player* Player) {
	Player->loot(getLootedGold(), getLootedKeyFragment());
}
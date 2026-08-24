#include "motel.h"
#include "player.h"
motel::motel(int posX, int posY, int healPoints)
	: entity(posX, posY, healPoints) {
}

int motel::getHealPoints() const {
	return getHealth();
}

// heal player
void motel::interact(player* Player) {
	Player->heal(getHealPoints());
}

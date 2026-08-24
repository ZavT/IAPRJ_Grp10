#include "motel.h"
#include "player.h"
motel::motel(int posX, int posY, int healPoints)
	: entity(posX, posY, healPoints, 0) {
}

int motel::getHealPoints() const {
	return getHealthPoints();
}

// heal player
void motel::interact(player* Player) {
	Player->heal(getHealPoints());
}

#include "boss.h"

boss::~boss() {
	bossActive = false;
}

void boss::setBossActive(bool state) {
	bossActive = state;
}

bool boss::getBossActive() const {
	return bossActive;
}
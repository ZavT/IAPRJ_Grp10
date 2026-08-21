#include "enemy.h"
#include "map.h"

#include <iostream>
#include <cmath>

enemy::enemy() {
	isTargeting = false;
}

void enemy::checkForPlayer(player& player) {
	//dstx and disty between enemy and player
	int distX = getPosX() - player.getPosX();
	int distY = getPosY() - player.getPosY();

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	if (hypoDist <= 3.9) {
		isTargeting = true;
	}
	else {
		isTargeting = false;
	}
}
void enemy::enemyBorderCol(int moveX, int moveY, int maxBorderX, int maxBorderY) {
	if (getPosX() < 1 || getPosX() > (maxBorderX - 1) ||
		getPosY() < 0 || getPosY() > (maxBorderY - 1)) {

		//revert movement if they try to move out
		setPosX(getPosX() - moveX);
		setPosY(getPosY() - moveY);
	}
}

void enemy::enemyMove(int moveX, int moveY) {
	setPosX(getPosX() + moveX);
	setPosY(getPosY() + moveY);
}

void enemy::enemyBehaviour(player& player, map& currentMap) {
	if (!isTargeting) {
		//idle behaviour
		int randX = (rand() % 3) - 1;

		enemyMove(randX, 0);
		enemyBorderCol(randX, 0, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
	}

	else {
		int dirEPX = player.getPosX() - getPosX();
		int dirEPY = player.getPosY() - getPosY();

		int directionX = (dirEPX > 0) - (dirEPX < 0);
		int directionY = (dirEPY > 0) - (dirEPY < 0);

		if (std::abs(dirEPX) > std::abs(dirEPY)) {
			enemyMove(directionX, 0);
			enemyBorderCol(directionX, 0, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
		}
		else {
			enemyMove(0, directionY);
			enemyBorderCol(0, directionY, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
		}
	}
}
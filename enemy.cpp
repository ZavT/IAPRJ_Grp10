#include "enemy.h"
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

	if (hypoDist <= 2.9) {
		std::cout << "An enemy is hunting you!" << std::endl;
		isTargeting = true;
	}
	else {
		isTargeting = false;
	}
}

void enemy::enemyMove(int moveX, int moveY) {
	if (getPosX() > 0 && getPosX() < 30 && getPosY() > 0 && getPosY() < 5) {
		setPosX(getPosX() + moveX);
		setPosY(getPosY() + moveY);
	}
}

void enemy::enemyBehaviour(player& player) {
	if (!isTargeting) {
		//idle behaviour
		int randX = (rand() % 3) - 1;

		enemyMove(randX, 0);
	}

	else {
		int playerX = player.getPosX();
		int playerY = player.getPosY();

		int dirEPX = getPosX() - playerX;
		int dirEPY = getPosY() - playerY;

		enemyMove(7, 0);
	}
}
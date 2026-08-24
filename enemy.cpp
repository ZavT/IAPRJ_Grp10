#include "enemy.h"
#include "map.h"
#include "player.h"
#include <iostream>
#include <cmath>

enemy::enemy(int posX, int posY, int id, int healthPoints)
	: entity(posX, posY, id, healthPoints) {
	isTargeting = false;
	setHealthPoints(20); // hp testing
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

bool enemy::enemyCheckCol(int checkX, int checkY, player& player, enemy** allEnemies, int enemyCount, int currentIdx)
{
	//check for player collision first
	if (checkX == player.getPosX() && checkY == player.getPosY()) {
		return true;
	}
	//check collision between other enemies
	//if e is the current enemy, 
	for (int i = 0; i < enemyCount; i++) {
		if (allEnemies[i] == nullptr) {
			continue;
		}
		if (i == currentIdx) {
			continue;
		}
		if (checkX == allEnemies[i]->getPosX() && checkY == allEnemies[i]->getPosY()) {
			return true;
		}
		
	}
	return false;
}

void enemy::enemyMove(int moveX, int moveY) {
	setPosX(getPosX() + moveX);
	setPosY(getPosY() + moveY);
}

void enemy::enemyBehaviour(player& player, map& currentMap, enemy** allEnemies, int enemyCount, int currentIdx) {
	if (!isTargeting) {
		//idle behaviour
		int randX = (rand() % 3) - 1;

		int destX = getPosX() + randX; //find tile destination on x axis
		int destY = getPosY();

		if (!enemyCheckCol(destX, destY, player, allEnemies, enemyCount, currentIdx)) {
			enemyMove(randX, 0);
			enemyBorderCol(randX, 0, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
		}
	}

	else {
		int dirEPX = player.getPosX() - getPosX();
		int dirEPY = player.getPosY() - getPosY();

		int directionX = (dirEPX > 0) - (dirEPX < 0);
		int directionY = (dirEPY > 0) - (dirEPY < 0);

		if (std::abs(dirEPX) > std::abs(dirEPY)) {
			//move on x axis first if X direction vector is greater than y direction vector 
			int destX = getPosX() + directionX; //find tile destination on x axis
			int destY = getPosY();

			if (!enemyCheckCol(destX, destY, player, allEnemies, enemyCount, currentIdx)) {
				enemyMove(directionX, 0);
				enemyBorderCol(directionX, 0, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
			}
		}
		else {
			int destX = getPosX(); 
			int destY = getPosY() + directionY; //find tile destination on y axis

			if (!enemyCheckCol(destX, destY, player, allEnemies, enemyCount, currentIdx)) {
				enemyMove(0, directionY);
				enemyBorderCol(0, directionY, currentMap.getDimensionCOL(), currentMap.getDimensionROW());
			}
		}
	}
}

enemy::~enemy() {
}
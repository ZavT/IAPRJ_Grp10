#include "enemy.h"
#include <iostream>
#include <cmath>

enemy::enemy() {

}

void enemy::checkForPlayer(player& player) {
	//dstx and disty between enemy and player
	int distX = getPosX() - player.getPosX();
	int distY = getPosY() - player.getPosY();

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	if (hypoDist <= 2.9) {
		std::cout << "enemy found u" << std::endl;
	}
}
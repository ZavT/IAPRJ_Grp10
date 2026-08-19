#include "player.h"
#include <cmath>
#include <iostream>

void player::move(int moveX, int moveY) {
	//setPosition( getPosX() + moveX, getPosY() + moveY);
	setPosX(getPosX() + moveX);
	setPosY(getPosY() + moveY);
}

void player::borderCol(int moveX, int moveY) {
	if (getPosX() < 0 || getPosX() > 20) {
		setPosX(getPosX() - moveX);
	}

	if (getPosY() < 0 || getPosY() > 15) {
		setPosY(getPosY() - moveY);
	}
}

//test functions
void player::testAttack(enemy& targetenemy) {
	//dstx and disty between enemy and player
	int distX = getPosX() - targetenemy.getPosX();
	int distY = getPosY() - targetenemy.getPosY();

	int accuracy = 95;

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	int a = static_cast<int>(hypoDist);

	if (hypoDist > 2) {
		accuracy = accuracy - (a * 2);
	}
	else {
		accuracy = accuracy - a;
	}
	
	std::cout << "distance: " << hypoDist << ", accuracy: " << accuracy << std::endl;
}
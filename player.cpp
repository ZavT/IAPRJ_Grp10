#include "player.h"
#include <cmath>
#include <iostream>

player::player() // added by Noah
{
	playerName = "Survivor";

	setHealthPoints(100);
	playerHealthPoints = getHealthPoints() + playerEndurance;

	playerStrength = 2;
	playerAgility = 2;
	playerLuck = 2;
	playerEndurance = 2;
	playerIntelligence = 2;

	playerStrengthFinal = playerStrength + playerLuckBoost();
	playerAgilityFinal = playerAgility + playerLuckBoost();
	playerLuckFinal = playerLuck;
	playerEnduranceFinal = playerEndurance + playerLuckBoost();
	playerIntelligenceFinal = playerIntelligence + playerLuckBoost();

	playerActionPoints = playerAgility;

	playerCombatMode = false;
}

float player::playerLuckBoost()
{
	return (playerLuckFinal / 8);
}

//player actions
void player::move(int moveX, int moveY) {
	setPosX(getPosX() + moveX);
	setPosY(getPosY() + moveY);

	if (playerCombatMode == true)
	{
		playerActionPoints--;
	}
}

void player::borderCol(int moveX, int moveY, int maxBorderX, int maxBorderY) {
	if (getPosX() < 0 || getPosX() > (maxBorderX - 1)) {
		setPosX(getPosX() - moveX);
	}

	if (getPosY() < 0 || getPosY() > (maxBorderY - 1)) {
		setPosY(getPosY() - moveY);
	}
}

//test functions
//player attack functions testing
void player::testAttack(enemy& targetenemy) {
	//dstx and disty between enemy and player
	int distX = getPosX() - targetenemy.getPosX();
	int distY = getPosY() - targetenemy.getPosY();

	float accuracy = 95;

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	int a = static_cast<int>(hypoDist);

	if (hypoDist > 2) {
		accuracy = accuracy - (a * (8 / playerStrengthFinal));
	}
	else {
		accuracy = accuracy - a;
	}
	
	std::cout << "distance: " << hypoDist << ", accuracy: " << accuracy << std::endl;
}

void player::checkForEnemy(enemy& targetenemy)
{
	//dstx and disty between enemy and player
	int distX = getPosX() - targetenemy.getPosX();
	int distY = getPosY() - targetenemy.getPosY();

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	if (hypoDist <= 1.5) {
		std::cout << "triggered battle cutscene with enemy" << std::endl;

	}
}

//player stat functions
int player::getPlayerHealthPoints() // added by Noah
{
	return playerHealthPoints;
}
void setPlayerHealthPoints(int hp)
{
	playerHealthPoints = hp;
}
int player::getPlayerStrength() // added by Noah
{
	return playerStrength;
}
float player::getPlayerStrengthFinal() // added by Noah
{
	return playerStrengthFinal;
}
int player::getPlayerAgility()
{
	return playerAgility;
}
float player::getPlayerAgilityFinal() // added by Noah
{
	return playerAgilityFinal;
}
int player::getPlayerLuck()
{
	return playerLuck;
}
float player::getPlayerLuckFinal() // added by Noah
{
	return playerLuckFinal;
}
int player::getPlayerEndurance()
{
	return playerEndurance;
}
float player::getPlayerEnduranceFinal() // added by Noah
{
	return playerEnduranceFinal;
}
int player::getPlayerIntelligence()
{
	return playerIntelligence;
}
float player::getPlayerIntelligenceFinal() // added by Noah
{
	return playerIntelligenceFinal;
}
int player::getPlayerActionPoints()
{
	return playerActionPoints;

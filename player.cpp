#include "player.h"
#include <cmath>
#include <iostream>

player::player(int playerGold, int playerKeyFragment)
{
	playerName = "Survivor";

	setHealthPoints(100);

	playerStrength = 2;
	playerAgility = 2;
	playerLuck = 2;
	playerEndurance = 2;
	playerIntelligence = 2;

	playerActionPoints = playerAgility;

	playerHealthPoints = getPlayerMaxHealthPoints();

	statPoints = 0;

	playerCombatMode = false;
}

float player::playerLuckBoost()
{
	return (getPlayerLuck() / 8.0f);
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

void player::takeDamage(int dmg)
{
	playerHealthPoints = playerHealthPoints - dmg;
}

void player::borderCol(int moveX, int moveY, int maxBorderX, int maxBorderY) {
	if (getPosX() < 0 || getPosX() > (maxBorderX - 1)) {
		setPosX(getPosX() - moveX);
	}

	if (getPosY() < 0 || getPosY() > (maxBorderY - 1)) {
		setPosY(getPosY() - moveY);
	}
}

int player::checkEnemyCol(int checkX, int checkY, enemy** allEnemies, int enemyCount) {
	for (int i = 0; i < enemyCount; i++) {
		if (checkX == allEnemies[i]->getPosX() && checkY == allEnemies[i]->getPosY()) {
			return i; // return whichever enemy it collided with
		}
	}
	return -1; //not colliding w any enemy
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
		accuracy = accuracy - (a * (8 / getPlayerStrengthFinal()));
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

bool player::checkforbattle(enemy& targetenemy)
{
	//dstx and disty between enemy and player	
	int distX = getPosX() - targetenemy.getPosX();
	int distY = getPosY() - targetenemy.getPosY();

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	if (hypoDist <= 1.5) {
		return true;
	}
	return false;
}


//player stat functions
std::string player::getPlayerName()
{
	return playerName;
}
void player::setPlayerName(std::string name)
{
	playerName = name;
}
//player stat functions
int player::getStatPoints()
{
	return statPoints;
}
void player::setStatPoints(int sp)
{
	statPoints = sp;
}
int player::getPlayerHealthPoints()
{
	return playerHealthPoints;
}
void player::setPlayerHealthPoints(int hp)
{
	int maxHP = getPlayerMaxHealthPoints();

	if (hp > maxHP) {
		hp = maxHP;
	}
	else if (hp < 0) {
		hp = 0;
	}

	playerHealthPoints = hp;
}
int player::getPlayerMaxHealthPoints()
{
	return getHealthPoints() + static_cast<int>(getPlayerEnduranceFinal());
}
int player::getPlayerStrength()
{
	return playerStrength;
}
float player::getPlayerStrengthFinal()
{
	return playerStrength + playerLuckBoost();
}
void player::setPlayerStrength(int s)
{
	playerStrength = s;
}
int player::getPlayerAgility()
{
	return playerAgility;
}
float player::getPlayerAgilityFinal()
{
	return playerAgility + playerLuckBoost();
}
void player::setPlayerAgility(int a)
{
	playerAgility = a;
}
int player::getPlayerLuck()
{
	return playerLuck;
}
void player::setPlayerLuck(int l)
{
	playerLuck = l;
}
int player::getPlayerEndurance()
{
	return playerEndurance;
}
float player::getPlayerEnduranceFinal()
{
	return playerEndurance + playerLuckBoost();
}
void player::setPlayerEndurance(int e)
{
	playerEndurance = e;
}
int player::getPlayerIntelligence()
{
	return playerIntelligence;
}
float player::getPlayerIntelligenceFinal()
{
	return playerIntelligence + playerLuckBoost();
}
void player::setPlayerIntelligence(int i)
{
	playerIntelligence = i;
}
int player::getPlayerActionPoints()
{
	return playerActionPoints;
}
void player::setPlayerActionPoints(int ap)
{
	playerActionPoints = ap;
}


int player::getPlayerGold()
{
	return playerGold;
}
void player::setPlayerGold(int value)
{
	playerGold = value;
}
int player::getPlayerKeyFragment()
{
	return playerKeyFragment;
}
void player::setPlayerKeyFragment(int value)
{
	playerKeyFragment = value;
}

// heal player
void player::heal(int value) {
	setPlayerHealthPoints(getPlayerHealthPoints() + value);
}

// player gains looted items
void player::loot(int value1, int value2) {
	setPlayerGold(getPlayerGold() + value1);
	setPlayerKeyFragment(getPlayerKeyFragment() + value2);
}
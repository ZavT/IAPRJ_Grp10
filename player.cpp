#include <cmath>
#include <iostream>
#include "player.h"
#include "enemy.h"

//starting gold/fragments
player::player() : player(20, 0) {}

player::player(int playerGold, int playerKeyFragment) : entity(0, 0, 100, 2)
{
	playerName = "Survivor";

	setHealthPoints(9999);

	playerStrength = 100;
	playerAgility = 2;
	playerLuck = 2;
	playerEndurance = 2;
	playerIntelligence = 2;

	playerActionPoints = playerAgility;

	playerHealthPoints = getPlayerMaxHealthPoints();

	statPoints = 0;

	playerCombatMode = false;
	isAlive = true;

	this->playerGold = playerGold;
	this->playerKeyFragment = playerKeyFragment;
}

float player::playerLuckBoost()
{
	return (getPlayerLuck() / 4.0f);
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
		if (allEnemies[i] == nullptr) {
			continue;
		}
		if (checkX == allEnemies[i]->getPosX() && checkY == allEnemies[i]->getPosY()) {
			return i; // return whichever enemy it collided with
		}
	}
	return -1; //not colliding w any enemy
}

bool player::checkforbattle(enemy& targetenemy)
{
	//dstx and disty between enemy and player	
	int distX = getPosX() - targetenemy.getPosX();
	int distY = getPosY() - targetenemy.getPosY();

	//for diagonals, find hypotenuse of triangles with sides distX distY
	float hypoDist = std::sqrt((distX * distX) + (distY * distY));

	if (hypoDist <= 1) { // ENEMY RANGE 
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

void player::setBattleState(bool battlestate) {
	inBattle = battlestate;
}

bool player::getBattleState() {
	return inBattle;
}
//level 
	int player::getPlayerLevel() {
		return pLevel.getlevel();
	}

	int player::getPlayerExp() {
		return pLevel.getexp();
	}

	void player::gainExp(int amt) {
		pLevel.gainexp(amt);
		if (pLevel.checklevelup()) {
			setStatPoints(getStatPoints() + 3);
		}
	}

	bool player::checkAlive()
	{
		if (getPlayerHealthPoints() <= 0) 
		{	
			isAlive = false;
			return false;
		}

		return true;
	}

	bool player::respawn()
	{
		//set hp again
		setPlayerHealthPoints(getPlayerMaxHealthPoints());
		isAlive = true; 

		//gold reduction
		int currentGold = getPlayerGold();
		if (currentGold >= 50) {
			setPlayerGold(currentGold - 50); 
		}
		else {
			setPlayerGold(0);
		}

		return true;
	}

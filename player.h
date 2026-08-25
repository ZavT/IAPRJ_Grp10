#pragma once
#include "entity.h"
#include <string>

class enemy;

class player : public entity
{
private:
	std::string playerName;

	int playerHealthPoints;
	int playerStrength;
	int playerAgility;
	int playerLuck;
	int playerEndurance;
	int playerIntelligence;

	int playerActionPoints;

	int statPoints;

	int playerGold;
	int playerKeyFragment;

	bool playerCombatMode;

public:
	player();
	player(int playerGold, int playerKeyFragment);

	std::string getPlayerName();
	void setPlayerName(std::string name);

	//player stat functions
	int getPlayerHealthPoints();
	void setPlayerHealthPoints(int hp);
	int getPlayerMaxHealthPoints();

	int getPlayerStrength();
	float getPlayerStrengthFinal();
	void setPlayerStrength(int s);

	int getPlayerAgility();
	float getPlayerAgilityFinal();
	void setPlayerAgility(int a);

	int getPlayerLuck();
	void setPlayerLuck(int l);

	int getPlayerEndurance();
	float getPlayerEnduranceFinal();
	void setPlayerEndurance(int e);

	int getPlayerIntelligence();
	float getPlayerIntelligenceFinal();
	void setPlayerIntelligence(int i);

	int getStatPoints();
	void setStatPoints(int sp);

	int getPlayerActionPoints();
	void setPlayerActionPoints(int ap);

	float playerLuckBoost();

	//player action functions
	void move(int moveX, int moveY);
	void borderCol(int moveX, int moveY, int maxBorderX, int maxBorderY);
	bool checkforbattle(enemy& targetenemy);

	int checkEnemyCol(int checkX, int checkY, enemy** allEnemies, int enemyCount);
	void takeDamage(int dmg);

	void heal(int value);           // restores some health
	void loot(int value1, int value2);           // give looted items to player

	// currency / misc

	int getPlayerGold();
	void setPlayerGold(int value);

	int getPlayerKeyFragment();
	void setPlayerKeyFragment(int value);
};
<<<<<<< HEAD
#pragma once
#include "entity.h"
#include "enemy.h"

class enemy;

class player : public entity
{
private:
	std::string playerName;

	int playerHealthPoints;

	int playerStrength;
	float playerStrengthFinal;

	int playerAgility;
	float playerAgilityFinal;

	int playerLuck;
	float playerLuckFinal;

	int playerEndurance;
	float playerEnduranceFinal;

	int playerIntelligence;
	float playerIntelligenceFinal;

	int playerActionPoints;

	bool playerCombatMode;

public:
	player();

	int getPlayerHealthPoints();
	void setPlayerHealthPoints(int hp);

	int getPlayerStrength();
	float getPlayerStrengthFinal();
	void setPlayerStrength(int s);

	int getPlayerAgility();
	float getPlayerAgilityFinal();
	void setPlayerAgility(int a);

	int getPlayerLuck();
	float getPlayerLuckFinal();
	void setPlayerLuck(int l);

	int getPlayerEndurance();
	float getPlayerEnduranceFinal();
	void setPlayerEndurance(int e);

	int getPlayerIntelligence();
	float getPlayerIntelligenceFinal();
	void setPlayerIntelligence(int i);

	int getPlayerActionPoints();
	void setPlayerActionPoints(int ap);

	float playerLuckBoost();

    void move(int moveX, int moveY);
    void borderCol(int moveX, int moveY);
    void testAttack(enemy& targetenemy);
    void checkForEnemy(enemy& targetenemy);
};

=======
#pragma once
#include "entity.h"
#include "enemy.h"
#include <string>

class enemy;

class player : public entity
{
private:
	std::string playerName;

	int playerHealthPoints;

	int playerStrength; // added by Noah
	float playerStrengthFinal;

	int playerAgility;
	float playerAgilityFinal;

	int playerLuck;
	float playerLuckFinal;

	int playerEndurance;
	float playerEnduranceFinal;

	int playerIntelligence;
	float playerIntelligenceFinal;

	int playerActionPoints;

	bool playerCombatMode;

public:
	player(); // added by Noah

	int getPlayerHealthPoints();
	void setPlayerHealthPoints(int hp);

	int getPlayerStrength(); // added by Noah
	float getPlayerStrengthFinal();
	void setPlayerStrength(int s);

	int getPlayerAgility();
	float getPlayerAgilityFinal();
	void setPlayerAgility(int a);

	int getPlayerLuck();
	float getPlayerLuckFinal();
	void setPlayerLuck(int l);

	int getPlayerEndurance();
	float getPlayerEnduranceFinal();
	void setPlayerEndurance(int e);

	int getPlayerIntelligence();
	float getPlayerIntelligenceFinal();
	void setPlayerIntelligence(int i);

	int getPlayerActionPoints();
	void setPlayerActionPoints(int ap);

	float playerLuckBoost();

    void move(int moveX, int moveY);
    void borderCol(int moveX, int moveY);
    void testAttack(enemy& targetenemy);
};


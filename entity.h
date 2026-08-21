#pragma once
class entity
{
private:
	int posX, posY;
	int healthPoints;
	int attack;
	int gold;
	int keyFragment;
	int weapon;
public:
	entity(int posX, int posY, int healthPoints, int attack);
	virtual ~entity();

	int getPosX();
	int getPosY();

	int getHealthPoints();
	void setHealthPoints(int hp);

	int getGold() const;
	void setGold(int value);
	int getKeyFragment() const;
	void setKeyFragment(int value);

	int getWeapon() const;

	void setPosition(int setX, int setY);
	void setPosX(int setX);
	void setPosY(int setY);

	virtual void interact(player* Player) {};  // runs when stepped on by player
	virtual int getAttack() const;
	virtual void displayStats() const {};
};


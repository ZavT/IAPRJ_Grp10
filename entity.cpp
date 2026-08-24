#include "entity.h"

void entity::setPosition(int setX, int setY)
{
	setPosX(setX);
	setPosY(setY);
}

//setters
void entity::setPosX(int setX) {
	posX = setX;
}

void entity::setPosY(int setY) {
	posY = setY;
}

//getters
entity::entity(int posX, int posY, int healthPoints, int attack)
	: posX(posX), posY(posY), healthPoints(healthPoints), attack(attack) {
}

entity::~entity() {

}
int entity::getPosX() {
	return posX;
}

int entity::getPosY() {
	return posY;
}

int entity::getHealthPoints()
{
	return healthPoints;
}

void entity::setHealthPoints(int hp)
{
	healthPoints = hp;
}

int entity::getAttack() const {
	return attack;
}
#pragma once
class entity
{
private:
	int posX, posY;
public:
	int getPosX();
	int getPosY();

	void setPosition(int setX, int setY);
	void setPosX(int setX);
	void setPosY(int setY);
};


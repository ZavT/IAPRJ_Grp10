#include "mutHuman.h"
#include <iostream>
using namespace std;

mutHuman::mutHuman(int posX, int posY, int id)
	: enemy(posX, posY, id + '0', 70) {
}

void mutHuman::displayStats() const
{
	cout << "Mutant Human" << " Health:" << getHealthPoints();
}
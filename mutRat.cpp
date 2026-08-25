#include "mutRat.h"
#include <iostream>
using namespace std;

mutRat::mutRat(int posX, int posY, int id)
	: enemy(posX, posY, id + '0', 30) {
}

void mutRat::displayStats() const
{
	cout << "Mutant Rat" << " Health:" << getHealthPoints() << " Attack:" << getAttack();
}

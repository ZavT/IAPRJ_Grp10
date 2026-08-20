#include "mutRat.h"
#include <iostream>
using namespace std;

mutRat::mutRat(int posX, int posY, int id)
	: enemy(posX, posY, id + '0', 20, 5, 0) {
}

void mutRat::displayStats() const
{
	cout << "Mutant Rat" << " Health:" << getHealth() << " Attack:" << getAttack();
}

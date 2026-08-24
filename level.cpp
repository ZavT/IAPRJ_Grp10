#include "level.h"

level::level(){
	Plevel = 1;
	exp = 0;
}

void level::gainexp(int amt)
{
	exp += amt;
}

int level::getlevel()
{
	return Plevel;
}

int level::getexp()
{
	return exp;
}

bool level::checklevelup()
{
	int expneeded;

	if (Plevel == 0 || Plevel == 1) {
		expneeded = 10;
	}
	else if (Plevel = 2) {
		expneeded = 20;
	}
	else if (Plevel = 3) {
		expneeded = 50;
	}
	else if (Plevel = 4) {
		expneeded = 70;
	}
	else
		return false; // level 5 

	if (exp >= expneeded) {
		exp -= expneeded;
		Plevel++; // level up
	}

	return false;
}

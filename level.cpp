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

int level::getexpneeded() {
	if (Plevel <= 1) return 10;
	if (Plevel == 2) return 20;
	if (Plevel == 3) return 50;
	if (Plevel == 4) return 70;
	return 0; // reach max lv
}

bool level::checklevelup()
{
	int expneeded = getexpneeded();

	if (expneeded == 0) 
	return false;  //level 5

	if (exp >= expneeded) {
		exp -= expneeded;
		Plevel++; // level up
		return true;
	}

	return false;
}

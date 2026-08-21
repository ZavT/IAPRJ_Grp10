#include "bunker.h"

bunker::bunker() : bunkerMap(9, 9)
{
}

void bunker::printbunkerMap(){
	bunkerMap.initPOImap();
	bunkerMap.setpos(0, 4, 'X'); //exit for bunker
	bunkerMap.setpos(0,5 , '-');
	bunkerMap.setpos(0, 3, '-');
}

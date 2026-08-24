#include "bunker.h"

bunker::bunker() : bunkerMap(9, 9)
{
}

void bunker::printbunkerMap(){
	bunkerMap.initPOImap();
	bunkerMap.setpos(8, 4, 'X'); //exit for bunker
	bunkerMap.setpos(8,5 , '-');
	bunkerMap.setpos(8, 3, '-');
}

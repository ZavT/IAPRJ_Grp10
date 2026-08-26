#include "town.h"

town::town():townMap(15,10){
}

void town::printtownMap() {
	townMap.initPOImap();
	townMap.setpos(0, 7, 'X');

	//NPC POSITION TESTING PLEASE DELETE IF NEEDED
	townMap.setpos(7, 4, 'A');
	townMap.setpos(7, 10, 'W');
	townMap.setpos(7, 16, 'M');
	townMap.setpos(7, 3, 'w'); // cat
	townMap.setpos(0, 6, '-');
	townMap.setpos(0, 8, '-');
}

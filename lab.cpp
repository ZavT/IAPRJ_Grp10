#include "lab.h"
#include "mutRat.h"
#include "mutHuman.h"

lab::lab() : labMap (9,20){
}

void lab::printlabMap() {
	labMap.initPOImap();
	labMap.setpos(0, 4, 'X');
}

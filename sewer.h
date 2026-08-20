#pragma once
#include "map.h"
class sewer :
    public map
{
private:
   
public:
    sewer();

    void printSewerMap(int sewernum);
    map sewerMap;
};


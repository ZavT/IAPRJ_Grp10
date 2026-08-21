#pragma once
#include "map.h"
class town :
    public map
{
public:
    town();
    void printtownMap();
    map townMap;
};


#pragma once
#include <string>

class menu
{
private:
    bool isOpen;
    int selectedOption;
    std::string currentTime;
    std::string playerName;
    int currentObjective; 

public:
    menu();
    void menuOpen();
};

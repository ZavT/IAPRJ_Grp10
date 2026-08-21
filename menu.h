#pragma once
#include <string>

class menu
{
private:
    bool isOpen;
    int selectedOption; // 0 = Time, 1 = Objective, 2 = Name, 3 = Stage reset, 4 = Game reset
    std::string currentTime;
    std::string playerName;
    int currentObjective; 

public:
    menu();
    void menuOpen();
};

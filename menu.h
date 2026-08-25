#pragma once
#include <string>

class menu
{
private:
    bool isOpen;
    int selectedOption;
    int currentObjective;

public:
    menu();

    // Allows you to change the objective from game.cpp
    void setObjective(int obj);

    // Now accepts the real time, and returns the minutes to skip!
    int menuOpen(int day, int month, int year, int hour, int minute);
};
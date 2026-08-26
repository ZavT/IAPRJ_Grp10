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
    void setObjective(int obj);
    int menuOpen(int day, int month, int year, int hour, int minute);
};
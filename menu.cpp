#include "menu.h"
#include <iostream>
#include <conio.h>
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER_KEY 13
#define ESCAPE_KEY 27

menu::menu()
{
    isOpen = false;
    selectedOption = 0;
    currentObjective = 1; // Default starting objective
}

void menu::setObjective(int obj) {
    currentObjective = obj;
}

int menu::menuOpen(int day, int month, int year, int hour, int minute)
{
    isOpen = true;
    int minutesToSkip = 0; 

    while (isOpen) {
        system("CLS");

        std::cout << "\t===============Menu===============\n\n";

        std::string timeStr = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year) + " ";
        timeStr += (hour < 10 ? "0" : "") + std::to_string(hour) + ":";
        timeStr += (minute < 10 ? "0" : "") + std::to_string(minute);

        //objectives //edit later
        //settings.setObjective(1); //use this to change objectives
        std::string objStr = "";
        if (currentObjective == 1) objStr = "Find three map fragments";
        else if (currentObjective == 2) objStr = "Kill all mutants";
        else if (currentObjective == 3) objStr = "Kill THE scientist";

        std::string opt0 = (selectedOption == 0) ? "< Time : " + timeStr + " >" : "  Time : " + timeStr + "  ";
        std::string opt1 = (selectedOption == 1) ? "< Objective : " + objStr + " >" : "  Objective : " + objStr + "  ";
        std::string opt2 = (selectedOption == 2) ? "< Skip 12 Hours >" : "  Skip 12 Hours  ";
        std::string opt3 = (selectedOption == 3) ? "< Restart stage >" : "  Restart stage  ";
        std::string opt4 = (selectedOption == 4) ? "< Restart game >" : "  Restart game  ";

        //visual
        std::cout << "\t" << opt0 << "\n";
        std::cout << "\t" << opt1 << "\n";
        std::cout << "\t" << opt2 << "\n";
        std::cout << "\t" << opt3 << "\n";
        std::cout << "\t" << opt4 << "\n\n";

        std::cout << "\n";
        std::cout << "\tPress UP/DOWN arrow key to switch between tabs\n";
        std::cout << "\tPress ENTER to select\n";
        std::cout << "\tPress ESCAPE to return to map\n";

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == KEY_UP) {
                selectedOption--;
                if (selectedOption < 0) selectedOption = 4; // Wrap to bottom
            }
            else if (ch == KEY_DOWN) {
                selectedOption++;
                if (selectedOption > 4) selectedOption = 0; // Wrap to top
            }
        }
        else if (ch == ENTER_KEY) {
            if (selectedOption == 2) {
                // Skip 12 hours (720 minutes)
                minutesToSkip += 720;
                isOpen = false; // Close menu to process time
            }
            else if (selectedOption == 3) {
                std::cout << "\n\t Press ENTER..."; //restart stage
                (void)_getch();
            }
            else if (selectedOption == 4) {
                std::cout << "\n\t Press ENTER..."; //restart game
                (void)_getch();
            }
        }
        else if (ch == ESCAPE_KEY) {
            isOpen = false;
        }
    }

    // Return the minutes we want to add back to game.cpp
    return minutesToSkip;
}
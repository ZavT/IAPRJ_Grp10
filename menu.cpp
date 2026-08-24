#include "menu.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER_KEY 13
#define ESCAPE_KEY 27

menu::menu()
{
    isOpen = false;
    selectedOption = 0; 
    currentTime = " ";
    playerName = " ";
    currentObjective = 1;
}

void menu::menuOpen()
{
    isOpen = true;

    while (isOpen) {
        system("CLS");

        std::cout << "\t===============Menu===============\n\n";

        std::string opt0 = (selectedOption == 0) ? "< Time : " + currentTime + " >" : "  Time : " + currentTime + "  ";
        std::string opt1 = (selectedOption == 1) ? "< Objective : >" : "  Objective :  ";
        std::string opt2 = (selectedOption == 2) ? "< Edit name: " + playerName + " >" : "  Edit name: " + playerName + "  ";
        std::string opt3 = (selectedOption == 3) ? "< restart stage >" : "  restart stage  ";
        std::string opt4 = (selectedOption == 4) ? "< restart game >" : "  restart game  ";

        // Print the left menu column, and align the objectives on the right
        std::cout << "\t" << std::left << std::setw(30) << opt0 << (currentObjective >= 1 ? "Find three map fragments" : "") << "\n";
        std::cout << "\t" << std::left << std::setw(30) << opt1 << (currentObjective >= 2 ? "Kill all rats" : "") << "\n";
        std::cout << "\t" << std::left << std::setw(30) << opt2 << (currentObjective >= 3 ? "Kill THE scientist" : "") << "\n";
        std::cout << "\t" << std::left << std::setw(30) << opt3 << "\n";
        std::cout << "\t" << std::left << std::setw(30) << opt4 << "\n\n";

       
        //instructions
        std::cout << "\n";
        std::cout << "\tPress left or right arrow key to switch between tabs\n";
        std::cout << "\tPress the number to see item in current tab\n";
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
            if (selectedOption == 0) {
                std::cout << "\n\tEnter new time: ";
                std::cin >> currentTime;
            }
            else if (selectedOption == 1) {  //change to at differnet parts of the game have diff objective
                currentObjective++;
                if (currentObjective > 3) currentObjective = 1;
            }
            else if (selectedOption == 2) {
                std::cout << "\n\tEnter new name: ";
                std::cin >> playerName;
            }
            else if (selectedOption == 3) {
                std::cout << "\n\t Press ENTER...";
                (void)_getch();
            }
            else if (selectedOption == 4) {
                std::cout << "\n\t Press ENTER...";
                (void)_getch();
            }
        }
        else if (ch == ESCAPE_KEY) { 
            isOpen = false;
        }
    }
}
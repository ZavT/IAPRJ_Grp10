#include "inspect.h"
#include <iostream>
#include <conio.h>

#define ESCAPE_KEY 27

inspect::inspect()
{
    isOpen = false;
}

void inspect::inspectOpen()
{
    isOpen = true;

    while (isOpen) {
        system("CLS");
        int ch = _getch();

        std::cout << "\t=============Inspect=============\n\n";

        std::cout << "Inspecting entities in current location\n" << std::endl;
        std::cout << "Mutant rats. Giant, vicious creatures that can tear you apart.\n" << std::endl;

        for (int i = 0; i < 3; ++i)
        {
            if (mutRats[i] != NULL) {
                mutRats[i]->displayStats();
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        std::cout << "Mutant humans.\n" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            if (mutHumans[i] != NULL) {
                mutHumans[i]->displayStats();
                std::cout << " ";
            }
        }
        if (ch == ESCAPE_KEY) {
            isOpen = false;
        }
    }
}
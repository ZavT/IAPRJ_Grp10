#include "inspect.h"
#include "enemy.h"
#include <iostream>
#include <conio.h>

#define ESCAPE_KEY 27

inspect::inspect()
{
    isOpen = false;
}

void inspect::inspectOpen(enemy** enemies, int enemyCount)
{
    isOpen = true;
    system("CLS");

    while (isOpen) {
        int ch = _getch();

        std::cout << "\t=============Inspect=============\n\n";

        std::cout << "Inspecting enemies in current location\n" << std::endl;

        if (enemies == nullptr || enemyCount == 0) {
            std::cout << "There are no enemies here." << std::endl;
        }
        else {
            for (int i = 0; i < enemyCount; ++i) {
                if (enemies[i] != nullptr) {
                    enemies[i]->displayStats();
                    std::cout << std::endl;
                }
            }
        }

        std::cout << "[ESC] Exit to game\n" << std::endl;

        if (ch == ESCAPE_KEY) {
            isOpen = false;
        }
    }
}
